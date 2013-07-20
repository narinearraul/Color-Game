// CresultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testSDI.h"
#include "CresultDlg.h"
#include "afxdialogex.h"
#include "testSDIDoc.h"


// CresultDlg dialog

IMPLEMENT_DYNAMIC(CresultDlg, CDialogEx)

CresultDlg::CresultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CresultDlg::IDD, pParent)
{
	
}

void CresultDlg::SetData(int uWin, int cWin)
{
	d_user = uWin; 
	d_computer = cWin;
}


CresultDlg::~CresultDlg()
{
}

void CresultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//   DDX_CONTROL(pDX, IDC_USER_SCORE, d_u_W);
	//   DDX_CONTROL(pDX, IDC_COMP_SCORE, d_c_W);
	//   DDX_CONTROL(pDX, IDC_WINNER, d_Winner);

	//  DDX_Control(pDX, IDC_COMP_SCORE, m_u_win);
	DDX_Control(pDX, IDC_COMP_SCORE, m_c_win);
	DDX_Control(pDX, IDC_USER_SCORE, m_u_win);
	DDX_Control(pDX, IDC_WINNER, m_winner);
}


BEGIN_MESSAGE_MAP(CresultDlg, CDialogEx)
END_MESSAGE_MAP()


// CresultDlg message handlers


BOOL CresultDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	CString userS, compS;
	compS = d_computer.ToString();
	userS = d_user.ToString();
	m_c_win.SetWindowText(compS);
	m_u_win.SetWindowText(userS);

	if(d_computer > d_user)
		winner = "THE COMPUTER HAS WON";
	else if (d_user > d_computer)
		winner = "THE USER HAS WON!!!";
	else
		winner = "IT IS A DRAW!!!";

	
	m_winner.SetWindowText(winner);
	return true;
}
