#pragma once

class CMainFrame;


// AnimationButton 대화 상자

class AnimationButton : public CDialog
{
	DECLARE_DYNAMIC(AnimationButton)

	enum class eButtonState
	{
		Pivot,
		Collider
	};

public:
	AnimationButton(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AnimationButton();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Animation_Button };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	bool mbOnPlay;
	bool mbPivot;
	bool mbCollider;
	afx_msg void OnBnClickedPlaybutton();
	afx_msg void OnBnClickedStopbutton();
	CComboBoxEx mInputStateBox;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeStateBox();
	afx_msg void OnDestroy();
};

// AnimationView

class CAnimationViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class AnimationView : public CDockablePane
{
	DECLARE_DYNAMIC(AnimationView)

public:
	AnimationView() noexcept;

	void AdjustLayout();
	void OnChangeVisualStyle();

	virtual ~AnimationView();

	CAnimationViewToolBar mWndToolBar;
	CD2DSolidColorBrush* mBlackBrush;
	ID2D1StrokeStyle* mStrokeStyle;

	AnimationButton mAnimationButton;

	map<UINT, CD2DBitmap*> mImages;
	UINT mSpriteID;

	CPoint mCenter;

	CMainFrame*	mMainFrame;

	// Mouse
	bool mbIsLButtonDown;
	CPoint mPrevCursor;
	CPoint mCurrCursor;

	// Drag
	CRect mDragRect;
	bool mbIsDrag;

	// ETC
	INT mToolBarHeight;
	UINT mDeltaTime;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	void SetTargetSprite(UINT spriteID);
	void AddImage(UINT imageName, CString path);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	void CalcDeltaTime();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};