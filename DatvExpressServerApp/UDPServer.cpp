#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "express.h"

extern CDatvExpressServerAppApp theApp;
DWORD lpThreadId[3];
SOCKET m_sockID;
struct sockaddr_in m_fepAddr;
int m_sock_len;
BOOL m_tox;
static ULONG m_inet_mult;
static ULONG m_inet_rmt;
static ULONG m_inet_lcl;

//
// This is because the Microsoft UDP interface acts on blocks
// and we want individual transport packets, so we have to buffer them
//
UCHAR m_udp_buffer[TP_SIZE*128];

// Leaving and joining multicast groups
#define u_int32 UINT32  // Unix uses u_int32

/* OUT: whatever setsockopt() returns */
int	join_source_group(int sd, u_int32 grpaddr, u_int32 srcaddr, u_int32 iaddr)
{
   struct ip_mreq_source imr; 
   int res;
   
   imr.imr_multiaddr.s_addr  = grpaddr;
   imr.imr_sourceaddr.s_addr = srcaddr;
   imr.imr_interface.s_addr  = iaddr;
   if(srcaddr == 0 )
		res = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &imr, sizeof(imr));  
   else
		res = setsockopt(sd, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP, (char *) &imr, sizeof(imr));  
   return res;
}

int leave_source_group(int sd, u_int32 grpaddr, u_int32 srcaddr, u_int32 iaddr)
{
   struct ip_mreq_source imr;
   int res;

   imr.imr_multiaddr.s_addr  = grpaddr;
   imr.imr_sourceaddr.s_addr = srcaddr;
   imr.imr_interface.s_addr  = iaddr;
   if(srcaddr == 0 )
		res = setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *) &imr, sizeof(imr));  
   else
		res = setsockopt(sd, IPPROTO_IP, IP_DROP_SOURCE_MEMBERSHIP, (char *) &imr, sizeof(imr));  
   return res;
}
int create_new_socket(void){

	m_sockID = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(theApp.m_multicast == FALSE){
		m_fepAddr.sin_family = AF_INET;
		m_fepAddr.sin_port = htons(theApp.m_ip_port);
		m_fepAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		m_sock_len = sizeof(struct sockaddr_in);
	}

	if(theApp.m_multicast == TRUE){
		m_fepAddr.sin_family = AF_INET;
		m_fepAddr.sin_port = htons(theApp.m_ip_port);
		m_sock_len = sizeof(struct sockaddr_in);
		char c_lcl[40],c_rmt[40],c_mult[40];

		WideCharToMultiByte( CP_ACP, 0, theApp.m_ip_local,     -1, c_lcl,  40,0,0);  
		WideCharToMultiByte( CP_ACP, 0, theApp.m_ip_remote,    -1, c_rmt,  40,0,0);  
		WideCharToMultiByte( CP_ACP, 0, theApp.m_ip_multicast, -1, c_mult, 40,0,0); 
		m_inet_mult = inet_addr(c_mult);
		m_inet_rmt  = inet_addr(c_rmt);
		m_inet_lcl  = inet_addr(c_lcl);

		m_fepAddr.sin_addr.s_addr = inet_addr(c_lcl);

		join_source_group(m_sockID, m_inet_mult, m_inet_rmt, m_inet_lcl);
	}

	if( bind(m_sockID, (struct sockaddr *)&m_fepAddr, m_sock_len) < 0)
	{
		int error = WSAGetLastError();
		printf("bind() failed: %ld.\n", error);
		closesocket(m_sockID);
	    return -1;
	}
	return 0;
}

void get_udp_buffer( UCHAR *b, INT len )
{
	static INT bytes_left;// Bytes left in UDP frames
	static INT offset;// Current offset into UDP frame

	if( bytes_left >= len )
	{
		// More bytes available than requested
		memcpy(b,&m_udp_buffer[offset],len);
		offset     += len;
		bytes_left -= len;
	}
	else
	{
		// Not enough available copy what we can
		memcpy(b,&m_udp_buffer[offset],bytes_left);
		INT to_do = len - bytes_left;// Number still requires
		INT start = bytes_left;// Where to place them
		// get a new buffer
		bytes_left = recvfrom(m_sockID, (char*)m_udp_buffer, TP_SIZE*128, 0,(struct sockaddr *)&m_fepAddr, &m_sock_len);
		offset     = 0;// Start at the begining of the buffer
        if(bytes_left > 0)
		{
			// Copy the remainder of the data
			memcpy(&b[start],m_udp_buffer,to_do);
			offset      = to_do;
			bytes_left -= to_do;
		}
		else
		{
			// Something has gone horribly wrong
			bytes_left = 0;
		}
	}
}
//
// Timer library
//
#define CLOCK_PERIOD 20
static long m_time;

