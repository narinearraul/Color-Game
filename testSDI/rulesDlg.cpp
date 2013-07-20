// rulesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testSDI.h"
#include "rulesDlg.h"
#include "afxdialogex.h"


// rulesDlg dialog

IMPLEMENT_DYNAMIC(rulesDlg, CDialogEx)

rulesDlg::rulesDlg(CWnd* pParent /*=NULL*/): CDialogEx(rulesDlg::IDD, pParent)
{
	//rulesDlg();
	//enum { IDD = IDD_HELP_HOWTOPLAY};
	EnableAutomation();

}

rulesDlg::~rulesDlg()
{
}

void rulesDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void rulesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(rulesDlg, CDialogEx)
//	ON_COMMAND(ID_HELP_HOWTOPLAY, &rulesDlg::OnHelpHowtoplay)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(rulesDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IrulesDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {F92CE464-4637-4717-9FC9-C737526A6490}
static const IID IID_IrulesDlg =
{ 0xF92CE464, 0x4637, 0x4717, { 0x9F, 0xC9, 0xC7, 0x37, 0x52, 0x6A, 0x64, 0x90 } };

BEGIN_INTERFACE_MAP(rulesDlg, CDialogEx)
	INTERFACE_PART(rulesDlg, IID_IrulesDlg, Dispatch)
END_INTERFACE_MAP()


// rulesDlg message handlers

//
//void rulesDlg::OnHelpHowtoplay()
//{
//	rulesDlg testdlg;
//    testdlg.DoModal();
//	// TODO: Add your command handler code here
//}
