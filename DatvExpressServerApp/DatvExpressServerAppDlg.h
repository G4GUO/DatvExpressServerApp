
// DatvExpressServerAppDlg.h : header file
//

#pragma once


// CDatvExpressServerAppDlg dialog
class CDatvExpressServerAppDlg : public CDialogEx
{
// Construction
public:
	CDatvExpressServerAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DATVEXPRESSSERVERAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void UpdateDialogTextControls();
	void DisplayStatusMessage( void );
	BOOL m_transmit;
	afx_msg void OnBnClickedCheckCarrier();
	BOOL m_carrier;
	afx_msg void OnClickedCheckTox();
	BOOL m_tox;
	afx_msg void OnClickedButtonPtt();
};
