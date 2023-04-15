// AnimationView.cpp: 구현 파일
//

#include "pch.h"
#include "SpriteTool.h"
#include "AnimationView.h"



// AnimationButton 대화 상자

IMPLEMENT_DYNAMIC(AnimationButton, CDialog)

AnimationButton::AnimationButton(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Animation_Button, pParent)
	, mbOnPlay(false)
	, mbPivot(false)
	, mbCollider(false)
{

}

AnimationButton::~AnimationButton()
{
	
}

void AnimationButton::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_State_Box, mInputStateBox);
}

BEGIN_MESSAGE_MAP(AnimationButton, CDialog)
	ON_BN_CLICKED(IDC_PlayButton, &AnimationButton::OnBnClickedPlaybutton)
	ON_BN_CLICKED(IDC_StopButton, &AnimationButton::OnBnClickedStopbutton)
	ON_CBN_SELCHANGE(IDC_State_Box, &AnimationButton::OnCbnSelchangeStateBox)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// AnimationButton 메시지 처리기


// AnimationView

IMPLEMENT_DYNAMIC(AnimationView, CDockablePane)

AnimationView::AnimationView() noexcept
	: mBlackBrush(nullptr)
	, mMainFrame(nullptr)
	, mSpriteID(0)
	, mbIsLButtonDown(false)
{
	EnableD2DSupport();

	mBlackBrush = new CD2DSolidColorBrush(
		GetRenderTarget(),
		D2D1::ColorF(D2D1::ColorF::Black));

	D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_TRIANGLE,
		D2D1_LINE_JOIN_MITER, 10.0f,
		D2D1_DASH_STYLE_DASH_DOT_DOT, 0.0f);

	AfxGetD2DState()->GetDirect2dFactory()->CreateStrokeStyle(strokeStyleProperties, nullptr, 0, &mStrokeStyle);
}

AnimationView::~AnimationView()
{
	
}

void AnimationView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
	mCenter = { (rectClient.right + rectClient.left) / 2, (rectClient.top + rectClient.bottom) / 2 };

	//int cyTlb = mWndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//mWndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	if (mAnimationButton.GetSafeHwnd())
		mAnimationButton.SetWindowPos(nullptr, 0, rectClient.top, rectClient.right, rectClient.top + 28, SWP_NOZORDER);

	mToolBarHeight = rectClient.top + 28;
}

void AnimationView::OnChangeVisualStyle()
{
	//mWndToolBar.CleanUpLockedImages();
	//mWndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 잠금 */);

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("비트맵을 로드할 수 없습니다. %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;
}


BEGIN_MESSAGE_MAP(AnimationView, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &AnimationView::OnDraw2D)
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// AnimationView 메시지 처리기

void AnimationView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

int AnimationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 뷰를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	// 뷰 이미지를 로드합니다.
	//mWndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	//mWndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 잠금 */);

	OnChangeVisualStyle();

	//mWndToolBar.SetPaneStyle(mWndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//mWndToolBar.SetPaneStyle(mWndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//mWndToolBar.SetOwner(this);

	//// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	//mWndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	mAnimationButton.Create(IDD_Animation_Button, this);
	mAnimationButton.ShowWindow(SW_SHOW);

	SetTimer(0, 16, nullptr);

	return 0;
}

