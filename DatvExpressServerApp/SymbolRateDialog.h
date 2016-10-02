#pragma once


// CSymbolRateDialog dialog

class CSymbolRateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSymbolRateDialog)

public:
	CSymbolRateDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSymbolRateDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SYMBOL_RATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	DWORD m_symbol_rate;
};
