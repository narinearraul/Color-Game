
// testSDIView.cpp : implementation of the CtestSDIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "testSDI.h"
#endif

#include "rulesDlg.h"
#include "testSDIDoc.h"
#include "testSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CtestSDIView

IMPLEMENT_DYNCREATE(CtestSDIView, CView)

BEGIN_MESSAGE_MAP(CtestSDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtestSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//OnDisplayErrorMessage()
	ON_COMMAND(ID_HELP_HOWTOPLAY, &CtestSDIView::OnHelpHowtoplay)
END_MESSAGE_MAP()

// CtestSDIView construction/destruction

CtestSDIView::CtestSDIView()
{
	// TODO: add construction code here

}

CtestSDIView::~CtestSDIView()
{
}

BOOL CtestSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CtestSDIView drawing

void CtestSDIView::OnDraw(CDC* pDC)
{
	CtestSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->SetMapMode (MM_LOENGLISH);
	// TODO: add draw code for native data here
	 for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            COLORREF color = pDoc->GetSquare (i, j);
            CBrush brush (color);
            int x1 = (j * 100) + 50;
            int y1 = (i * -100) - 50;
            int x2 = x1 + 100;
            int y2 = y1 - 100;
            CRect rect (x1, y1, x2, y2);
            pDC->FillRect (rect, &brush);
        }
    }

	 for (int x=50; x<=450; x+=100) {
        pDC->MoveTo (x, -50);
        pDC->LineTo (x, -450);
    }

    for (int y=-50; y>=-450; y-=100) {
        pDC->MoveTo (50, y);
        pDC->LineTo (450, y);
    }

	//pDC->TextOut(100, 500, "HELLO");
}


// CtestSDIView printing


void CtestSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtestSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CtestSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CtestSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CtestSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtestSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtestSDIView diagnostics

#ifdef _DEBUG
void CtestSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CtestSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestSDIDoc* CtestSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestSDIDoc)));
	return (CtestSDIDoc*)m_pDocument;
}
#endif //_DEBUG

bool CtestSDIView::IsDone()
{
	CtestSDIDoc* pDoc = GetDocument();
	for (int i=0; i<4; i++)
				{
					for (int j=0; j<4; j++)
					{
						if(pDoc->m_clrGrid[i][j] ==  RGB (255, 255, 255))
						{
							return false;
						}
						
					}
				}		
	return true;
}


// CtestSDIView message handlers
void CtestSDIView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CView::OnLButtonDown(nFlags, point);	
	CClientDC dc (this);
    dc.SetMapMode (MM_LOENGLISH);
    CPoint pos = point;
    dc.DPtoLP (&pos);	
	/*int uW = 0;
	int cW = 0;*/
    // If a square was clicked, set its color to the current color.
    //
	
  if (pos.x >= 50 && pos.x <= 450 && pos.y <= -50 && pos.y >= -450) 
	 {
        int i = (-pos.y - 50) / 100;
        int j = (pos.x - 50) / 100;
        CtestSDIDoc* pDoc = GetDocument();
        COLORREF clrCurrentColor = pDoc->GetCurrentColor();
		if (clrCurrentColor == RGB (255, 255, 255) || clrCurrentColor == RGB (0, 0, 0))
			AfxMessageBox(_T("Select a color from the menu first!!!"));
		if(!IsDone())
		{
				if (pDoc->m_clrGrid[i][j] != RGB (255, 255, 255))
				{
					if(IsDone())
						Sleep(0);
					else
					AfxMessageBox(_T("This Square has already been used! Pick another square!"));
				}
				else if (pDoc->m_clrGrid[i][j] == RGB (255, 255, 255))
				{
					pDoc->SetSquare (i, j, clrCurrentColor);
					if(IsDone())
						{
							AfxMessageBox(_T("Out of MOVES! Generating Results!"));
							//pDoc->Results();	
							//Sleep(0);  // yield					
						}	
     				//AfxMessageBox(_T("Please wait till The computer is makes a move..."));
					pDoc->ComputerMoves(i,j); 
				}				
				
		}
			if(IsDone())	pDoc->Results(/*uW,cW*/);
  }
}

void CtestSDIView::OnHelpHowtoplay()
{
	rulesDlg testdlg;
    testdlg.DoModal();
	// TODO: Add your command handler code here
}
