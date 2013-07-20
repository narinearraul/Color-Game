
// testSDIView.h : interface of the CtestSDIView class
//
#if !defined(AFX_SQUARESVIEW_H__00156CED_BB17_11D2_A2FD_0000861BAE71__INCLUDED_)
#define AFX_SQUARESVIEW_H__00156CED_BB17_11D2_A2FD_0000861BAE71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CtestSDIView : public CView
{
protected: // create from serialization only
	
	CtestSDIView();
	DECLARE_DYNCREATE(CtestSDIView)
	

// Attributes
public:
	CtestSDIDoc* GetDocument() const;//
    bool IsDone();	
// Operations
public:
	
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CtestSDIView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnDisplayErrorMessage();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpHowtoplay();
};

#ifndef _DEBUG  // debug version in testSDIView.cpp
inline CtestSDIDoc* CtestSDIView::GetDocument() const
   { return reinterpret_cast<CtestSDIDoc*>(m_pDocument); }
#endif

#endif 
