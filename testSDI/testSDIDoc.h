
// testSDIDoc.h : interface of the CtestSDIDoc class
//
#if !defined(AFX_SQUARESDOC_H__00156CEB_BB17_11D2_A2FD_0000861BAE71__INCLUDED_)
#define AFX_SQUARESDOC_H__00156CEB_BB17_11D2_A2FD_0000861BAE71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CtestSDIDoc : public CDocument
{
protected: // create from serialization only
	CtestSDIDoc();

	DECLARE_DYNCREATE(CtestSDIDoc)
	#define ID_COLOR_RED                  32774 //added from another source NC whew
	#define ID_COLOR_YELLOW                 32775
	#define ID_COLOR_GREEN                  32776
	#define ID_COLOR_CYAN                   32777
	#define ID_COLOR_BLUE                   32778
	#define ID_COLOR_WHITE					32776
// Attributes
public:
	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	void SetSquare(int i, int j, COLORREF color); //NC
	void ComputerMoves(int i, int j);
	void UserMoves();
	void SelectSquare(int& i, int& j);
	void Results(/*int& userScore, int& compScore*/);
	bool ComputerWon(int& count);	
	COLORREF GetSquare (int i, int j);
	COLORREF GetCurrentColor();
	virtual ~CtestSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public: //changed to public NC
	//{{AFX_MSG(CSquaresDoc) NC
	COLORREF m_clrGrid[4][4]; //NC 
	COLORREF m_clrCurrentColor; //NC
	COLORREF m_CompColor;// = RGB(0,0,0);
	afx_msg void OnColorRed();
    afx_msg void OnColorYellow();
    afx_msg void OnColorGreen();
    afx_msg void OnColorCyan();
    afx_msg void OnColorBlue();
    afx_msg void OnColorWhite();
    afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorYellow(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorCyan(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorWhite(CCmdUI* pCmdUI);
    //}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()


#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


#endif
	afx_msg void OnPickacolor();
	//afx_msg void OnHelpHowtoplay();
	afx_msg void OnHelpHowtoplay();
};
