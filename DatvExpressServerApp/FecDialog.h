#pragma once


// CFecDialog dialog

class CFecDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFecDialog)

public:
	CFecDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFecDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_FEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_fec_button;
	afx_msg void OnBnClickedOk();
};
