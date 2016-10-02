#pragma once


// CFrequencyDialog dialog

class CFrequencyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFrequencyDialog)

public:
	CFrequencyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFrequencyDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_FREQUENCY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	DWORD m_frequency;
};
