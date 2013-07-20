#pragma once

#include "afxwin.h"

// CresultDlg dialog

class CresultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CresultDlg)

public:
	CresultDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CresultDlg();
	int d_user; 
	int d_computer;
	CString winner;
	/*CEdit d_u_W; //the wizard will do this :)
	CEdit d_c_W;
	CEdit d_Winner;*/
	void SetData(int, int);
// Dialog Data
	enum { IDD = IDD_RESULT_SUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_c_win;
	CEdit m_u_win;
	CStatic m_winner;
protected:
	virtual BOOL OnInitDialog();
};
