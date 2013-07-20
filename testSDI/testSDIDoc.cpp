
// testSDIDoc.cpp : implementation of the CtestSDIDoc class
//
#include <afxwin.h>
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "testSDI.h"
#endif
#include "CresultDlg.h"
#include "testSDIDoc.h"
#include "resource.h"
#include <propkey.h>
#include "rulesDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CtestSDIDoc

IMPLEMENT_DYNCREATE(CtestSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CtestSDIDoc) NC
    ON_COMMAND(ID_COLOR_RED, OnColorRed)
    ON_COMMAND(ID_COLOR_YELLOW, OnColorYellow)
    ON_COMMAND(ID_COLOR_GREEN, OnColorGreen)
    ON_COMMAND(ID_COLOR_CYAN, OnColorCyan)
    ON_COMMAND(ID_COLOR_BLUE, OnColorBlue)
    ON_COMMAND(ID_COLOR_WHITE, OnColorWhite)
    ON_UPDATE_COMMAND_UI(ID_COLOR_RED, OnUpdateColorRed)
    ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, OnUpdateColorYellow)
    ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, OnUpdateColorGreen)
    ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, OnUpdateColorCyan)
    ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, OnUpdateColorBlue)
    ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, OnUpdateColorWhite)
    //}}AFX_MSG_MAP
//	ON_COMMAND(ID_PICKACOLOR, &CtestSDIDoc::OnPickacolor)
//ON_UPDATE_COMMAND_UI(ID_PICKACOLOR, &CtestSDIDoc::OnUpdatePickacolor)
ON_COMMAND(ID_PICKACOLOR, &CtestSDIDoc::OnPickacolor)
//ON_COMMAND(ID_HELP_HOWTOPLAY, &CtestSDIDoc::OnHelpHowtoplay)
//ON_COMMAND(ID_HELP_HOWTOPLAY, &CtestSDIDoc::OnHelpHowtoplay)
END_MESSAGE_MAP()


// CtestSDIDoc construction/destruction

CtestSDIDoc::CtestSDIDoc()
{
	// TODO: add one-time construction code here

}

CtestSDIDoc::~CtestSDIDoc()
{
}

BOOL CtestSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here 
	////start NC
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			m_clrGrid[i][j] = RGB(255, 255, 255);
		}
	}
	m_clrCurrentColor = RGB(200,50,50);
	////end NC
	// (SDI documents will reuse this document)

	return TRUE;
}




// CtestSDIDoc serialization

void CtestSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					ar << m_clrGrid[i][j];
			ar << m_clrCurrentColor;
		}
		else
		{
			for (int i=0; i<4; i++)
				for (int j=0; j<4; j++)
					ar >> m_clrGrid[i][j];
			ar >> m_clrCurrentColor;
		}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CtestSDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CtestSDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CtestSDIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CtestSDIDoc diagnostics

#ifdef _DEBUG
void CtestSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////
// CtestSDIDoc commands
///// NC added Random number generator for color selection
int GetRandom(int high,int low)
 {
   time_t SeedTime;
   struct tm SeedDate;
   SeedTime = time(0);
   SeedDate = *localtime(&SeedTime);
   int FinalSeed = (int)SeedTime + SeedDate.tm_mday + (SeedDate.tm_mon+1) + (SeedDate.tm_year+1900);
   srand((unsigned int) FinalSeed);
 
   int Interval = high - low + 1;
   int RandomOffset = rand() % Interval;
   int RandomNumber = low + RandomOffset;
   return RandomNumber;
 }
/////// NC will pop up the color dialoge asking the user to pick a color
COLORREF colorC=RGB(0,0,0);
COLORREF g_rgbCustom[16] = {0};
void DoSelectColor(HWND hwnd)
{
    CHOOSECOLOR cc = {sizeof(CHOOSECOLOR)};

    cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
    cc.hwndOwner = hwnd;
    cc.rgbResult = colorC;
    cc.lpCustColors = g_rgbCustom;

    if(ChooseColor(&cc))
    {
        colorC = cc.rgbResult;
    }
    InvalidateRect(hwnd, NULL,FALSE);
}
////////////////////////////////////////////////////////////
//NC returns the random or user picked color to the onLButton function to change 
//the color of  the correst
COLORREF CtestSDIDoc::GetCurrentColor()
{
	//HWND hwnd = NULL;
	if (colorC==RGB(0,0,0))
	{
	    //AfxMessageBox(_T("Select a color from the menu first!!!"));
		OnColorWhite() ;
	}
	else
	m_clrCurrentColor = colorC;
	return m_clrCurrentColor;
	//DoSelectColor(hwnd);
	//return colorC;
}

