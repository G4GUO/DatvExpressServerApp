
// DatvExpressServerApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "DatvExpressServerAppDlg.h"
#include "FrequencyDialog.h"
#include "SymbolrateDialog.h"
#include "FecDialog.h"
#include "NetworkDialog.h"
#include "OffsetDialog.h"
#include "TxLevelDialog.h"
#include "ToxLevelDialog.h"
#include "Express.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDatvExpressServerAppApp

BEGIN_MESSAGE_MAP(CDatvExpressServerAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_COMMAND(ID_CONFIGURATION_FREQUENCY, &CDatvExpressServerAppApp::OnConfigurationFrequency)
	ON_COMMAND(ID_CONFIGURATION_SYMBOLRATE, &CDatvExpressServerAppApp::OnConfigurationSymbolrate)
	ON_COMMAND(ID_CONFIGURATION_FEC, &CDatvExpressServerAppApp::OnConfigurationFec)
	ON_COMMAND(ID_CONFIGURATION_NETWORK, &CDatvExpressServerAppApp::OnConfigurationNetwork)
	ON_COMMAND(ID_CONFIGURATION_DCOFFSET, &CDatvExpressServerAppApp::OnConfigurationDcoffset)
	ON_COMMAND(ID_CONFIGURATION_TXLEVEL, &CDatvExpressServerAppApp::OnConfigurationTxlevel)
	ON_COMMAND(ID_CONFIGURATION_TOXLEVEL, &CDatvExpressServerAppApp::OnConfigurationToxlevel)
END_MESSAGE_MAP()


// CDatvExpressServerAppApp construction

CDatvExpressServerAppApp::CDatvExpressServerAppApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDatvExpressServerAppApp object

CDatvExpressServerAppApp theApp;


// CDatvExpressServerAppApp initialization

BOOL CDatvExpressServerAppApp::InitInstance()
{
	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	m_threads = TRUE;// Enable Express threads to run
	LoadConfigFromDisk();
	ConfigureExpress();
	CDatvExpressServerAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	m_threads = FALSE;// Kill the threads
	SaveConfigToDisk();// Always Save
    DeConfigureExpress();// Shutdown Express Correctly
    // Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



void CDatvExpressServerAppApp::OnConfigurationFrequency()
{
	// TODO: Add your command handler code here
	CFrequencyDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		express_set_freq(theApp.m_frequency);
		((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
	}
}

void CDatvExpressServerAppApp::OnConfigurationSymbolrate()
{
	// TODO: Add your command handler code here
	CSymbolRateDialog dlg;
	DWORD oldrate = theApp.m_symbol_rate;
	if(dlg.DoModal()==IDOK)
	{
		express_set_sr(theApp.m_symbol_rate);
        ((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
	}
}


void CDatvExpressServerAppApp::OnConfigurationFec()
{
	// TODO: Add your command handler code here
	CFecDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		express_set_fec(theApp.m_fec);
		((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
	}
}


void CDatvExpressServerAppApp::OnConfigurationNetwork()
{
	// TODO: Add your command handler code here
	CNetworkDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
		::MessageBox(NULL,L"Restart required",L"Warning",MB_OK);
	}
}
void CDatvExpressServerAppApp::OnConfigurationDcoffset()
{
	// TODO: Add your command handler code here
	COffsetDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		//((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
	}
}
void CDatvExpressServerAppApp::OnConfigurationTxlevel()
{
	// TODO: Add your command handler code here
	CTxLevelDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		express_set_level(theApp.m_level);
		((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
	}
}
void CDatvExpressServerAppApp::OnConfigurationToxlevel()
{
	// TODO: Add your command handler code here
	CToxLevelDialog dlg;
	if(dlg.DoModal()==IDOK)
	{
		((CDatvExpressServerAppDlg *)m_pMainWnd)->UpdateDialogTextControls();
	}
}
void CDatvExpressServerAppApp::DisplayStatusMessage(void)
{
	CDatvExpressServerAppDlg *dlg = (CDatvExpressServerAppDlg *)m_pMainWnd;
	dlg->DisplayStatusMessage();
}
// DATV Express specific code
void CDatvExpressServerAppApp::OnTransmit( BOOL b )
{
	m_status_tx = b;

	if (b == TRUE){
		express_transmit();
		m_status_s = "TRANSMIT";
	}
	else{
		express_receive();
		m_status_s = "RECEIVE";
	}
	DisplayStatusMessage();
}
BOOL CDatvExpressServerAppApp::IsTransmit( void )
{
	return m_status_tx;
}
void CDatvExpressServerAppApp::OnCarrier( BOOL b )
{
	express_set_carrier(b);
}
void CDatvExpressServerAppApp::IDCOffsetUpdate( int ival )
{
	m_i_offset = ival;
}
void CDatvExpressServerAppApp::QDCOffsetUpdate( int ival )
{
	m_q_offset = ival;
}
//
// Read in Configuration information from Disk
//
void CDatvExpressServerAppApp::LoadConfigFromDisk(void)
{
	WCHAR directory[250];
	if(GetCurrentDirectory(250,directory)){
		wcsncat_s(directory,L"\\datvexpress.txt",17);
		FILE *fp;
		if(_wfopen_s(&fp,directory,L"r") == 0 ){
			char a[20],b[20],c[20];
			m_multicast = FALSE;
			while(fscanf_s(fp,"%s %s %s",a,_countof(a),b,_countof(b),c,_countof(c))!= EOF){
				if(a[0] != '#'){
					if(strncmp(a,"set",3)==0){
						if(strncmp(b,"fec",3)==0){
							if(strncmp(c,"1/2",3)==0) m_fec = FEC_12;
							if(strncmp(c,"2/3",3)==0) m_fec = FEC_23;
							if(strncmp(c,"3/4",3)==0) m_fec = FEC_34;
							if(strncmp(c,"5/6",3)==0) m_fec = FEC_56;
							if(strncmp(c,"7/8",3)==0) m_fec = FEC_78;
						}
						if(strncmp(b,"srate",5)==0){
							m_symbol_rate = strtoul(c,NULL,10);
						}
						if(strncmp(b,"freq",4)==0){
							m_frequency = strtoul(c,NULL,10);
						}
						if(strncmp(b,"level",5)==0){
							m_level = atoi(c);
						}
						if(strncmp(b,"ip_port",7)==0){
							m_ip_port = atoi(c);
						}
						if(strncmp(b,"ip_remote",9)==0){
							m_ip_remote = c;
						}
						if(strncmp(b,"ip_local",8)==0){
							m_ip_local = c;
						}
						if(strncmp(b,"ip_multicast",12)==0){
							m_ip_multicast = c;
						}
						if(strncmp(b,"multicast",9)==0){
							m_multicast = TRUE;
						}
						if(strncmp(b,"ioff",4)==0){
							m_i_offset = atoi(c);
						}
						if(strncmp(b,"qoff",4)==0){
							m_q_offset = atoi(c);
						}
						if(strncmp(b,"tox",4)==0){
							m_tox_timeout = atoi(c);
						}
					}
				}
			}
			fclose(fp);
		}  
	}
}
//
// Save the configuration information to disk
// called after OK exit
//
void CDatvExpressServerAppApp::SaveConfigToDisk(void)
{
	WCHAR filename[2][250];
	if(GetCurrentDirectory(250,filename[0])){
		wcsncat_s(filename[0],L"\\datvexpress.txt",17);
	    if(GetCurrentDirectory(250,filename[1])){
		    wcsncat_s(filename[1],L"\\datvexpress.bak",17);
			_wremove(filename[1]);
			_wrename(filename[0],filename[1]);

  			FILE *fp;
			char text[256];
			if(_wfopen_s(&fp,filename[0],L"w") == 0 ){
				fprintf(fp,"# Automatically updated\n");
				fprintf(fp,"set srate %lu\n",m_symbol_rate);
				fprintf(fp,"set freq %lu\n",m_frequency);
				fprintf(fp,"set level %d\n",m_level);
				fprintf(fp,"set ip_port %d\n",m_ip_port);
				WideCharToMultiByte( CP_ACP, 0, m_ip_remote, -1, text, 20,0,0);  
				fprintf(fp,"set ip_remote %s\n",text);
				WideCharToMultiByte( CP_ACP, 0, m_ip_local, -1, text, 20,0,0);  
				fprintf(fp,"set ip_local %s\n",text);
				WideCharToMultiByte( CP_ACP, 0, m_ip_multicast, -1, text, 20,0,0);  
				fprintf(fp,"set ip_multicast %s\n",text);
				fprintf(fp,"set ioff %d\n",m_i_offset);
				fprintf(fp,"set qoff %d\n",m_q_offset);
				fprintf(fp,"set tox %d\n",m_tox_timeout);
				if(m_multicast==TRUE) fprintf(fp,"set multicast on\n");

				switch(m_fec)
				{
				case FEC_12:
					fprintf(fp,"set fec 1/2\n");
					break;
				case FEC_23:
					fprintf(fp,"set fec 2/3\n");
					break;
				case FEC_34:
					fprintf(fp,"set fec 3/4\n");
					break;
				case FEC_56:
					fprintf(fp,"set fec 5/6\n");
					break;
				case FEC_78:
					fprintf(fp,"set fec 7/8\n");
					break;
				default:
					break;
				}
				fclose(fp);
			}
		}  
	}
}
void CDatvExpressServerAppApp::ConfigureExpress(void)
{
	FILE *fpga,*fx2;
	WCHAR directory[250];

	if(GetCurrentDirectory(250,directory)){
		wcsncat_s(directory,L"\\datvexpress8.ihx",18);
		if(_wfopen_s(&fx2,directory,L"rb") == 0 )
		{
			if(GetCurrentDirectory(250,directory))
			{
				wcsncat_s(directory,L"\\datvexpressdvbs.rbf",21);
				if(_wfopen_s(&fpga,directory,L"rb") == 0 )
				{
					express_init( fx2, fpga);
					fclose(fpga);
				}
				else
				{
					m_status_s = "No FPGA File";
					::MessageBox(NULL,L"FPGA .rbf File not found",L"Fatal",MB_OK);
				}
				fclose(fx2);
			}
		}
		else
		{
			m_status_s = "No FX2 File";
		    ::MessageBox(NULL,L"FX2 firmware .ihx File not found",L"Fatal",MB_OK);
		}
	}
}
void CDatvExpressServerAppApp::DeConfigureExpress(void)
{
	express_deinit();
}
