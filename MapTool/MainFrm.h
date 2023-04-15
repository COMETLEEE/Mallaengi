
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class MiniMap;
class Editor;
class Control;

/// <summary>
///	CSplitterWnd 클래스를 상속 받고 OnNcHitTest 함수를 이용하여
/// FormView의 Scroll Bar 생성을 강제적으로 막기 위한 클래스.
/// 
/// 2022. 02. 07 JK
/// </summary>
class CSplitterX : public CSplitterWnd
{
public:
	CSplitterX() {};
	~CSplitterX() {};

public:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

/// <summary>
/// MFC 프로젝트 생성시 기본으로 제공되는 MainFrame 클래스
/// 화면을 분할하고 분할된 화면에 각 View Class를 적용시키는 작업을 진행한다.
/// 
/// 2022. 02. 07 JK
/// </summary>
class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
protected:
	// 화면 분할을 위해 사용되는 변수
	CSplitterX mWndSplitter;
	CSplitterX mSubSplitter;

// 작업입니다.
public:
	Editor* mEditorView;
	MiniMap* mMiniMapView;
	Control* mControlView;
	
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          mWndToolBar;
	CStatusBar        mWndStatusBar;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

};