COLORREF CtestSDIDoc::GetSquare(int i, int j)
{
    ASSERT (i >= 0 && i <= 3 && j >= 0 && j <= 3);
    return m_clrGrid[i][j];
}

void CtestSDIDoc::SetSquare(int i, int j, COLORREF color)
{    
	if (m_clrGrid[i][j] == RGB (255, 255, 255))
	{
		ASSERT (i >= 0 && i <= 3 && j >= 0 && j <= 3);
		m_clrGrid[i][j] = color;
		m_clrCurrentColor = color;
		SetModifiedFlag (TRUE);
		UpdateAllViews (NULL);
	}
	/*else
    	AfxMessageBox(_T("This Square has already been used! Pick another square!"));*/
}


void CtestSDIDoc::UserMoves() 
{
}

void CtestSDIDoc::SelectSquare(int& iPos, int& jPos)
{	
	int iP = iPos;
	int jP = jPos;
	m_CompColor = RGB(0,0,0);
	int choice = GetRandom(1,0);
	switch(choice)
	{
		case 0:
			{
			bool gotIt1 = false;
			bool gotIt2 = false;

			for (int j=0; j<4; j++)
						{
							if(m_clrGrid[iPos][j] ==  RGB (255, 255, 255))
								{
									//iPos = i;
									jPos = j;
									gotIt1 = true;
								}						
						}
			if (!gotIt1)
			{
				for (int i=0; i<4; i++)
						{
					if(m_clrGrid[i][jPos] ==  RGB (255, 255, 255))
						{
							iPos = i;
							//jPos = j;
							gotIt2 = true;
						}			
					}			
			}
	
			if (!gotIt1 && !gotIt2)
			{
					for (int i=0; i<4; i++)
						{
							for (int j=0; j<4; j++)
							{
								if(m_clrGrid[i][j] ==  RGB (255, 255, 255))
								{
									iPos = i;
									jPos = j;
								}									
							}
						}		
			}
			}break;
	case 1:
			{
			bool gotIt1 = false;
			bool gotIt2 = false;

			for (int i=0; i<4; i++)
				{
					if(m_clrGrid[i][jPos] ==  RGB (255, 255, 255))
						{
							iPos = i;
							//jPos = j;
							gotIt1 = true;
						}						
				}
			if (!gotIt1)
			{
				for (int j=0; j<4; j++)
					{
						if(m_clrGrid[iPos][j] ==  RGB (255, 255, 255))
						{
									//iPos = i;
									jPos = j;
							gotIt2 = true;
						}			
					}			
			}
	
			if (!gotIt1 && !gotIt2)
			{
					for (int i=0; i<4; i++)
						{
							for (int j=0; j<4; j++)
							{
								if(m_clrGrid[i][j] ==  RGB (255, 255, 255))
								{
									iPos = i;
									jPos = j;
								}									
							}
						}		
			}
			}break;
	}		
}
//mixed up version of SelectSquare: didn't quite workout
//void CtestSDIDoc::SelectSquare(int& iPos, int& jPos)
//{
//	m_CompColor = RGB(0,0,0);
//	int choice = GetRandom(2,0);
//	switch(choice)
//	{
//		case 0:
//			{
//				for (int i=0; i<4; i++)
//				{
//					if(m_clrGrid[i][jPos] ==  RGB (255, 255, 255))
//						{
//							iPos = i;
//							//jPos = j;
//							//SetSquare(iPos, jPos, m_CompColor);
//						}
//					//else
//					//{
//					//	for (int j=0; j<4; j++)
//					//	{
//					//		if(m_clrGrid[iPos][j] ==  RGB (255, 255, 255))
//					//			{
//					//				//iPos = i;
//					//				jPos = j;
//					//				//SetSquare(iPos, jPos, m_CompColor);
//					//				break;
//					//			}		
//					//	}
//					//}
//				}
//			}				
//			break;					
//		case 1:
//			{
//				for (int j=0; j<4; j++)
//				{
//					if(m_clrGrid[iPos][j] ==  RGB (255, 255, 255))
//						{
//							//iPos = i;
//							jPos = j;
//							//SetSquare(iPos, jPos, m_CompColor);					
//					}				
//				//else
//				//{
//				//	for (int i=0; i<4; i++)
//				//    {
//				//		if(m_clrGrid[i][jPos] ==  RGB (255, 255, 255))
//				//			{
//				//			iPos = i;
//				//			//SetSquare(iPos, jPos, m_CompColor);
//				//			//jPos = j;
//				//			break;
//				//			}
//				//		}
//				//	}
//				}		
//			}break;		
//		case 2:
//			{
//				if(m_clrGrid[iPos][jPos] ==  RGB (255, 255, 255))
//			{
//				for (int i=0; i<4; i++)
//					{
//						for (int j=0; j<4; j++)
//						{
//							if(m_clrGrid[i][j] ==  RGB (255, 255, 255))
//							{
//								iPos = i;
//								jPos = j;
//							}									
//						}
//					}		
//			}
//			}break;
//	}	
//}