UINT ticktock_thread(LPVOID pParam)
{
	m_time = 0;
	while( theApp.m_threads )
	{
		Sleep(CLOCK_PERIOD);
		if( m_time > 0 ){
			m_time -= CLOCK_PERIOD;
			if(m_time <= 0) m_time = 0;
		}
	}
	return 0;
}
// See if we have timeout
BOOL istimeout(void){
	if(m_time > 0) 
		return FALSE;
	else
		return TRUE;
}
// Start / restart the timer
void start_timer( long timeperiod ){
	if(timeperiod > 0 ) m_time = timeperiod;
}
//
// Continuously read from the UDP socket
//
UINT udp_thread(LPVOID pParam)
{
	while( theApp.m_threads )
	{
		UCHAR *b = alloc_buff();
		get_udp_buffer( b, TP_SIZE );
		if( b[0] != SYNC_BYTE ){ // Try to achieve sync
			for( int i = 0; i < TP_SIZE-1; i++ ){
				get_udp_buffer( b, 1 );
				if( b[0] == SYNC_BYTE ){
				    get_udp_buffer( b, TP_SIZE - 1 );
				}
			}
		}
		if(((b[1]&0x1F) == 0x1F)&&(b[1] == 0xFF)){
			// Strip out unwanted NULLs in the transport stream
			rel_buff(b);
		}
		else{
			// Queue
			post_buff( b );
		}
	}
	// Close the socket gracefully
	if(theApp.m_multicast == TRUE){
		leave_source_group(m_sockID, m_inet_mult, m_inet_rmt, m_inet_lcl);
	}
	closesocket(m_sockID);
    WSACleanup();
	return 0;
}
//
// Add NULL packets when no user TP are available
//
UINT tx_thread(LPVOID pParam)
{
	UCHAR *b;
	while( theApp.m_threads )
	{
		if(theApp.m_status_tx == TRUE ){
		    if((b = get_buff()) != NULL)
		    {
				if( m_tox == TRUE ) start_timer(theApp.m_tox_timeout);
			    express_write_transport_stream(b,TP_SIZE);
		    }
		    else
		    {
			    express_write_transport_stream(null_pkt(),TP_SIZE);// Add a NULL
		    }
			// We are transmitting
		    if( m_tox == TRUE ){
			    if(istimeout()==TRUE) theApp.OnTransmit(FALSE);
		    }
		}
		else{
			 // We are receiving
		     if( m_tox == TRUE ){
				 if(get_buf_qsize()> 10 )theApp.OnTransmit(TRUE);
			 }
			 Sleep(10);
		}
	}
	// Shutdown Express gracefully
	return 0;
}
void UDPServerTOX(BOOL tox){
    m_tox = tox;
	if(tox == FALSE )theApp.OnTransmit(FALSE); 
}
int UDPServerInit(void)
{
	int n;

	m_tox = FALSE;
    buf_init();
    null_fmt();

	WSADATA wsaData = {0};

	// Create and listen to the UDP socket
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(create_new_socket()<0){
        WSACleanup();
	    return -1;
	}
	//
	// Create the thread processes
	//
	CreateThread(NULL, //Choose default security
                 0, //Default stack size
                 (LPTHREAD_START_ROUTINE)&udp_thread, //Routine to execute
                 (LPVOID) &n, //Thread parameter
                 0, //Immediately run the thread
                 &lpThreadId[0] //Thread Id
     );

     CreateThread(NULL, //Choose default security
                  0, //Default stack size
                  (LPTHREAD_START_ROUTINE)&tx_thread, //Routine to execute
                  (LPVOID) &n, //Thread parameter
                  0, //Immediately run the thread
                  &lpThreadId[1] //Thread Id
     );

	 CreateThread(NULL, //Choose default security
                  0, //Default stack size
                  (LPTHREAD_START_ROUTINE)&ticktock_thread, //Routine to execute
                  (LPVOID) &n, //Thread parameter
                  0, //Immediately run the thread
                  &lpThreadId[2] //Thread Id
     );
     //SetThreadPriority( &lpThreadId[1],  THREAD_PRIORITY_TIME_CRITICAL);
	 return 0;
}