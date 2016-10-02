#pragma once
#include "afxwin.h"


// CNetworkDialog dialog

class CNetworkDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNetworkDialog)

public:
	CNetworkDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNetworkDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_NETWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	int m_port;
public:
	virtual BOOL OnInitDialog();
	CEdit m_remote_ip;
	CComboBox m_local_ip;
	CString m_remote_ip_s;
	CString m_multicast_ip_s;
	BOOL m_multicast_enable;
	CButton m_multicast_on;
	CEdit m_multicast_ip;
	afx_msg void OnClickedCheckMulticast();
};
