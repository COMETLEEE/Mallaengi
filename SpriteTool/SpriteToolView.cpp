
// SpriteToolView.cpp: CSpriteToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SpriteTool.h"
#endif

#include "SpriteToolDoc.h"
#include "SpriteToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpriteToolView

IMPLEMENT_DYNCREATE(CSpriteToolView, CView)

BEGIN_MESSAGE_MAP(CSpriteToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSpriteToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CSpriteToolView::OnDraw2D)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Sprite_Regist, &CSpriteToolView::OnSpriteRegist)
	ON_COMMAND(ID_Select_Cancle, &CSpriteToolView::OnSelectCancle)
	ON_UPDATE_COMMAND_UI(ID_Sprite_Regist, &CSpriteToolView::OnUpdateSpriteRegist)
	ON_UPDATE_COMMAND_UI(ID_Select_Cancle, &CSpriteToolView::OnUpdateSelectCancle)
END_MESSAGE_MAP()

// CSpriteToolView 생성/소멸

CSpriteToolView::CSpriteToolView() noexcept
	: mWhiteBrush(nullptr)
	, mBlackBrush(nullptr)
	, mStrokeStyle(nullptr)
	, mbSelected(false)
	, mbIsLButtonDown(false)
	, mPrevCursor{}
	, mCurrCursor{}
	, mDragRect{}
	, mbIsDrag(false)
	, mMainFrame(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

	EnableD2DSupport();

	mBlackBrush = new CD2DSolidColorBrush(
		GetRenderTarget(),
		D2D1::ColorF(D2D1::ColorF::Black));

	mWhiteBrush = new CD2DSolidColorBrush(
		GetRenderTarget(),
		D2D1::ColorF(D2D1::ColorF::White));

	D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_TRIANGLE,
		D2D1_LINE_JOIN_MITER, 10.0f,
		D2D1_DASH_STYLE_DASH_DOT_DOT, 0.0f);

	AfxGetD2DState()->GetDirect2dFactory()->CreateStrokeStyle(strokeStyleProperties, nullptr, 0, &mStrokeStyle);
}

CSpriteToolView::~CSpriteToolView()
{
}

BOOL CSpriteToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSpriteToolView 그리기

void CSpriteToolView::AddImage(UINT imageID, CString path)
{
	auto findResult = mImages.find(imageID);

	if (findResult == mImages.end())
		mImages[imageID] = new CD2DBitmap(GetRenderTarget(), path);
}

void CSpriteToolView::SetImageID(UINT imageID)
{
	mSelectedImageID = imageID;
	mbSelected = true;
}

void CSpriteToolView::OnDraw(CDC* /*pDC*/)
{
	CSpriteToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSpriteToolView 인쇄


void CSpriteToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSpriteToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSpriteToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSpriteToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSpriteToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSpriteToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSpriteToolView 진단

#ifdef _DEBUG
void CSpriteToolView::AssertValid() const
{
	CView::AssertValid();
}

void CSpriteToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpriteToolDoc* CSpriteToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpriteToolDoc)));
	return (CSpriteToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CSpriteToolView 메시지 처리기

afx_msg LRESULT CSpriteToolView::OnDraw2D(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* pRT = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(pRT);

	pRT->Clear(mWhiteBrush->GetColor());

	CRect clientRect;
	GetClientRect(&clientRect);

	if (mbSelected == true)
		pRT->DrawBitmap(mImages[mSelectedImageID], CRect(0, 0, mImages[mSelectedImageID]->GetSize().width, mImages[mSelectedImageID]->GetSize().height));

	if (mbIsLButtonDown == true)
		pRT->DrawRectangle(CRect(mPrevCursor.x, mPrevCursor.y, mCurrCursor.x, mCurrCursor.y), mBlackBrush, 1.0f, mStrokeStyle);
	else if (mbIsDrag == true)
		pRT->DrawRectangle(mDragRect, mBlackBrush, 1.0f, mStrokeStyle);

	return true;
}


void CSpriteToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	InvalidateRect(nullptr);

	CView::OnTimer(nIDEvent);
}


void CSpriteToolView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(0);
}

void CSpriteToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetTimer(0, 16, nullptr);

	mMainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);
}

void CSpriteToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	mPrevCursor = point;
	mbIsLButtonDown = true;

	CView::OnLButtonDown(nFlags, point);
}

void CSpriteToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (mbIsLButtonDown == true)
	{
		mbIsLButtonDown = false;

		if (abs(mPrevCursor.x - point.x) < 10 && abs(mPrevCursor.y - point.y) < 10)
		{
			mDragRect = {};
			mbIsDrag = false;
		}
		else
		{
			mDragRect.left = mPrevCursor.x;
			mDragRect.top = mPrevCursor.y;
			mDragRect.right = point.x;
			mDragRect.bottom = point.y;

			if (mbSelected == true)
			{
				if (mDragRect.left > mImages[mSelectedImageID]->GetSize().width)
					mDragRect.left = mImages[mSelectedImageID]->GetSize().width;

				if (mDragRect.top > mImages[mSelectedImageID]->GetSize().height)
					mDragRect.top = mImages[mSelectedImageID]->GetSize().height;

				if (mDragRect.right > mImages[mSelectedImageID]->GetSize().width)
					mDragRect.right = mImages[mSelectedImageID]->GetSize().width;

				if (mDragRect.bottom > mImages[mSelectedImageID]->GetSize().height)
					mDragRect.bottom = mImages[mSelectedImageID]->GetSize().height;
			}

			mbIsDrag = true;
		}
	}

	CView::OnLButtonUp(nFlags, point);
}

void CSpriteToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	mCurrCursor = point;

	CView::OnMouseMove(nFlags, point);
}

void CSpriteToolView::OnSpriteRegist()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	mMainFrame->mWndSpriteView.Insert(mSelectedImageID, mDragRect);
}

void CSpriteToolView::OnSelectCancle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	mbIsDrag = false;
	mDragRect = {};
}

void CSpriteToolView::OnUpdateSpriteRegist(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(mbIsDrag);
}

void CSpriteToolView::OnUpdateSelectCancle(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(mbIsDrag);
}