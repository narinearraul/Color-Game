
// testSDI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "testSDI.h"
#include "MainFrm.h"
#include "rulesDlg.h"
#include "CresultDlg.h"
#include "testSDIDoc.h"
#include "testSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CtestSDIApp

BEGIN_MESSAGE_MAP(CtestSDIApp, CWinApp) //changed from CWinAppEx
	ON_COMMAND(ID_APP_ABOUT, &CtestSDIApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_HELP_HOWTOPLAY, &CtestSDIApp::OnHelpHowtoplay)
END_MESSAGE_MAP()


// CtestSDIApp construction

CtestSDIApp::CtestSDIApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
//	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("testSDI.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CtestSDIApp object

CtestSDIApp theApp;


// CtestSDIApp initialization

BOOL CtestSDIApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CtestSDIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CtestSDIView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

int CtestSDIApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CtestSDIApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
//BEGIN_MESSAGE_MAP(rulesDlg, CDialogEx)
//END_MESSAGE_MAP()

// App command to run the dialog
void CtestSDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CtestSDIApp customization load/save methods

void CtestSDIApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CtestSDIApp::LoadCustomState()
{
}

void CtestSDIApp::SaveCustomState()
{
}

// CtestSDIApp message handlers


// C:\Users\Narine\Documents\HW\CSIT\CSIT861\testSDI\testSDI\testSDI.cpp : implementation file
//

#include "stdafx.h"
#include "testSDI.h"
#include "C:\Users\Narine\Documents\HW\CSIT\CSIT861\testSDI\testSDI\testSDI.h"
#include "afxdialogex.h"


// CRulesDlg dialog
//class CRulesDlg : public CDialogEx
//{
//	public:
//		CRulesDlg();
//
//	// Dialog Data
//		enum { IDD2 = IDD_HELP_HOWTOPLAY };
//
//	protected:
//		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//	// Implementation
//	protected:
//		DECLARE_MESSAGE_MAP()
//	public:
//}
IMPLEMENT_DYNAMIC(CRulesDlg, CDialogEx)

CRulesDlg::CRulesDlg(CWnd* pParent /*=NULL*/):CDialogEx(CRulesDlg::IDD2, pParent)
{

}

CRulesDlg::~CRulesDlg()
{
}

void CRulesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_ManagedControl(pDX, IDD_RULESDLG, d_Rules); //CN //associating the hosted control with the static MFC
}


BEGIN_MESSAGE_MAP(CRulesDlg, CDialogEx)
	ON_COMMAND(ID_HELP_HOWTOPLAY, &CRulesDlg::OnHelpHowtoplay)
END_MESSAGE_MAP()

void CtestSDIApp::OnHelpHowtoplay()
{
	rulesDlg testdlg;
    testdlg.DoModal();
	// TODO: Add your command handler code here
}
// CRulesDlg message handlers


void CRulesDlg::OnHelpHowtoplay()
{
	rulesDlg testdlg;
    testdlg.DoModal();
	// TODO: Add your command handler code here
}


INT_PTR CRulesDlg::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::DoModal();
}
