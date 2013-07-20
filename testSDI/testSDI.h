
// testSDI.h : main header file for the testSDI application
//
#if !defined(AFX_SDISQUARES_H__00156CE5_BB17_11D2_A2FD_0000861BAE71__INCLUDED_)
#define AFX_SDISQUARES_H__00156CE5_BB17_11D2_A2FD_0000861BAE71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "afxwin.h"
#endif // _MSC_VER > 1000
#ifndef __AFXWIN_H__
    #error include `stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CtestSDIApp:
// See testSDI.cpp for the implementation of this class
//

class CtestSDIApp : public CWinAppEx
{
public:
	CtestSDIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnHelpHowtoplay();
};

extern CtestSDIApp theApp;

#endif#pragma once


// CRulesDlg dialog

class CRulesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRulesDlg)

public:
	CRulesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRulesDlg();

// Dialog Data
	enum { IDD2 = IDD_RULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//CWinFormsControl<System::Windows::Form::ShowDialog()>d_Rules; //creating the Winforms control //CN
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpHowtoplay();
	virtual INT_PTR DoModal();
};
