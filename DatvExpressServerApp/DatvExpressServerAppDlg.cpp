
// DatvExpressServerAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "DatvExpressServerAppDlg.h"
#include "afxdialogex.h"
#include "express.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Should be in a header
void UDPServerTOX(BOOL tox);


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDatvExpressServerAppDlg dialog



CDatvExpressServerAppDlg::CDatvExpressServerAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDatvExpressServerAppDlg::IDD, pParent)
	, m_transmit(FALSE)
	, m_carrier(FALSE)
	, m_tox(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDatvExpressServerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CARRIER, m_carrier);
	DDX_Check(pDX, IDC_CHECK_TOX, m_tox);
}

BEGIN_MESSAGE_MAP(CDatvExpressServerAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_CARRIER, &CDatvExpressServerAppDlg::OnBnClickedCheckCarrier)
	ON_BN_CLICKED(IDC_CHECK_TOX, &CDatvExpressServerAppDlg::OnClickedCheckTox)
	ON_BN_CLICKED(IDC_BUTTON_PTT, &CDatvExpressServerAppDlg::OnClickedButtonPtt)
END_MESSAGE_MAP()


// CDatvExpressServerAppDlg message handlers

BOOL CDatvExpressServerAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    UpdateDialogTextControls();
	//
	// Configure the express board here
	//
	express_set_freq(theApp.m_frequency);
	express_set_sr(theApp.m_symbol_rate);
	express_set_fec(theApp.m_fec);
	express_set_level(theApp.m_level);

    if(UDPServerInit()<0) ::MessageBox(NULL,L"Unable to open UDP Network Socket",L"Fatal",MB_OK);

    theApp.m_status_s = "RECEIVE";
	theApp.DisplayStatusMessage();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDatvExpressServerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDatvExpressServerAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void CDatvExpressServerAppDlg::UpdateDialogTextControls()
{
	CString text;
	CStatic *di;
	di = (CStatic*)GetDlgItem(IDC_STATIC_FREQUENCY_TEXT);
	text.Format(_T("%u"),theApp.m_frequency);
	di->SetWindowTextW(text);
	di = (CStatic*)GetDlgItem(IDC_STATIC_SYMBOL_RATE_TEXT);
	text.Format(_T("%ld"),theApp.m_symbol_rate);
	di->SetWindowTextW(text);
	di = (CStatic*)GetDlgItem(IDC_STATIC_LEVEL_TEXT);
	text.Format(_T("%d"),theApp.m_level);
	di->SetWindowTextW(text);
	di = (CStatic*)GetDlgItem(IDC_STATIC_FEC_TEXT);
	switch(theApp.m_fec)
	{
	case FEC_12:
	    text.Format(_T("%s"),_T("1/2"));
		break;
	case FEC_23:
	    text.Format(_T("%s"),_T("2/3"));
		break;
	case FEC_34:
	    text.Format(_T("%s"),_T("3/4"));
		break;
	case FEC_56:
	    text.Format(_T("%s"),_T("5/6"));
		break;
	case FEC_78:
	    text.Format(_T("%s"),_T("7/8"));
		break;
	default:
	    text.Format(_T("%s"),_T("??"));
		break;
	}
	di->SetWindowTextW(text);
	di = (CStatic*)GetDlgItem(IDC_STATIC_SOCKET_TEXT);
	text.Format(_T("%d"),theApp.m_ip_port);
	di->SetWindowTextW(text);
}
void CDatvExpressServerAppDlg::DisplayStatusMessage(void)
{
	CStatic *di = (CStatic*)GetDlgItem(IDC_STATIC_STATUS_TEXT);
	di->SetWindowTextW(theApp.m_status_s);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDatvExpressServerAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDatvExpressServerAppDlg::OnBnClickedCheckCarrier()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	theApp.OnCarrier(m_carrier);
}


void CDatvExpressServerAppDlg::OnClickedCheckTox()
{
	// TODO: Add your control notification handler code here
	UpdateData();
    UDPServerTOX(m_tox);
}


void CDatvExpressServerAppDlg::OnClickedButtonPtt()
{
	// TODO: Add your control notification handler code here
	// Toggle the transmitter

	if(m_transmit == TRUE)
		m_transmit = FALSE;
	else
	    m_transmit = TRUE;

	theApp.OnTransmit( m_transmit );
}
