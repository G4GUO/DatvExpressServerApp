// TxLevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "TxLevelDialog.h"
#include "afxdialogex.h"


// CTxLevelDlg dialog

IMPLEMENT_DYNAMIC(CTxLevelDialog, CDialogEx)

CTxLevelDialog::CTxLevelDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTxLevelDialog::IDD, pParent)
	, m_tx_level(0)
{
	m_tx_level = theApp.m_level;
}

CTxLevelDialog::~CTxLevelDialog()
{
}

void CTxLevelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TX_LEVEL, m_tx_level);
	DDV_MinMaxInt(pDX, m_tx_level, 0, 100);
}


BEGIN_MESSAGE_MAP(CTxLevelDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTxLevelDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CTxLevelDlg message handlers


void CTxLevelDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
	theApp.m_level = m_tx_level;
}