void CtestSDIDoc::ComputerMoves(int rndi, int rndj)
{	
	m_CompColor = RGB(0,0,0);
	/*do
	{*/
		SelectSquare(rndi, rndj);			
	if (m_clrGrid[rndi][rndj] ==  RGB (255, 255, 255))
	//				{
	//					int random = GetRandom(5,1); //generated number is used to pick a nubmer from 6 colors
	//						switch(random)
	//						{
	//							case 1:	OnColorRed();
	//								break;
	//							case 2: OnColorYellow();
	//								break;
	//							case 3: OnColorGreen();
	//								break;
	//							case 4: OnColorCyan();
	//								break;
	//							case 5: OnColorBlue();
	//								break;								
	//						}												
	//				}					
	//}while(m_clrGrid[rndi][rndj] !=  RGB (255, 255, 255));
	SetSquare(rndi, rndj, m_CompColor);	
}
void CtestSDIDoc::OnColorRed() 
{
    m_clrCurrentColor = RGB (255, 0, 0);    
}

void CtestSDIDoc::OnColorYellow() 
{
    m_clrCurrentColor = RGB (255, 255, 0);    
}

void CtestSDIDoc::OnColorGreen() 
{
    m_clrCurrentColor = RGB (0, 255, 0);    
}

void CtestSDIDoc::OnColorCyan() 
{
    m_clrCurrentColor = RGB (0, 255, 255);    
}

void CtestSDIDoc::OnColorBlue() 
{
    m_clrCurrentColor = RGB (0, 0, 255);    
}

void CtestSDIDoc::OnColorWhite() 
{
    m_clrCurrentColor = RGB (255, 255, 255);    
}

void CtestSDIDoc::OnUpdateColorRed(CCmdUI* pCmdUI) 
{
    pCmdUI->SetRadio (m_clrCurrentColor == RGB (255, 0, 0));    
}

void CtestSDIDoc::OnUpdateColorYellow(CCmdUI* pCmdUI) 
{
    pCmdUI->SetRadio (m_clrCurrentColor == RGB (255, 255, 0));    
}

void CtestSDIDoc::OnUpdateColorGreen(CCmdUI* pCmdUI) 
{
    pCmdUI->SetRadio (m_clrCurrentColor == RGB (0, 255, 0));    
}

void CtestSDIDoc::OnUpdateColorCyan(CCmdUI* pCmdUI) 
{
    pCmdUI->SetRadio (m_clrCurrentColor == RGB (0, 255, 255));    
}

void CtestSDIDoc::OnUpdateColorBlue(CCmdUI* pCmdUI) 
{
    pCmdUI->SetRadio (m_clrCurrentColor == RGB (0, 0, 255));    
}

void CtestSDIDoc::OnUpdateColorWhite(CCmdUI* pCmdUI) 
{
    pCmdUI->SetRadio (m_clrCurrentColor == RGB (255, 255, 255));    
}

