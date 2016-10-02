
#include "stdafx.h"
#include <sys/types.h>
#include <memory.h>
#include "express.h"

static unsigned char m_null[TP_SIZE];

//
// Format a transport packet
//
void null_fmt( void )
{
    m_null[0] = 0x47;
    m_null[1] = 0;
    // Add the 13 bit pid
	m_null[1] = 0x1F;
	m_null[2] = 0xFF;
	m_null[3] = 0x10;
    for( int i = 4; i < TP_SIZE; i++ ) m_null[i] = 0xFF;
}
void update_cont_counter( void )
{
   unsigned char c;

   c = m_null[3]&0x0F;
   c = (c+1)&0x0F;
   m_null[3] = (m_null[3]&0xF0) | c;
}
//
// Send a NULL packet
//
UCHAR *null_pkt(void)
{
    update_cont_counter();
    UCHAR *b = alloc_buff();
	if(b != NULL )
	{
		memcpy(b,m_null,TP_SIZE);
	}
	return b;
}
