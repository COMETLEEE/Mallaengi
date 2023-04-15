// MiniMap.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "MiniMap.h"
#include "JsonManager.h"


// MiniMap

IMPLEMENT_DYNCREATE(MiniMap, CView)

MiniMap::MiniMap()
	: mWhiteBrush(nullptr)
	, mMainFrame(nullptr)
	, mbMiniMapDrag(false)
{
	CreateD2D();
}

MiniMap::~MiniMap()
{
}

BEGIN_MESSAGE_MAP(MiniMap, CView)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &MiniMap::OnDraw2D)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// MiniMap 그리기

void MiniMap::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// MiniMap 진단

#ifdef _DEBUG
void MiniMap::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MiniMap::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void MiniMap::CreateD2D()
{
	try
	{
		// Enable D2D support for this window:
		EnableD2DSupport();

		// Initialize D2D resources:

		// Brush
		mWhiteBrush = new CD2DSolidColorBrush(GetRenderTarget(), 0xffffff);
		mBlackBrush = new CD2DSolidColorBrush(GetRenderTarget(), 0x000000);
	}
	catch (std::bad_alloc& ba)
	{
		CString errMessage = _T("Bad Alloc : ");
		errMessage = ba.what();

		OutputDebugString(errMessage);
	}
	catch (...)
	{
		OutputDebugString(_T("Editor에서 D2D 생성하는 중에 에러가 발생했습니다.\n"));
	}
}

HRESULT MiniMap::AddImage(UINT imageID, CString path)
{
	map<UINT, CD2DBitmap*>::iterator temp = mImages.find(imageID);

	if (temp != mImages.end())
		return S_OK;

	mImages[imageID] = new CD2DBitmap(GetRenderTarget(), path);

	if (mImages[imageID] != nullptr)
		return S_OK;

	return E_FAIL;
}
#endif
#endif //_DEBUG

// MiniMap 메시지 처리기

afx_msg LRESULT MiniMap::OnDraw2D(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* pRT = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(pRT);

	pRT->Clear(mWhiteBrush->GetColor());
	pRT->DrawBitmap(mImages[1], mMiniMapSize);

	// Editor View로부터 타일 데이터를 받아온다.
	const vector<vector<TileData>>& tileTemp = mMainFrame->mEditorView->mTiles;
	const vector<vector<vector<TileData>>>& objectTemp = mMainFrame->mEditorView->mObjects;

	if (tileTemp.empty() || objectTemp.empty())
		return TRUE;

	// 클라이언트 기준 가로세로 크기 구하기
	float width = static_cast<float>(mMiniMapSize.Width()) / tileTemp[0].size();
	float height = static_cast<float>(mMiniMapSize.Height()) / tileTemp.size();

	// 타일 데이터를 축소해서 미니맵에 그린다.
	for (int y = 0; y < tileTemp.size(); y++)
	{
		for (int x = 0; x < tileTemp[y].size(); x++)
		{
			CD2DRectF tileRect;

			tileRect.left = mMiniMapSize.left + static_cast<int>(x * width);
			tileRect.right = mMiniMapSize.left + static_cast<int>((x + 1) * width);
			tileRect.top = mMiniMapSize.top + static_cast<int>(y * height);
			tileRect.bottom = mMiniMapSize.top + static_cast<int>((y + 1) * height);

			if (tileTemp[y][x].layer != 0)
				pRT->DrawBitmap(mImages[tileTemp[y][x].imageID], tileRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &tileTemp[y][x].imageRect);

			for (int k = 0; k < objectTemp[y][x].size(); k++)
			{
				CD2DRectF imageRect = objectTemp[y][x][k].imageRect;
				INT groupIndex = objectTemp[y][x][k].group.front();

				if (groupIndex > 0)
					groupIndex = 0;

				int nx = -groupIndex & 0xffff;
				int ny = -groupIndex >> 16;

				imageRect.left += nx * 80;
				imageRect.top += ny * 77;
				imageRect.right = imageRect.left + 80;
				imageRect.bottom = imageRect.top + 77;

				if (objectTemp[y][x][k].layer != 0)
					pRT->DrawBitmap(mImages[objectTemp[y][x][k].imageID], tileRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &imageRect);
			}
		}
	}

	pRT->DrawRectangle(mShowRect, mBlackBrush);

	return TRUE;
}

