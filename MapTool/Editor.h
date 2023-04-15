#pragma once

#include "JsonManager.h"
#include <vector>
#include <map>
#include <algorithm>

using std::map;
using std::vector;

class CMainFrame;

// Editor 보기

/// <summary>
/// 맵툴 실제 작업 View 영역
/// 
/// 2022. 02. 07 JK
/// </summary>
class Editor : public CScrollView
{
	DECLARE_DYNCREATE(Editor)

	enum class eEventMessage
	{
		REDRAW = 0,
		LASTOFENUM
	};

#pragma region MyVariable
protected:
	// Text Format
	CD2DTextFormat* mTextFormat;	// Tile Index 출력을 위한 TextFormat

	// Brush
	CD2DSolidColorBrush* mBlackBrush;	// Grid, Text
	CD2DSolidColorBrush* mWhiteBrush;	// BackGround
	CD2DSolidColorBrush* mAlphaBrush;	// BackGround
	CD2DSolidColorBrush* mGreenBrush;	// Cursor Index Box
	CD2DSolidColorBrush* mRedBrush;	// Cursor Index Box

	// Resources
	map<UINT, CD2DBitmap*> mImages;	// Image Resource

	// Back Buffer, 여기서 필요한 부분을 잘라서 사용
	CBitmapRenderTarget* mTileRT;	// 타일
	CD2DBitmap* mTileBackBuffer;	// Tile Bitmap
	CBitmapRenderTarget* mIndexRT;	// 타일 주소
	CD2DBitmap* mIndexBackBuffer;	// Index Bitmap
	CBitmapRenderTarget* mGridRT;	// 그리드
	CD2DBitmap* mGridBackBuffer;	// Grid Bitmap

	// Tile
	INT	mTileWidth;		// 타일의 가로 길이
	INT	mTileHeight;	// 타일의 세로 길이
	INT	mTileXAmount;	// 타일의 가로 갯수
	INT	mTileYAmount;	// 타일의 세로 갯수

public:
	vector<vector<TileData>> mTiles;			// Terrain 정보
	vector<vector<vector<TileData>>> mObjects;	// Object 정보

protected:
	// Mouse
	CPoint	mCursorIndex;		// 마우스의 타일 좌표
	CPoint	mPrevCursorIndex;	// 마우스의 이전 타일 좌표
	bool	mbLButtonDown;
	bool	mbRButtonDown;
	bool	mbMouseTrack;		// 마우스가 화면 안인지 밖인지 확인
	bool	mbIsCanSetTile;		// 타일을 놓을 수 있는가에 대한 관련 처리

	// Screen Control
	FLOAT	mZoom;				// Zoom In, Zoom Out
	CPoint	mScroll;			// X, Y 스크롤의 상태

public:
	// On/Off Toggle
	// Doc에서 메뉴 호출로 온/오프한다.
	bool	mbIsGridOn;
	bool	mbIsTileIndexOn;

	// Draw2D에서 랜더타겟받고 호환되는 백버퍼를 만들 때 사용하는 bool 변수
	bool callOnce;

protected:
	// ETC
	CMainFrame* mMainFrame;
#pragma endregion

protected:
	Editor();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Editor();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

#pragma region MyFunction
private:
	// MFC에서 지원하는 D2D 초기 설정과 랜더타겟을 받고 백버퍼 생성하는 함수
	void CreateD2D();
	void CreateBackBufferRT(CHwndRenderTarget* pRT);

	// 백버퍼에 내용을 그린다. 백버퍼는 맵을 그리는 버퍼와 그리드 버퍼 인덱스 버퍼가 나뉘어 있다.
	void DrawBackBuffer();

	// 최적화를 위해 변경된 특정 타일만 선택하여 그리기 작업을 한다.
	void DrawTargetTile(CPoint tile);
	void DrawGrid();
	void DrawTileIndex(CPoint tile);

	// 커서의 위치 혹은 현재 선택중인 오브젝트가 있을 때 그 크기만큼의 테두리를 그린다.
	// 테두리는 타일을 놓을 수 있다면 녹색 아닐 경우 빨간색
	void DrawCursorBox(CHwndRenderTarget* pRT);

	// 파일로부터 읽어와서 타일에 저장
	void SetDataToTile();

	void SetTargetTile(CPoint tile);
	void PopTargetTile(CPoint tile);

public:
	// 미니맵에서 사용하기위해 현재 에디터 뷰에 보여지는 위치 정보를 전달한다.
	CD2DPointF	GetScrollPercent();
	CD2DPointF	GetScreenPercent();

	void SetScroll(CD2DPointF percent);
	HRESULT AddImage(UINT imageID, CString path);

	void InitTiles();
	void DrawAllTiles();

	void SaveFile(string path);
	string SaveFile();
	void SaveData(MapJson& mapJson);

	void LoadFile(string path);
	void LoadFileFromData(string data);
	void LoadData(MapJson& mapJson);

	void SizeChange(INT xAmount, INT yAmount);

#pragma endregion

protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);

	// Mouse 동작 관련 메시지 호출 함수
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	// 타이머
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 스크롤
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};