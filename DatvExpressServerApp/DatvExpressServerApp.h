
// DatvExpressServerApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "express.h"

typedef enum{FEC_12=FEC_RATE_12, FEC_23=FEC_RATE_23, FEC_34=FEC_RATE_34, FEC_56=FEC_RATE_56, FEC_78=FEC_RATE_78}Fectype;

// CDatvExpressServerAppApp:
// See DatvExpressServerApp.cpp for the implementation of this class
//

class CDatvExpressServerAppApp : public CWinApp
{
// Express database
public:
	DWORD   m_frequency;
	DWORD   m_symbol_rate;
	UINT    m_level;
	UINT    m_fec;
	// IP port configuration 
	CString  m_ip_local;
	CString  m_ip_remote;
	CString  m_ip_multicast;
	UINT     m_ip_port;
	BOOL     m_multicast;
	//
	LONG    m_tox_timeout;
	INT     m_i_offset;
	INT     m_q_offset;
	BOOL    m_threads;
	CString m_status_s;
	BOOL    m_status_tx;
	void OnTransmit( BOOL );
	BOOL IsTransmit(void);
	void OnCarrier( BOOL );
	void IDCOffsetUpdate( int );
	void QDCOffsetUpdate( int );
	void LoadConfigurationFile(void);
	void SaveConfigurationFile(void);
	void DisplayStatusMessage(void);
	void LoadConfigFromDisk(void);
	void SaveConfigToDisk(void);
	void ConfigureExpress(void);
	void DeConfigureExpress(void);
public:
	CDatvExpressServerAppApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	afx_msg void OnConfigurationFrequency();
	afx_msg void OnConfigurationSymbolrate();
	afx_msg void OnConfigurationFec();
	afx_msg void OnConfigurationNetwork();
	afx_msg void OnConfigurationDcoffset();
	afx_msg void OnConfigurationTxlevel();
	afx_msg void OnConfigurationToxlevel();
};

extern CDatvExpressServerAppApp theApp;