void CtestSDIDoc::Results(/*int& userWon, int& compW*/)
{
	int userWon = 0;
	int compW = 0;
	if((m_clrGrid[0][0] == colorC) &&  (m_clrGrid[0][1] == colorC) &&
	   (m_clrGrid[0][2] == colorC) &&  (m_clrGrid[0][3] == colorC))
	{
		userWon++;
		//AfxMessageBox(_T ("The User won "));		
	}
	if((m_clrGrid[1][0] ==  colorC) && 	   (m_clrGrid[1][1] ==  colorC) &&
	   (m_clrGrid[1][2] ==  colorC) && 	   (m_clrGrid[1][3] ==  colorC))
	{
		//AfxMessageBox(_T ("The User won "));
		userWon++;
	}
	if((m_clrGrid[2][0] ==  colorC) &&     (m_clrGrid[2][1] ==  colorC) &&
	   (m_clrGrid[2][2] ==  colorC) &&	   (m_clrGrid[2][3] ==  colorC))
	{
		//AfxMessageBox(_T ("The User won "));
		userWon++;
	}
	if((m_clrGrid[3][0] ==  colorC) && 	   (m_clrGrid[3][1] ==  colorC) &&
	   (m_clrGrid[3][2] ==  colorC) &&	   (m_clrGrid[3][3] ==  colorC))
	{
		//AfxMessageBox(_T ("The User won "));
		userWon++;
	}
	if((m_clrGrid[0][0] ==  colorC) && 	   (m_clrGrid[1][0] ==  colorC) &&
	   (m_clrGrid[2][0] ==  colorC) &&	   (m_clrGrid[3][0] ==  colorC))
	{
		//AfxMessageBox(_T ("The User won "));
		userWon++;
	}
	if((m_clrGrid[0][1] ==  colorC) &&	   (m_clrGrid[1][1] ==  colorC) &&
	   (m_clrGrid[2][1] ==  colorC) &&	   (m_clrGrid[3][1] ==  colorC))
	{
		//AfxMessageBox(_T ("The User won "));
		userWon++;
	}
	if((m_clrGrid[0][2] ==  colorC) &&	   (m_clrGrid[1][2] ==  colorC) &&
	   (m_clrGrid[2][2] ==  colorC) &&	   (m_clrGrid[3][2] ==  colorC))
	{
		//AfxMessageBox(_T ("The User won "));
		userWon++;
	}
	if((m_clrGrid[0][3] ==  colorC) &&	   (m_clrGrid[1][3] ==  colorC) &&
	   (m_clrGrid[2][3] ==  colorC) &&	   (m_clrGrid[3][3] ==  colorC))
	{		userWon++;	}

	
		/*if (userWon > 0)
		{
			AfxMessageBox(_T ("The User won "));
		}*/
		ComputerWon(compW);
		CresultDlg ResDlg;
		ResDlg.SetData(userWon,compW);
		ResDlg.DoModal();

		/*char c[10];
			_itoa(userWon,c,10);
			CString MFCString;
			MFCString = c;
	
			MessageBox(NULL,
				L"The Score for the user is: \t ",
				L"Color Squares Results",
				MB_OK | MB_ICONINFORMATION); 
			AfxMessageBox(MFCString);*/
	
	/*	if (ComputerWon(compW))
		{
				AfxMessageBox(_T ("The Computer Won "));	
		}			
		char a[10];
		_itoa(compW,a,10);
		CString MFCString1;
		MFCString1 = a;
	
		MessageBox(NULL,
			L"The Score for the computer is: \t ",
			L"Color Squares Results",
			MB_OK | MB_ICONINFORMATION); 
		AfxMessageBox(MFCString1);*/	
}


bool CtestSDIDoc::ComputerWon(int& computerWon)
{
	computerWon = 0;
	if((m_clrGrid[0][0] != colorC) &&  (m_clrGrid[0][1] != colorC) &&
	   (m_clrGrid[0][2] != colorC) &&  (m_clrGrid[0][3] != colorC))
	{
		computerWon++;
		return true;
	}
	if((m_clrGrid[1][0] !=  colorC) && 	   (m_clrGrid[1][1] !=  colorC) &&
	   (m_clrGrid[1][2] !=  colorC) && 	   (m_clrGrid[1][3] !=  colorC))
	{
		computerWon++;
		return true;		
	}
	if((m_clrGrid[2][0] !=  colorC) &&     (m_clrGrid[2][1] !=  colorC) &&
	   (m_clrGrid[2][2] !=  colorC) &&	   (m_clrGrid[2][3] !=  colorC))
	{
		computerWon++;
		return true;		
	}
	if((m_clrGrid[3][0] !=  colorC) && 	   (m_clrGrid[3][1] !=  colorC) &&
	   (m_clrGrid[3][2] !=  colorC) &&	   (m_clrGrid[3][3] !=  colorC))
	{
		computerWon++;
		return true;		
	}
	if((m_clrGrid[0][0] !=  colorC) && 	   (m_clrGrid[1][0] !=  colorC) &&
	   (m_clrGrid[2][0] !=  colorC) &&	   (m_clrGrid[3][0] !=  colorC))
	{
		computerWon++;
		return true;		
	}
	if((m_clrGrid[0][1] !=  colorC) &&	   (m_clrGrid[1][1] !=  colorC) &&
	   (m_clrGrid[2][1] !=  colorC) &&	   (m_clrGrid[3][1] !=  colorC))
	{
		computerWon++;
		return true;
	}
	if((m_clrGrid[0][2] !=  colorC) &&	   (m_clrGrid[1][2] !=  colorC) &&
	   (m_clrGrid[2][2] !=  colorC) &&	   (m_clrGrid[3][2] !=  colorC))
	{
		computerWon++;
		return true;
	}
	else
		return false;
	if((m_clrGrid[0][3] !=  colorC) &&	   (m_clrGrid[1][3] !=  colorC) &&
	   (m_clrGrid[2][3] !=  colorC) &&	   (m_clrGrid[3][3] !=  colorC))
	{		
		computerWon++; 
		return true;
	}
	else 
		return false;
}
void CtestSDIDoc::OnPickacolor()
{
	HWND hwnd = NULL;
	DoSelectColor(hwnd);
	// TODO: Add your command handler code here
}