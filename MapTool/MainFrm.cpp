
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MapTool.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SPLIT_COLUMN 350

// CSplitterX

BEGIN_MESSAGE_MAP(CSplitterX, CSplitterWnd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

LRESULT CSplitterX::OnNcHitTest(CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return HTNOWHERE;
}

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
	: mEditorView(nullptr)
	, mMiniMapView(nullptr)
	, mControlView(nullptr)
{

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!mWndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!mWndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!mWndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	mWndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	mWndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&mWndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// 윈도우를 좌/우로 2등분한다.
	BOOL ret = mWndSplitter.CreateStatic(this, 1, 2);

	// 2등분된 윈도우 중 왼쪽 윈도우를 상/하로 2등분한다.
	mSubSplitter.CreateStatic(&mWndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, mWndSplitter.IdFromRowCol(0, 0));

	// 분할된 윈도우에 각 View 클래스를 연결한다.
	mWndSplitter.CreateView(0, 1, RUNTIME_CLASS(Editor), 
	CSize(8000, 8000), pContext);
	mSubSplitter.CreateView(0, 0, RUNTIME_CLASS(MiniMap), CSize(0, 350), pContext);
	mSubSplitter.CreateView(1, 0, RUNTIME_CLASS(Control), CSize(0, 0), pContext);

	// 등록된 View 객체를 포인터 변수로 저장하여, 다른 View에서 접근할 때 사용한다.
	mEditorView = dynamic_cast<Editor*>(mWndSplitter.GetPane(0, 1));
	mMiniMapView = dynamic_cast<MiniMap*>(mSubSplitter.GetPane(0, 0));
	mControlView = dynamic_cast<Control*>(mSubSplitter.GetPane(1, 0));

	// Split Bar의 위치
	mWndSplitter.SetColumnInfo(0, SPLIT_COLUMN, 10);

	return ret;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기