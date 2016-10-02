#pragma once


// CTxLevelDlg dialog

class CTxLevelDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTxLevelDialog)

public:
	CTxLevelDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTxLevelDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_TX_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_tx_level;
	afx_msg void OnBnClickedOk();
};
