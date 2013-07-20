#pragma once


// rulesDlg dialog

class rulesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(rulesDlg)

public:
	rulesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~rulesDlg();

	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_RULESDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	//afx_msg void OnHelpHowtoplay();
};
