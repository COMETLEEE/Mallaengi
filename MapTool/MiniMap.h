#pragma once


// MiniMap 보기

/// <summary>
/// Editor View의 작업 내용을 축소해서 보여주는 Mini Map View
/// 
/// 2022. 02. 08 JK
/// </summary>
class MiniMap : public CView
{
	DECLARE_DYNCREATE(MiniMap)

	enum class eEventMessage
	{
		REDRAW = 0,
		LASTOFENUM
	};

protected:
	MiniMap();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~MiniMap();

#pragma region MyVariable
	// Resources
	map<UINT, CD2DBitmap*> mImages;	// Image Resource

	// Brush
	CD2DSolidColorBrush* mWhiteBrush;
	CD2DSolidColorBrush* mBlackBrush;

	// Minimap Rect
	CRect mMiniMapSize;
	CRect mShowRect;

	// ETC
	CMainFrame* mMainFrame;
	bool mbMiniMapDrag;
#pragma endregion

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

#pragma region MyFunction
private:
	void CreateD2D();

public:
	HRESULT AddImage(UINT imageID, CString path);

	CRect& MiniMapSizeProp();
#pragma endregion


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	// 마우스
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};