afx_msg LRESULT AnimationView::OnDraw2D(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* pRT = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(pRT);

	pRT->Clear(D2D1::ColorF(0xffffff));

	CRect clientRect;
	GetClientRect(&clientRect);

	pRT->DrawLine(CD2DPointF(0, mCenter.y), CD2DPointF(clientRect.right, mCenter.y), mBlackBrush);
	pRT->DrawLine(CD2DPointF(mCenter.x, 0), CD2DPointF(mCenter.x, clientRect.bottom), mBlackBrush);

	if (mMainFrame != nullptr)
	{
		auto findResult = mMainFrame->mWndSpriteView.mSpriteList.find(mSpriteID);

		if (findResult != mMainFrame->mWndSpriteView.mSpriteList.end())
		{
			CD2DRectF rect(mCenter.x - findResult->second.pivot.x,
				mCenter.y - findResult->second.pivot.y,
				mCenter.x - findResult->second.pivot.x + findResult->second.imageRect.right - findResult->second.imageRect.left,
				mCenter.y - findResult->second.pivot.y + findResult->second.imageRect.bottom - findResult->second.imageRect.top);

			pRT->DrawBitmap(mImages[findResult->second.imageID],
				rect,
				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				&(findResult->second.imageRect));

			if (mMainFrame->mWndProperties.GetPrintBoarderLine() == true)
				pRT->DrawRectangle(rect, mBlackBrush, 0.5f);

			switch (mMainFrame->mWndSpriteView.mSpriteList[mSpriteID].collider.type)
			{
			case 1:
				if (mbIsLButtonDown == true)
				{
					CSize size;

					size.cx = (mCurrCursor.x - mPrevCursor.x) / 2;
					size.cy = (mCurrCursor.y - mPrevCursor.y) / 2;

					if (size.cx < size.cy)
						size.cy = size.cx;
					else if (size.cy < size.cx)
						size.cx = size.cy;

					pRT->DrawEllipse(CD2DEllipse(CPoint(mPrevCursor.x + size.cx, mPrevCursor.y + size.cy), size), mBlackBrush, 1.0f, mStrokeStyle);
				}
				else
				{
					CRect rect = mMainFrame->mWndSpriteView.mSpriteList[mSpriteID].collider.rect;
					pRT->DrawEllipse(CD2DEllipse(CPoint(mCenter.x - findResult->second.pivot.x + rect.left, mCenter.y - findResult->second.pivot.y + rect.top), CD2DSizeF(rect.right, rect.bottom)), mBlackBrush, 1.0f, mStrokeStyle);
				}
				break;
			case 2:
				if (mbIsLButtonDown == true)
				{
					pRT->DrawRectangle(CRect(mPrevCursor.x, mPrevCursor.y, mCurrCursor.x, mCurrCursor.y), mBlackBrush, 1.0f, mStrokeStyle);
				}
				else
				{
					CRect rect = mMainFrame->mWndSpriteView.mSpriteList[mSpriteID].collider.rect;
					pRT->DrawRectangle(CRect(
						mCenter.x - findResult->second.pivot.x + rect.left - rect.right,
						mCenter.y - findResult->second.pivot.y + rect.top - rect.bottom,
						mCenter.x - findResult->second.pivot.x + rect.left + rect.right,
						mCenter.y - findResult->second.pivot.y + rect.top + rect.bottom), mBlackBrush, 1.0f, mStrokeStyle);
				}
				break;
			}
		}
	}
	else
	{
		mMainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);
	}

	return true;
}

void AnimationView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
}

void AnimationView::SetTargetSprite(UINT spriteID)
{
	mSpriteID = spriteID;
}

void AnimationView::AddImage(UINT imageID, CString path)
{
	auto findResult = mImages.find(imageID);

	if (findResult == mImages.end())
		mImages[imageID] = new CD2DBitmap(GetRenderTarget(), path);
}

void AnimationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	InvalidateRect(nullptr);

	CalcDeltaTime();

	if (mAnimationButton.mbOnPlay == true)
	{
		auto findResult = mMainFrame->mWndSpriteView.mSpriteList.find(mSpriteID);

		if (findResult != mMainFrame->mWndSpriteView.mSpriteList.end())
		{
			static FLOAT duringTime = 0.0f;

			duringTime += mDeltaTime;

			if (duringTime >= findResult->second.duration * 1000)
			{
				auto upperResult = mMainFrame->mWndSpriteView.mSpriteList.upper_bound(mSpriteID);

				if (upperResult == mMainFrame->mWndSpriteView.mSpriteList.end())
					upperResult = mMainFrame->mWndSpriteView.mSpriteList.begin();

				mSpriteID = upperResult->first;

				duringTime = 0.0f;
			}
		}
	}

	CDockablePane::OnTimer(nIDEvent);
}

void AnimationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	auto findResult = mMainFrame->mWndSpriteView.mSpriteList.find(mSpriteID);

	if (findResult != mMainFrame->mWndSpriteView.mSpriteList.end())
	{
		if (mAnimationButton.mbPivot == true)
		{
			CPoint pivot = mMainFrame->mWndSpriteView.mSpriteList[mSpriteID].pivot + point - mCenter;
			mMainFrame->mWndProperties.SetPivotFromSprite(pivot);
		}
		else if (mAnimationButton.mbCollider == true)
		{
			mbIsLButtonDown = true;
			mPrevCursor = point;
		}
	}

	if (point.y < mToolBarHeight)
		CDockablePane::OnLButtonDown(nFlags, point);
}

void AnimationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	mCurrCursor = point;

	CDockablePane::OnMouseMove(nFlags, point);
}

void AnimationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (mbIsLButtonDown == true)
	{
		mbIsLButtonDown = false;

		if (mAnimationButton.mbCollider == true)
		{
			mCurrCursor = point;

			if (abs(mPrevCursor.x - point.x) < 10 && abs(mPrevCursor.y - point.y) < 10)
			{
				mDragRect = {};
				mbIsDrag = false;
			}
			else
			{
				SpriteInfo& temp = mMainFrame->mWndSpriteView.mSpriteList[mSpriteID];
				CSize size;

				size.cx = (mCurrCursor.x - mPrevCursor.x) / 2;
				size.cy = (mCurrCursor.y - mPrevCursor.y) / 2;

				if (temp.collider.type == 1)
				{
					if (size.cx < size.cy)
						size.cy = size.cx;
					else if (size.cy < size.cx)
						size.cx = size.cy;
				}

				temp.collider.rect = {
				static_cast<FLOAT>(mPrevCursor.x + size.cx - mCenter.x + temp.pivot.x), static_cast<FLOAT>(mPrevCursor.y + size.cy - mCenter.y + temp.pivot.y),
				static_cast<FLOAT>(abs(size.cx)), static_cast<FLOAT>(abs(size.cy)) };
				mMainFrame->mWndProperties.SetColliderTypeFromSprite(mMainFrame->mWndSpriteView.mSpriteList[mSpriteID].collider);

				mbIsDrag = true;
			}
		}
	}

	CDockablePane::OnLButtonUp(nFlags, point);
}

void AnimationView::CalcDeltaTime()
{
	static UINT prevTime = GetTickCount64();

	mDeltaTime = GetTickCount64() - prevTime;

	prevTime = GetTickCount64();
}

void AnimationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (point.y < mToolBarHeight)
		CDockablePane::OnRButtonDown(nFlags, point);
}

void AnimationButton::OnBnClickedPlaybutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	mbOnPlay = true;
}

void AnimationButton::OnBnClickedStopbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	mbOnPlay = false;
}

BOOL AnimationButton::OnInitDialog()
{
	CDialog::OnInitDialog();

	COMBOBOXEXITEM* item = new COMBOBOXEXITEM;
	ZeroMemory(item, sizeof(COMBOBOXEXITEM));

	item->pszText = _T("Pivot");
	item->mask = CBEIF_TEXT;
	item->iItem = static_cast<int>(eButtonState::Pivot);

	mInputStateBox.InsertItem(item);

	delete item;

	item = new COMBOBOXEXITEM;
	ZeroMemory(item, sizeof(COMBOBOXEXITEM));

	item->pszText = _T("Collider");
	item->mask = CBEIF_TEXT;
	item->iItem = static_cast<int>(eButtonState::Collider);

	mInputStateBox.InsertItem(item);

	delete item;

	mInputStateBox.SetCurSel(static_cast<int>(eButtonState::Pivot));
	mbPivot = true;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void AnimationButton::OnCbnSelchangeStateBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	switch (static_cast<eButtonState>(mInputStateBox.GetCurSel()))
	{
	case eButtonState::Pivot:
		mbPivot = true;
		mbCollider = false;
		break;
	case eButtonState::Collider:
		mbPivot = false;
		mbCollider = true;
		break;
	}
}

void AnimationButton::OnDestroy()
{
	CDialog::OnDestroy();


}