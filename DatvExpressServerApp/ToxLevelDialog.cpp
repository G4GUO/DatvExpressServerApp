// ToxLevelDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "ToxLevelDialog.h"
#include "afxdialogex.h"


// CToxLevelDialog dialog

IMPLEMENT_DYNAMIC(CToxLevelDialog, CDialogEx)

CToxLevelDialog::CToxLevelDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToxLevelDialog::IDD, pParent)
	, m_tox_timeout(0)
{
	m_tox_timeout = theApp.m_tox_timeout;
}

CToxLevelDialog::~CToxLevelDialog()
{
}

void CToxLevelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TOX_LEVEL, m_tox_timeout);
	DDV_MinMaxInt(pDX, m_tox_timeout, 0, 10000);}


BEGIN_MESSAGE_MAP(CToxLevelDialog, CDialogEx)
ON_BN_CLICKED(IDOK, &CToxLevelDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CToxLevelDialog message handlers
void CToxLevelDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
	theApp.m_tox_timeout = m_tox_timeout;
}
