// SymbolRateDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "SymbolRateDialog.h"
#include "afxdialogex.h"


// CSymbolRateDialog dialog

IMPLEMENT_DYNAMIC(CSymbolRateDialog, CDialogEx)

CSymbolRateDialog::CSymbolRateDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSymbolRateDialog::IDD, pParent)
	, m_symbol_rate(0)
{
	m_symbol_rate = theApp.m_symbol_rate;
}

CSymbolRateDialog::~CSymbolRateDialog()
{
}

void CSymbolRateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SYMBOL_RATE, m_symbol_rate);
	DDV_MinMaxDWord(pDX, m_symbol_rate, 100000, 12000000);
}


BEGIN_MESSAGE_MAP(CSymbolRateDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSymbolRateDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSymbolRateDialog message handlers


void CSymbolRateDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	theApp.m_symbol_rate = m_symbol_rate;
}
