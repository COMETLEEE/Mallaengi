// Editor.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "Editor.h"
#include <queue>

#define ZOOM_MIN 0.5f
#define ZOOM_MAX 2.0f

using std::priority_queue;

// Editor

IMPLEMENT_DYNCREATE(Editor, CScrollView)

Editor::Editor()
#pragma region Initialize
	: mTextFormat(nullptr)
	, mBlackBrush(nullptr)
	, mWhiteBrush(nullptr)
	, mGreenBrush(nullptr)
	, mTileWidth(80)
	, mTileHeight(77)
	, mTileXAmount(30)
	, mTileYAmount(30)
	, mCursorIndex{}
	, mScroll{}
	, mZoom(1.0f)
	, mbLButtonDown(false)
	, mbRButtonDown(false)
	, mbMouseTrack(false)
	, mbIsCanSetTile(false)
	, mbIsGridOn(true)
	, mbIsTileIndexOn(true)
	, mMainFrame(nullptr)
	, callOnce(false)
#pragma endregion
{
	// MFC D2D 사용
	CreateD2D();

	// 기본 Tile 초기화
	InitTiles();
}

Editor::~Editor()
{
	if (mTileRT != nullptr)
	{
		mTileRT->Destroy();
		delete mTileRT;
	}

	if (mGridRT != nullptr)
	{
		mGridRT->Destroy();
		delete mGridRT;
	}

	if (mIndexRT != nullptr)
	{
		mIndexRT->Destroy();
		delete mIndexRT;
	}
}

// Editor 진단

#ifdef _DEBUG
void Editor::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void Editor::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

BEGIN_MESSAGE_MAP(Editor, CScrollView)
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &Editor::OnDraw2D)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

// Editor 그리기

