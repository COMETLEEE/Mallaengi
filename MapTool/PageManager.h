#pragma once

#include "JsonManager.h"
#include <map>

using std::map;

/// <summary>
/// 다형적 동작을 위한 PageManager
/// Page별로 선택중인 대상을 가져오기 위해 사용
/// 
/// 2022. 02. 07 JK
/// </summary>
class PageManager : public CPropertyPage
{
protected:
	// 타일 Resource 정보
	map<UINT, ItemData> mResourcesData;
	map<UINT, CD2DBitmap*> mImages;

	// Text Format
	CD2DTextFormat* mTextFormat;	// Tile Index 출력을 위한 TextFormat

	// Brush
	CD2DSolidColorBrush* mBlackBrush;	// Grid, Text

	// Font
	CFont mStaticFont;

	// Tree Control
	CTreeCtrl* mTree;

	// 선택된 대상
	CStatic* mSelectedItem;
	CStatic* mSelectedImageID;
	CStatic* mSelectedPath;

public:
	// Type
	string mType;

	// 선택된 대상의 ItemData
	ItemData	mSelectedData;

protected:
	PageManager() = delete;
	PageManager(UINT nIDTemplate, CTreeCtrl* tree, CStatic* selected, CStatic* imageID, CStatic* path);
	virtual ~PageManager();

protected:
	void CreateD2D();
	HRESULT AddImage(UINT imageID, CString path);
	HTREEITEM AddItem(CString itemName, HTREEITEM root = TVI_ROOT, ItemData itemData = {});
	void PictureRender(ItemData iData);

	void SelectedItem(LPNMTREEVIEW pNMTreeView);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};