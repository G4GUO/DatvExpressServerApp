// FrequencyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "FrequencyDialog.h"
#include "afxdialogex.h"


// CFrequencyDialog dialog

IMPLEMENT_DYNAMIC(CFrequencyDialog, CDialogEx)

CFrequencyDialog::CFrequencyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFrequencyDialog::IDD, pParent)
	, m_frequency(0)
{
	m_frequency = theApp.m_frequency;
}

CFrequencyDialog::~CFrequencyDialog()
{
}

void CFrequencyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_frequency);
	DDV_MinMaxDWord(pDX, m_frequency, 65000000, 2480000000);
}


BEGIN_MESSAGE_MAP(CFrequencyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFrequencyDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CFrequencyDialog message handlers


void CFrequencyDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	theApp.m_frequency = m_frequency;
}