void Editor::CreateD2D()
{
	try
	{
		// Enable D2D support for this window:
		EnableD2DSupport();

		// Initialize D2D resources:

		// Text Format
		mTextFormat = new CD2DTextFormat(GetRenderTarget(), _T("Verdana"), 50);
		mTextFormat->Get()->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		mTextFormat->Get()->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		// Brush
		mBlackBrush = new CD2DSolidColorBrush(GetRenderTarget(), 0x000000);
		mWhiteBrush = new CD2DSolidColorBrush(GetRenderTarget(), 0xffffff);
		mGreenBrush = new CD2DSolidColorBrush(GetRenderTarget(), 0x00ff00);
		mRedBrush = new CD2DSolidColorBrush(GetRenderTarget(), 0x0000ff);

		// 투명한 영역을 위해 알파로 초기화하기 위한 변수
		D3DCOLORVALUE alpha;
		alpha.a = 0;
		mAlphaBrush = new CD2DSolidColorBrush(GetRenderTarget(), alpha);

		// Back Buffer
		mTileBackBuffer = new CD2DBitmap(GetRenderTarget(), _T("Resources\\BackGround\\backbuffer.png"));
		mIndexBackBuffer = new CD2DBitmap(GetRenderTarget(), _T("Resources\\BackGround\\backbuffer.png"));
		mGridBackBuffer = new CD2DBitmap(GetRenderTarget(), _T("Resources\\BackGround\\backbuffer.png"));
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

void Editor::CreateBackBufferRT(CHwndRenderTarget* pRT)
{
	callOnce = false;

	CD2DSizeF size = { static_cast<FLOAT>(mTileWidth * mTileXAmount * ZOOM_MAX), static_cast<FLOAT>(mTileHeight * mTileYAmount * ZOOM_MAX) };

	// MFC에서 제공되는 Render Target과 호환되는 Bitmap RenderTarget들을 생성한다.

	if (mTileRT != nullptr)
	{
		mTileRT->Destroy();
		delete mTileRT;
	}

	if (mGridRT != nullptr)
	{
		mGridRT->Destroy();
		delete mGridRT;
	}

	if (mIndexRT != nullptr)
	{
		mIndexRT->Destroy();
		delete mIndexRT;
	}

	mTileRT = new CBitmapRenderTarget;
	mIndexRT = new CBitmapRenderTarget;
	mGridRT = new CBitmapRenderTarget;

	pRT->CreateCompatibleRenderTarget(*mTileRT, size);
	mTileRT->GetBitmap(*mTileBackBuffer);
	pRT->CreateCompatibleRenderTarget(*mIndexRT, size);
	mIndexRT->GetBitmap(*mIndexBackBuffer);
	pRT->CreateCompatibleRenderTarget(*mGridRT, size);
	mGridRT->GetBitmap(*mGridBackBuffer);
	DrawBackBuffer();
}

void Editor::DrawBackBuffer()
{
	// Tile 레이어 초기화
	mTileRT->BeginDraw();
	mTileRT->Clear(mAlphaBrush->GetColor());
	mTileRT->EndDraw();

	// Index 레이어 초기화
	mIndexRT->BeginDraw();
	mIndexRT->Clear(mAlphaBrush->GetColor());
	mIndexRT->EndDraw();

	// Grid 레이어 초기화
	mGridRT->BeginDraw();
	mGridRT->Clear(mAlphaBrush->GetColor());
	mGridRT->EndDraw();

	for (int y = 0; y < mTileYAmount; y++)
	{
		for (int x = 0; x < mTileXAmount; x++)
		{
			CPoint temp(x, y);
			DrawTargetTile(temp);
			DrawTileIndex(temp);
		}
	}

	DrawGrid();
}

/// <summary>
/// Tile에 저장된 데이터를 토대로 타일을 그린다.
/// </summary>
void Editor::DrawTargetTile(CPoint tile)
{
	mTileRT->BeginDraw();

	CD2DRectF rect;

	rect.left = static_cast<int>(tile.x * mTileWidth);
	rect.top = static_cast<int>(tile.y * mTileHeight);
	rect.right = static_cast<int>((tile.x + 1) * mTileWidth);
	rect.bottom = static_cast<int>((tile.y + 1) * mTileHeight);

	// 영역을 지정해서 해당된 부분만 투명 상태로 초기화시켜준다.
	mTileRT->PushAxisAlignedClip(rect);
	mTileRT->Clear(mAlphaBrush->GetColor());
	mTileRT->PopAxisAlignedClip();

	// 레이어로 우선 순위를 정해 정렬시킨다.
	bool (*pred)(TileData& dest, TileData& src) = [](TileData& dest, TileData& src)-> bool { return dest.layer > src.layer; };
	priority_queue<TileData, vector<TileData>, decltype(pred)> drawQueue(pred);

	// 빈 타일이 아닐경우 해당 이미지 출력
	// 빈 타일인 경우 layer == 0
	for (auto iter : mObjects[tile.y][tile.x])
	{
		drawQueue.push(iter);
	}

	if (mTiles[tile.y][tile.x].layer != 0)
	{
		drawQueue.push(mTiles[tile.y][tile.x]);
	}

	// Queue에 등록된 순서대로 그린다. 위에서 조건을 정해줬으므로 레이어 값이 제일 높은 것부터 그린다.
	while (drawQueue.empty() != true)
	{
		CD2DRectF imageRect = drawQueue.top().imageRect;
		INT groupIndex = drawQueue.top().group.front();

		// 그룹 인덱스가 양수라면 맵툴에서 오브젝트의 기준점이 되는 타일 이므로 주소값을 변경하지 않는다.
		if (groupIndex > 0)
			groupIndex = 0;

		// 오브젝트의 기준점으로부터의 좌표를 구한다.
		int x = -groupIndex & 0xffff;
		int y = -groupIndex >> 16;

		imageRect.left += x * mTileWidth;
		imageRect.top += y * mTileHeight;
		imageRect.right = imageRect.left + mTileWidth;
		imageRect.bottom = imageRect.top + mTileHeight;

		// 현재 타일에 필요한 이미지정보를 가져온다.
		mTileRT->DrawBitmap(mImages[drawQueue.top().imageID], rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &imageRect);

		drawQueue.pop();
	}

	mTileRT->EndDraw();
}

void Editor::DrawAllTiles()
{
	for (int y = 0; y < mTileYAmount; y++)
		for (int x = 0; x < mTileXAmount; x++)
			DrawTargetTile(CPoint(x, y));
}

/// <summary>
/// Tile 구분을 위해 격자 무늬를 그린다.
/// </summary>
void Editor::DrawGrid()
{
	mGridRT->BeginDraw();

	// 가로 줄
	for (int i = 1; i <= mTileYAmount; i++)
	{
		FLOAT height = i * mTileHeight;

		CD2DPointF dest = { 0, height };
		CD2DPointF src = { mTileXAmount * mTileWidth / mZoom, height };

		mGridRT->DrawLine(dest, src, mBlackBrush);
	}

	// 세로 줄
	for (int i = 1; i <= mTileXAmount; i++)
	{
		FLOAT width = i * mTileWidth;

		CD2DPointF dest = { width, 0 };
		CD2DPointF src = { width, mTileYAmount * mTileHeight / mZoom };

		mGridRT->DrawLine(dest, src, mBlackBrush);
	}

	mGridRT->EndDraw();
}

void Editor::DrawTileIndex(CPoint tile)
{
	mIndexRT->BeginDraw();

	CD2DRectF rect;

	rect.left = static_cast<int>(tile.x * mTileWidth);
	rect.right = static_cast<int>((tile.x + 1) * mTileWidth);
	rect.top = static_cast<int>(tile.y * mTileHeight);
	rect.bottom = static_cast<int>((tile.y + 1) * mTileHeight);

	// 타일의 주소 출력
	TCHAR buf[16];

	_stprintf_s(buf, 16, _T("[%d,%d]"), tile.y, tile.x);
	mIndexRT->DrawText(buf, rect, mBlackBrush);

	mIndexRT->EndDraw();
}

/// <summary>
/// 현재 마우스가 위치하는 타일 주소에 사각형 테두리를 그린다.
/// </summary>
void Editor::DrawCursorBox(CHwndRenderTarget* pRT)
{
	CD2DRectF rect;

	rect.left = mCursorIndex.x * mTileWidth - mScroll.x / mZoom;
	rect.right = (mCursorIndex.x + 1) * mTileWidth - mScroll.x / mZoom;
	rect.top = mCursorIndex.y * mTileHeight - mScroll.y / mZoom;
	rect.bottom = (mCursorIndex.y + 1) * mTileHeight - mScroll.y / mZoom;

	// 선택중인 Item을 받아온다.
	ItemData temp = mMainFrame->mControlView->mControlSheet->GetSelectedItemData();

	// 선택중인 Item이 존재할 경우에 해당 Item의 크기만큼 테두리도 키우고
	// Item은 Alpha값을 0.3주어서 입력할 Item을 미리 보여준다.
	if (temp.imageID != 0)
	{
		rect.right = rect.left + temp.imageRect.right - temp.imageRect.left;
		rect.bottom = rect.top + temp.imageRect.bottom - temp.imageRect.top;

		pRT->DrawBitmap(mImages[temp.imageID], rect, 0.3f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &temp.imageRect);
	}

	if (mbIsCanSetTile == true)
		pRT->DrawRectangle(rect, mGreenBrush, 3.0f);
	else
		pRT->DrawRectangle(rect, mRedBrush, 3.0f);
}

void Editor::InitTiles()
{
	mTiles.clear();
	mObjects.clear();
	mTiles.resize(mTileYAmount);
	mObjects.resize(mTileYAmount);

	for (int i = 0; i < mTileYAmount; i++)
	{
		mTiles[i].resize(mTileXAmount);
		mObjects[i].resize(mTileXAmount);
	}
}

/// <summary>
/// 드래그 했을 때 이전 마우스 좌표와 현재 마우스 좌표를 가지고
/// 대상이 되는 타일 좌표를 계산한다.
/// 래스터 라이징과 비슷하게 동작하도록 처리
/// </summary>
void Editor::SetDataToTile()
{
	// 마우스를 클릭중이 아니라면 함수를 탈출한다.
	if (mbLButtonDown == false && mbRButtonDown == false)
		return;

	FLOAT xDistance = abs(mCursorIndex.x - mPrevCursorIndex.x);
	FLOAT yDistance = abs(mCursorIndex.y - mPrevCursorIndex.y);

	// 이전 마우스 좌표와 현재 마우스 좌표가 같은 경우 함수를 탈출한다.
	if (xDistance == 0 && yDistance == 0)
		return;

	int xSign = mCursorIndex.x >= mPrevCursorIndex.x ? 1 : -1;
	int ySign = mCursorIndex.y >= mPrevCursorIndex.y ? 1 : -1;

	// X의 차이가 y의 차이보다 큰 경우
	if (xDistance >= yDistance)
	{
		for (int i = 1; i <= xDistance; i++)
		{
			int x = mPrevCursorIndex.x + xSign * i;
			int y = mPrevCursorIndex.y + ySign * (i / xDistance) * yDistance;

			// L 버튼이 눌렸다면 타일에 데이터 입력
			if (mbLButtonDown == true)
				SetTargetTile(CPoint(x, y));
			// R 버튼이 눌렸다면 타일에서 데이터 제거
			else if (mbRButtonDown == true)
				PopTargetTile(CPoint(x, y));
		}
	}
	// y의 차이가 더 큰 경우
	else
	{
		for (int i = 1; i <= yDistance; i++)
		{
			int x = mPrevCursorIndex.x + xSign * (i / yDistance) * xDistance;
			int y = mPrevCursorIndex.y + ySign * i;

			// L 버튼이 눌렸다면 타일에 데이터 입력
			if (mbLButtonDown == true)
				SetTargetTile(CPoint(x, y));
			// R 버튼이 눌렸다면 타일에서 데이터 제거
			else if (mbRButtonDown == true)
				PopTargetTile(CPoint(x, y));
		}
	}
}

void Editor::SetTargetTile(CPoint tile)
{
	if (mbIsCanSetTile == true)
	{
		mbIsCanSetTile = false;

		// Control View에서 Property 클래스 포인터와 ItemData를 받아온다.
		ControlProperty* ctrlProp = mMainFrame->mControlView->mControlSheet;
		ItemData temp = ctrlProp->GetSelectedItemData();

		// ItemTyep : Terrain, Object 두가지
		switch (ctrlProp->GetItemType())
		{
		case eItemType::Terrain:
			// 선택된 Item을 Tile에 저장하고
			mTiles[tile.y][tile.x].ID = temp.ID;
			mTiles[tile.y][tile.x].type = ctrlProp->GetItemTypeString();
			mTiles[tile.y][tile.x].group = temp.group;
			mTiles[tile.y][tile.x].imageID = temp.imageID;
			mTiles[tile.y][tile.x].imageRect = temp.imageRect;
			mTiles[tile.y][tile.x].layer = temp.layer;

			// 그 타일이 여러 그리드를 사용하는 타일이라면 해당되는 타일들을 전부 저장한다.
			if (temp.group.empty() != true && temp.group.front() > 0)
			{
				for (int i = 0; i < temp.group.size(); i++)
				{
					INT groupIndex = temp.group[i];
					int x = tile.x + (groupIndex & 0xffff);
					int y = tile.y + (groupIndex >> 16);

					mTiles[y][x].ID = temp.ID;
					mTiles[y][x].type = ctrlProp->GetItemTypeString();
					mTiles[y][x].group.push_back(-groupIndex);
					mTiles[y][x].imageID = temp.imageID;
					mTiles[y][x].imageRect = temp.imageRect;
					mTiles[y][x].layer = temp.layer;

					DrawTargetTile(CPoint(x, y));
				}
			}
			break;
		case eItemType::Object:
			// 동일한 ID를 가진 Object와는 겹치지않게 한다.
			for (int i = 0; i < mObjects[tile.y][tile.x].size(); i++)
			{
				if (mObjects[tile.y][tile.x][i].ID == temp.ID)
					return;
			}

			mObjects[tile.y][tile.x].push_back({
				temp.ID,
				ctrlProp->GetItemTypeString(),
				0,
				temp.group,
				temp.imageID,
				temp.imageRect,
				temp.layer });

			// Object가 여러 그리드를 사용하는 경우
			if (temp.group.empty() != true && temp.group.front() > 0)
			{
				for (int i = 0; i < temp.group.size(); i++)
				{
					// 그룹인덱스의 값을 적용시켜서 해당되는 타일의 주소를 구하고
					INT groupIndex = temp.group[i];
					int x = tile.x + (groupIndex & 0xffff);
					int y = tile.y + (groupIndex >> 16);

					// 값을 저장한다.
					mObjects[y][x].push_back({
						temp.ID,
						ctrlProp->GetItemTypeString(),
						0,
						vector<INT>(1),
						temp.imageID,
						temp.imageRect,
						temp.layer });

					mObjects[y][x].back().group.back() = -groupIndex;

					// 저장한 후에는 레이어가 높은게 앞으로 오도록 정렬해준다.
					std::sort(mObjects[y][x].begin(), mObjects[y][x].end(),
						[](TileData& dest, TileData& src) -> bool { return dest.layer > src.layer; });

					DrawTargetTile(CPoint(x, y));
				}
			}

			// 본체의 타일도 정렬시켜준다.
			std::sort(mObjects[tile.y][tile.x].begin(), mObjects[tile.y][tile.x].end(),
				[](TileData& dest, TileData& src) -> bool {return dest.layer > src.layer; });
			break;
		default:
			return;
		}

		DrawTargetTile(CPoint(tile.x, tile.y));
	}
}

void Editor::PopTargetTile(CPoint tile)
{
	CPoint temp = tile;

	ControlProperty* ctrlProp = mMainFrame->mControlView->mControlSheet;

	switch (ctrlProp->GetItemType())
	{
	case eItemType::Terrain:
		if (mTiles[temp.y][temp.x].group.empty() != true)
		{
			INT groupIndex;

			if (mTiles[temp.y][temp.x].group.front() < 0)
			{
				groupIndex = -mTiles[temp.y][temp.x].group.front();
				temp.x -= groupIndex & 0xffff;
				temp.y -= groupIndex >> 16;
			}

			for (int i = 0; i < mTiles[temp.y][temp.x].group.size(); i++)
			{
				groupIndex = mTiles[temp.y][temp.x].group[i];
				mTiles[temp.y + (groupIndex >> 16)][temp.x + (groupIndex & 0xffff)] = {};
				DrawTargetTile(CPoint(temp.x + (groupIndex & 0xffff), temp.y + (groupIndex >> 16)));
			}

			// 타일 정보 초기화
			mTiles[temp.y][temp.x] = {};
		}
		break;
	case eItemType::Object:
		if (mObjects[temp.y][temp.x].empty() != true)
		{
			INT groupIndex;

			// 지우려는 대상의 본체를 찾는 작업을 한다.
			if (mObjects[temp.y][temp.x].front().group.front() < 0)
			{
				groupIndex = -mObjects[temp.y][temp.x].front().group.front();
				temp.x -= groupIndex & 0xffff;
				temp.y -= groupIndex >> 16;
			}

			// 본체 좌표에서 ID가 일치하는 오브젝트를 찾아야한다.
			for (auto iter = mObjects[temp.y][temp.x].begin(); iter != mObjects[temp.y][temp.x].end(); iter++)
			{
				if (iter->ID == mObjects[tile.y][tile.x].front().ID)
				{
					// 일치하는 오브젝트를 찾았다면 해당 Group도 전부 찾는다.
					for (int i = 0; i < iter->group.size(); i++)
					{
						if (iter->group[i] == 0)
							break;

						groupIndex = iter->group[i];
						int x = temp.x + (groupIndex & 0xffff);
						int y = temp.y + (groupIndex >> 16);

						// 해당 Group 타일 좌표에 있는 오브젝트 중에서 ID가 일치하는 것을 찾아서 지운다.
						for (auto iter2 = mObjects[y][x].begin(); iter2 != mObjects[y][x].end(); iter2++)
						{
							if (iter->ID == iter2->ID)
							{
								mObjects[y][x].erase(iter2);
								DrawTargetTile(CPoint(x, y));
								break;
							}
						}
					}

					mObjects[temp.y][temp.x].erase(iter);
					break;
				}
			}
		}
		break;
	}

	DrawTargetTile(temp);
}

CD2DPointF Editor::GetScrollPercent()
{
	CD2DPointF ret;
	ret.x = mScroll.x / static_cast<FLOAT>(mTileWidth * mTileXAmount * mZoom);
	ret.y = mScroll.y / static_cast<FLOAT>(mTileHeight * mTileYAmount * mZoom);

	return ret;
}

CD2DPointF Editor::GetScreenPercent()
{
	CRect rect;
	GetClientRect(&rect);

	CD2DPointF ret;
	ret.x = (mScroll.x + rect.Width()) / static_cast<FLOAT>(mTileWidth * mTileXAmount * mZoom);
	ret.y = (mScroll.y + rect.Height()) / static_cast<FLOAT>(mTileHeight * mTileYAmount * mZoom);

	return ret;
}

void Editor::SetScroll(CD2DPointF percent)
{
	CRect rect;
	GetClientRect(&rect);

	FLOAT width = static_cast<FLOAT>(mTileWidth * mTileXAmount * mZoom) - rect.Width();
	FLOAT height = static_cast<FLOAT>(mTileHeight * mTileYAmount * mZoom) - rect.Height();

	SetScrollPos(SB_HORZ, width * percent.x);
	SetScrollPos(SB_VERT, height * percent.y);

	mScroll = GetDeviceScrollPosition();
}

HRESULT Editor::AddImage(UINT imageID, CString path)
{
	map<UINT, CD2DBitmap*>::iterator temp = mImages.find(imageID);

	if (temp != mImages.end())
		return S_OK;

	mImages[imageID] = new CD2DBitmap(GetRenderTarget(), path);

	if (mImages[imageID] != nullptr)
		return S_OK;

	return E_FAIL;
}

void Editor::SaveFile(string path)
{
	MapJson mapJson;

	SaveData(mapJson);
	mapJson.SerializeToFile(path);
}

string Editor::SaveFile()
{
	MapJson mapJson;

	SaveData(mapJson);

	return mapJson.SerializeToMFC();
}

void Editor::SaveData(MapJson& mapJson)
{
	vector<vector<TileData>> tileTemp = mTiles;
	vector<vector<vector<TileData>>> objectTemp = mObjects;

	for (int i = 0; i < tileTemp.size(); i++)
	{
		for (int j = 0; j < tileTemp[i].size(); j++)
		{
			if (tileTemp[i][j].ID != 0)
			{
				mapJson.mTileList.push_back(tileTemp[i][j]);
				mapJson.mTileList.back().index = (i << 16) + (j & 0xffff);

				if (tileTemp[i][j].group.empty() != true && tileTemp[i][j].group.front() != 0)
				{
					for (int k = 0; k < tileTemp[i][j].group.size(); k++)
					{
						INT index = tileTemp[i][j].group[k];

						tileTemp[i + (index >> 16)][j + (index & 0xffff)] = {};
					}
				}
			}

			for (auto iter : objectTemp[i][j])
			{
				mapJson.mTileList.push_back(iter);
				mapJson.mTileList.back().index = (i << 16) + (j & 0xffff);

				if (iter.group.empty() != true && iter.group.front() != 0)
				{
					for (int k = 0; k < iter.group.size(); k++)
					{
						INT index = iter.group[k];
						int x = j + (index & 0xffff);
						int y = i + (index >> 16);

						for (auto iter2 = objectTemp[y][x].begin(); iter2 != objectTemp[y][x].end(); iter2++)
						{
							if (iter.ID == iter2->ID)
							{
								objectTemp[y][x].erase(iter2);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void Editor::LoadFile(string path)
{
	MapJson mapJson;
	mapJson.DeserializeFromFile(path);

	LoadData(mapJson);
}

void Editor::LoadFileFromData(string data)
{
	MapJson mapJson;
	mapJson.DeserializeFromData(data);

	LoadData(mapJson);
}

void Editor::LoadData(MapJson& mapJson)
{
	InitTiles();

	mTiles.resize(100);
	mObjects.resize(100);

	for (int i = 0; i < 100; i++)
	{
		mTiles[i].resize(100);
		mObjects[i].resize(100);
	}

	INT maxX = 0;
	INT maxY = 0;

	for (int i = 0; i < mapJson.mTileList.size(); i++)
	{
		UINT index = mapJson.mTileList[i].index;
		INT x = index & 0xffff;
		INT y = index >> 16;

		if (x > maxX)
			maxX = x;

		if (y > maxY)
			maxY = y;

		if (mapJson.mTileList[i].type.compare("Terrain") == 0)
		{
			mTiles[y][x] = mapJson.mTileList[i];
		}
		else if (mapJson.mTileList[i].type.compare("Object") == 0)
		{
			mObjects[y][x].push_back(mapJson.mTileList[i]);

			if (mapJson.mTileList[i].group.empty() != true && mapJson.mTileList[i].group.front() > 0)
			{
				for (int j = 0; j < mapJson.mTileList[i].group.size(); j++)
				{
					INT groupIndex = mapJson.mTileList[i].group[j];
					INT nx = x + (groupIndex & 0xffff);
					INT ny = y + (groupIndex >> 16);

					if (nx > maxX)
						maxX = nx;

					if (ny > maxY)
						maxY = ny;

					mObjects[ny][nx].push_back({
						mapJson.mTileList[i].ID,
						mapJson.mTileList[i].type,
						0,
						vector<INT>(1, -groupIndex),
						mapJson.mTileList[i].imageID,
						mapJson.mTileList[i].imageRect,
						mapJson.mTileList[i].layer });

					std::sort(mObjects[ny][nx].begin(), mObjects[ny][nx].end(),
						[](TileData& dest, TileData& src) -> bool { return dest.layer < src.layer; });
				}
			}

			std::sort(mObjects[y][x].begin(), mObjects[y][x].end(),
				[](TileData& dest, TileData& src) -> bool {return dest.layer < src.layer; });
		}
	}

	if (maxX < 10)
		maxX = 10;
	if (maxY < 10)
		maxY = 10;

	SizeChange(maxX + 1, maxY + 1);

	DrawAllTiles();
}

/// <summary>
/// Doc에서 타일 사이즈를 변경했을 때 호출되는 함수
/// </summary>
void Editor::SizeChange(INT xAmount, INT yAmount)
{
	mTileXAmount = xAmount;
	mTileYAmount = yAmount;

	// 사이즈 변경으로 인해 BackBuffer 세팅을 다시하기 위한 callOnce 변수를 활성화한다.
	callOnce = true;

	FLOAT mapWidth = mTileWidth * mTileXAmount;
	FLOAT mapHeight = mTileHeight * mTileYAmount;

	mTiles.resize(yAmount);
	mObjects.resize(yAmount);

	for (int i = 0; i < yAmount; i++)
	{
		mTiles[i].resize(xAmount);
		mObjects[i].resize(xAmount);
	}

	// 스크롤 사이즈도 변경
	CSize sizeTotal;

	sizeTotal.cx = mapWidth * mZoom;
	sizeTotal.cy = mapHeight * mZoom;
	SetScrollSizes(MM_TEXT, sizeTotal);

	mScroll = GetDeviceScrollPosition();

	// 미니맵의 사이즈도 같이 변경해준다.
	CRect& miniMap = mMainFrame->mMiniMapView->MiniMapSizeProp();
	FLOAT center;

	if (mapWidth > mapHeight)
	{
		center = miniMap.bottom / 2;

		miniMap.bottom *= mapHeight / mapWidth;
		miniMap.top = center - miniMap.bottom / 2;
		miniMap.bottom += miniMap.top;
	}
	else
	{
		center = miniMap.right / 2;

		miniMap.right *= mapWidth / mapHeight;
		miniMap.left = center - miniMap.right / 2;
		miniMap.right += miniMap.top;
	}
}

// Draw2D를 사용하기 때문에 쓰지않음.
void Editor::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

void Editor::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// Single Document라서 그런지.. Doc에서 새 파일을 하거나, 파일을 읽어올 때
	// 모든 View의 OnInitialUpdate함수를 호출한다.. 그래서 한번만 호출되도록 처리를 했다.
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

		// Scroll Bar 사이즈 초기화
		CSize sizeTotal;

		sizeTotal.cx = mTileWidth * mTileXAmount;
		sizeTotal.cy = mTileHeight * mTileYAmount;
		SetScrollSizes(MM_TEXT, sizeTotal);

		SizeChange(mTileXAmount, mTileYAmount);

		// Timer 설정
		SetTimer(static_cast<UINT_PTR>(eEventMessage::REDRAW), 7/*144FPS*/, nullptr);

		callOnce = false;
	}
}

// Editor 메시지 처리기

void Editor::OnDestroy()
{
	CScrollView::OnDestroy();

	KillTimer(static_cast<UINT_PTR>(eEventMessage::REDRAW));
}

afx_msg LRESULT Editor::OnDraw2D(WPARAM wParam, LPARAM lParam)
{
	CHwndRenderTarget* pRT = (CHwndRenderTarget*)lParam;
	ASSERT_VALID(pRT);

	// 1회에 호출하여 백버퍼 랜더 타겟을 생성하고 그린다.
	// 만약 사이즈 변경이 생긴다면 다시 호출하긴 한다..
	if (callOnce != false)
		CreateBackBufferRT(pRT);

	CRect clientRect;
	GetClientRect(&clientRect);

	pRT->Clear(mWhiteBrush->GetColor());

	// mImage[1]은 백그라운드 이미지. 임시로 그려준다.
	pRT->DrawBitmap(mImages[1],
		CRect(0, clientRect.bottom / mZoom - mImages[1]->GetSize().height,
			mImages[1]->GetSize().width, clientRect.bottom / mZoom));

	// mZoom 값에 인한 Scale 확대, 감소
	pRT->SetTransform(D2D1::IdentityMatrix());
	pRT->SetTransform(D2D1::Matrix3x2F::Scale(D2D1_SIZE_F({ mZoom, mZoom })));

	// 백버퍼의 내용 중에 화면에 출력할 부분만 잘라서 옮겨그린다.
	CD2DRectF temp(mScroll.x / mZoom, mScroll.y / mZoom, (mScroll.x + clientRect.Width()) / mZoom, (mScroll.y + clientRect.Height()) / mZoom);

	// 맵 버퍼의 내용을 그린다.
	pRT->DrawBitmap(mTileBackBuffer, CD2DRectF(0, 0, clientRect.Width() / mZoom, clientRect.Height() / mZoom), 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &temp);

	// 타일 주소 내용을 그린다.
	if (mbIsTileIndexOn == true)
		pRT->DrawBitmap(mIndexBackBuffer, CD2DRectF(0, 0, clientRect.Width() / mZoom, clientRect.Height() / mZoom), 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &temp);

	// 그리드를 그린다.
	if (mbIsGridOn == true)
		pRT->DrawBitmap(mGridBackBuffer, CD2DRectF(0, 0, clientRect.Width() / mZoom, clientRect.Height() / mZoom), 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &temp);

	// 커서 위치에 해당되는 타일들의 테두리를 그린다.
	DrawCursorBox(pRT);

	return TRUE;
}

BOOL Editor::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta >= 0)
	{
		// Zoom in
		mZoom += 0.1f;

		if (mZoom > ZOOM_MAX)
			mZoom = ZOOM_MAX;
	}
	else
	{
		mZoom -= 0.1f;

		// Zoom out
		if (mZoom < ZOOM_MIN)
			mZoom = ZOOM_MIN;
	}

	// 줌 변경으로 인한 스크린 사이즈 변경
	CSize sizeTotal;

	sizeTotal.cx = (mTileWidth * mTileXAmount) * mZoom;
	sizeTotal.cy = (mTileHeight * mTileYAmount) * mZoom;
	SetScrollSizes(MM_TEXT, sizeTotal);

	mScroll = GetDeviceScrollPosition();

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void Editor::OnMouseMove(UINT nFlags, CPoint point)
{
	// Zoom이 적용된 가로, 세로 길이
	FLOAT width = mTileWidth * mZoom;
	FLOAT height = mTileHeight * mZoom;

	// 현재 마우스의 위치 + 스크롤 바의 위치를 더해서
	// 새로 구한 가로 세로 길이를 나누어 마우스의 타일 좌표를 구한다.
	mPrevCursorIndex = mCursorIndex;
	mCursorIndex = { static_cast<int>((point.x + mScroll.x) / width), static_cast<int>((point.y + mScroll.y) / height) };

	// 혹시 모를 예외 처리
	if (mCursorIndex.x < 0)	mCursorIndex.x = 0;
	if (mCursorIndex.y < 0)	mCursorIndex.y = 0;
	if (mCursorIndex.x >= mTileXAmount) mCursorIndex.x = mTileXAmount - 1;
	if (mCursorIndex.y >= mTileYAmount) mCursorIndex.y = mTileYAmount - 1;

	mbIsCanSetTile = true;

	// Terrain은 아예 중복되지 않게 처리한다.
	if (mTiles[mCursorIndex.y][mCursorIndex.x].ID != 0)
	{
		mbIsCanSetTile = false;
	}
	else
	{
		// Object가 중복된 ID 혹은 Terrain과는 겹쳐서 놓을 수 없도록 해준다.
		ControlProperty* ctrlProp = mMainFrame->mControlView->mControlSheet;
		ItemData temp = ctrlProp->GetSelectedItemData();

		if (temp.layer != 0)
		{
			// 중복 ID 검사
			for (int i = 0; i < mObjects[mCursorIndex.y][mCursorIndex.x].size(); i++)
			{
				if (temp.ID == mObjects[mCursorIndex.y][mCursorIndex.x][i].ID)
				{
					mbIsCanSetTile = false;
					break;
				}
			}

			// 선택된 오브젝트의 Group의 타일 위치 또한 검사한다.
			for (int i = 0; i < temp.group.size() && mbIsCanSetTile == true; i++)
			{
				if (temp.group[i] != 0)
				{
					int x = mCursorIndex.x + (temp.group[i] & 0xffff);
					int y = mCursorIndex.y + (temp.group[i] >> 16);

					if (x >= mTileXAmount || y >= mTileYAmount)
					{
						mbIsCanSetTile = false;
						break;
					}

					if (mTiles[y][x].ID != 0)
					{
						mbIsCanSetTile = false;
						break;
					}

					if (ctrlProp->GetItemType() == eItemType::Object)
					{
						for (int j = 0; j < mObjects[y][x].size(); j++)
						{
							if (temp.ID == mObjects[y][x][j].ID)
							{
								mbIsCanSetTile = false;
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			mbIsCanSetTile = false;
		}
	}

	// 마우스의 이전 좌표와 현재 좌표를 기준으로 타일을 입력한다.
	SetDataToTile();

	// 마우스가 View 밖으로 벗어나는지 확인
	if (mbMouseTrack == false)
	{
		TRACKMOUSEEVENT MouseEvent;
		ZeroMemory(&MouseEvent, sizeof(MouseEvent));
		MouseEvent.cbSize = sizeof(MouseEvent);
		MouseEvent.dwFlags = TME_LEAVE;
		MouseEvent.hwndTrack = m_hWnd;
		MouseEvent.dwHoverTime = 0;
		mbMouseTrack = _TrackMouseEvent(&MouseEvent);
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void Editor::OnMouseLeave()
{
	// 마우스가 떠났을 때 그리기 상태를 해제한다.
	mbLButtonDown = false;
	mbRButtonDown = false;
	mbMouseTrack = false;

	CScrollView::OnMouseLeave();
}

void Editor::OnLButtonDown(UINT nFlags, CPoint point)
{
	mbLButtonDown = true;

	// 선택중인 타일 정보 받아서 타일에 입력
	SetTargetTile(mCursorIndex);

	CScrollView::OnLButtonDown(nFlags, point);
}

void Editor::OnLButtonUp(UINT nFlags, CPoint point)
{
	mbLButtonDown = false;

	CScrollView::OnLButtonUp(nFlags, point);
}

void Editor::OnRButtonDown(UINT nFlags, CPoint point)
{
	mbRButtonDown = true;

	PopTargetTile(mCursorIndex);

	CScrollView::OnRButtonDown(nFlags, point);
}

void Editor::OnRButtonUp(UINT nFlags, CPoint point)
{
	mbRButtonDown = false;

	CScrollView::OnRButtonUp(nFlags, point);
}

void Editor::OnTimer(UINT_PTR nIDEvent)
{
	switch (static_cast<eEventMessage>(nIDEvent))
	{
		// 화면 갱신
	case eEventMessage::REDRAW:
		InvalidateRect(nullptr);
		break;
	}

	CScrollView::OnTimer(nIDEvent);
}

void Editor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	mScroll = GetDeviceScrollPosition();

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void Editor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	mScroll = GetDeviceScrollPosition();

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}