#pragma once


// COffsetDialog dialog

class COffsetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(COffsetDialog)

public:
	COffsetDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~COffsetDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_DC_OFFSET_BALANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_i_val;
	int m_q_val;
	afx_msg void OnNMCustomdrawSliderI(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderQ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTRBNThumbPosChangingSliderQ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderQ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderI(NMHDR *pNMHDR, LRESULT *pResult);
};