void MiniMap::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	static bool callOnce = true;

	if (callOnce == true)
	{
		// 이미지 추가
		ImageJson imageJson;
		imageJson.DeserializeFromFile("Json\\ImageResourceTable.json");

		for (auto iter = imageJson.mImageList.begin(); iter != imageJson.mImageList.end(); iter++)
			AddImage(iter->imageID, iter->path);

		// Main Frame
		mMainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

		// Timer 설정
		SetTimer(static_cast<UINT_PTR>(eEventMessage::REDRAW), 66/*15FPS*/, nullptr);

		callOnce = false;
	}
}

void MiniMap::OnTimer(UINT_PTR nIDEvent)
{
	switch (static_cast<eEventMessage>(nIDEvent))
	{
		// 화면 갱신
	case eEventMessage::REDRAW:
		// 현재 사용자가 보고있는 영역을 사각형으로 표시한다.
		CD2DPointF editorScrollPer = mMainFrame->mEditorView->GetScrollPercent();
		CD2DPointF editorScreenPer = mMainFrame->mEditorView->GetScreenPercent();

		mShowRect = { mMiniMapSize.left, mMiniMapSize.top, mMiniMapSize.left, mMiniMapSize.top };
		
		mShowRect.left += static_cast<FLOAT>(mMiniMapSize.Width()) * editorScrollPer.x;
		mShowRect.top += static_cast<FLOAT>(mMiniMapSize.Height()) * editorScrollPer.y;
		mShowRect.right += static_cast<FLOAT>(mMiniMapSize.Width()) * editorScreenPer.x;
		mShowRect.bottom += static_cast<FLOAT>(mMiniMapSize.Height()) * editorScreenPer.y;

		InvalidateRect(nullptr);
		break;
	}

	CView::OnTimer(nIDEvent);
}

void MiniMap::OnDestroy()
{
	CView::OnDestroy();

	KillTimer(static_cast<UINT_PTR>(eEventMessage::REDRAW));
}

void MiniMap::OnLButtonDown(UINT nFlags, CPoint point)
{
	mbMiniMapDrag = true;

	CD2DPointF temp = point;
	CRect cursorRect = {
	mMiniMapSize.left + mShowRect.Width() / 2, mMiniMapSize.top + mShowRect.Height() / 2,
	mMiniMapSize.right - mShowRect.Width() / 2, mMiniMapSize.bottom - mShowRect.Height() / 2 };

	if (temp.x < cursorRect.left) temp.x = cursorRect.left;
	if (temp.x > cursorRect.right) temp.x = cursorRect.right;
	if (temp.y < cursorRect.top) temp.y = cursorRect.top;
	if (temp.y > cursorRect.bottom) temp.y = cursorRect.bottom;

	temp.x = static_cast<FLOAT>(temp.x - cursorRect.left) / cursorRect.Width();
	temp.y = static_cast<FLOAT>(temp.y - cursorRect.top) / cursorRect.Height();

	mMainFrame->mEditorView->SetScroll(temp);

	CView::OnLButtonDown(nFlags, point);
}

void MiniMap::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mbMiniMapDrag == true)
	{
		CD2DPointF temp = point;
		CRect cursorRect = {
		mMiniMapSize.left + mShowRect.Width() / 2, mMiniMapSize.top + mShowRect.Height() / 2,
		mMiniMapSize.right - mShowRect.Width() / 2, mMiniMapSize.bottom - mShowRect.Height() / 2 };

		if (temp.x < cursorRect.left) temp.x = cursorRect.left;
		if (temp.x > cursorRect.right) temp.x = cursorRect.right;
		if (temp.y < cursorRect.top) temp.y = cursorRect.top;
		if (temp.y > cursorRect.bottom) temp.y = cursorRect.bottom;

		temp.x = static_cast<FLOAT>(temp.x - cursorRect.left) / cursorRect.Width();
		temp.y = static_cast<FLOAT>(temp.y - cursorRect.top) / cursorRect.Height();

		mMainFrame->mEditorView->SetScroll(temp);
	}

	CView::OnMouseMove(nFlags, point);
}

CRect& MiniMap::MiniMapSizeProp()
{
	GetClientRect(&mMiniMapSize);

	return mMiniMapSize;
}

void MiniMap::OnLButtonUp(UINT nFlags, CPoint point)
{
	mbMiniMapDrag = false;

	CView::OnLButtonUp(nFlags, point);
}