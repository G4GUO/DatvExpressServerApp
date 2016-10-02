#pragma once


// CToxLevelDialog dialog

class CToxLevelDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CToxLevelDialog)

public:
	CToxLevelDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CToxLevelDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_TOX_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_tox_timeout;
	afx_msg void OnBnClickedOk();
};
