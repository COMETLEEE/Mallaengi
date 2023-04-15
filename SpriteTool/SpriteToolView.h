
// SpriteToolView.h: CSpriteToolView 클래스의 인터페이스
//

#pragma once
#include <map>

using std::map;

class CSpriteToolDoc;

class CSpriteToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSpriteToolView() noexcept;
	DECLARE_DYNCREATE(CSpriteToolView)

// 특성입니다.
public:
	CSpriteToolDoc* GetDocument() const;

// 작업입니다.
public:
	CD2DSolidColorBrush* mWhiteBrush;
	CD2DSolidColorBrush* mBlackBrush;
	ID2D1StrokeStyle* mStrokeStyle;

	map<UINT, CD2DBitmap*> mImages;
	UINT mSelectedImageID;

	// Tree
	bool mbSelected;

	// Mouse
	bool mbIsLButtonDown;
	CPoint mPrevCursor;
	CPoint mCurrCursor;

	// Drag
	CRect mDragRect;
	bool mbIsDrag;

	// ETC
	CMainFrame* mMainFrame;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSpriteToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	void AddImage(UINT imageID, CString path);
	void SetImageID(UINT imageID);
	afx_msg void OnSpriteRegist();
	afx_msg void OnSelectCancle();
	afx_msg void OnUpdateSpriteRegist(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectCancle(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // SpriteToolView.cpp의 디버그 버전
inline CSpriteToolDoc* CSpriteToolView::GetDocument() const
   { return reinterpret_cast<CSpriteToolDoc*>(m_pDocument); }
#endif