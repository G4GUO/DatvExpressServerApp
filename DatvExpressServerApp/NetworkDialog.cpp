// NetworkDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "NetworkDialog.h"
#include "afxdialogex.h"


// CNetworkDialog dialog

IMPLEMENT_DYNAMIC(CNetworkDialog, CDialogEx)

CNetworkDialog::CNetworkDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkDialog::IDD, pParent)
	, m_port(0)
	, m_remote_ip_s(_T(""))
	, m_multicast_ip_s(_T(""))
	, m_multicast_enable(FALSE)
{
	m_port = theApp.m_ip_port;

}

CNetworkDialog::~CNetworkDialog()
{
}

void CNetworkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDV_MinMaxInt(pDX, m_port, 0, 65535);
	DDX_Control(pDX, IDC_EDIT_REMOTE_IP, m_remote_ip);
	DDX_Control(pDX, IDC_COMBO_LOCAL_IP, m_local_ip);
	DDX_Text(pDX, IDC_EDIT_REMOTE_IP, m_remote_ip_s);
	DDX_Text(pDX, IDC_EDIT_MULTICAST_IP, m_multicast_ip_s);
	DDX_Check(pDX, IDC_CHECK_MULTICAST, m_multicast_enable);
	DDX_Control(pDX, IDC_CHECK_MULTICAST, m_multicast_on);
	DDX_Control(pDX, IDC_EDIT_MULTICAST_IP, m_multicast_ip);
}


BEGIN_MESSAGE_MAP(CNetworkDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNetworkDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_MULTICAST, &CNetworkDialog::OnClickedCheckMulticast)
END_MESSAGE_MAP()


// CNetworkDialog message handlers


void CNetworkDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	theApp.m_ip_port = m_port;
	CString text;
	m_local_ip.GetWindowTextW(text);
	//m_local_ip.GetLBText(0,text);
	theApp.m_ip_local = text;
	theApp.m_ip_remote=m_remote_ip_s;
	theApp.m_multicast = m_multicast_enable;
	theApp.m_ip_multicast = m_multicast_ip_s;
}


BOOL CNetworkDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	hostent* localHost;
    char* localIP;
	CString text;

	// Get the local host information
    localHost = gethostbyname("");
	if(localHost != NULL){
		int index = 0;
		while(localHost->h_addr_list[index] != NULL ){
			localIP   = inet_ntoa (*(struct in_addr *)localHost->h_addr_list[index]);
			text = localIP;
			m_local_ip.AddString(text);
			index++;
		}
	}
	else{
		m_local_ip.AddString(theApp.m_ip_local);
	}
	m_local_ip.SelectString(-1,theApp.m_ip_local);
	m_remote_ip.SetWindowTextW(theApp.m_ip_remote);
	m_multicast_on.SetCheck(theApp.m_multicast);
	m_multicast_ip.SetWindowTextW(theApp.m_ip_multicast);

	if(theApp.m_multicast == FALSE){
		m_local_ip.EnableWindow(FALSE);
		m_remote_ip.EnableWindow(FALSE);
		m_multicast_ip.EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CNetworkDialog::OnClickedCheckMulticast()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BOOL status =  m_multicast_enable;
	m_local_ip.EnableWindow(status);
	m_remote_ip.EnableWindow(status);
	m_multicast_ip.EnableWindow(status);
}
