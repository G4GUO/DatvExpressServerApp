// FecDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "FecDialog.h"
#include "afxdialogex.h"


// CFecDialog dialog

IMPLEMENT_DYNAMIC(CFecDialog, CDialogEx)

CFecDialog::CFecDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFecDialog::IDD, pParent)
	, m_fec_button(0)
{
	m_fec_button = theApp.m_fec;
}

CFecDialog::~CFecDialog()
{
}

void CFecDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_FEC_12, m_fec_button);
	DDV_MinMaxInt(pDX, m_fec_button, 0, 4);
}


BEGIN_MESSAGE_MAP(CFecDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFecDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CFecDialog message handlers


void CFecDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	theApp.m_fec = m_fec_button;
}
