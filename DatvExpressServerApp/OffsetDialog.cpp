// OffsetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DatvExpressServerApp.h"
#include "OffsetDialog.h"
#include "afxdialogex.h"


// COffsetDialog dialog

IMPLEMENT_DYNAMIC(COffsetDialog, CDialogEx)

COffsetDialog::COffsetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(COffsetDialog::IDD, pParent)
	, m_i_val(0)
	, m_q_val(0)
{
	m_i_val = theApp.m_i_offset + 50;
	m_q_val = theApp.m_q_offset + 50;
}

COffsetDialog::~COffsetDialog()
{
}

void COffsetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_I, m_i_val);
	DDV_MinMaxInt(pDX, m_i_val, 0, 100);
	DDX_Slider(pDX, IDC_SLIDER_Q, m_q_val);
	DDV_MinMaxInt(pDX, m_q_val, 0, 100);
}


BEGIN_MESSAGE_MAP(COffsetDialog, CDialogEx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_Q, &COffsetDialog::OnNMReleasedcaptureSliderQ)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_I, &COffsetDialog::OnNMReleasedcaptureSliderI)
END_MESSAGE_MAP()


// COffsetDialog message handlers

void COffsetDialog::OnNMReleasedcaptureSliderQ(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData();
	theApp.QDCOffsetUpdate( m_q_val - 50 );
	*pResult = 0;
}

void COffsetDialog::OnNMReleasedcaptureSliderI(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData();
	theApp.IDCOffsetUpdate(	m_i_val - 50 );
	*pResult = 0;
}
