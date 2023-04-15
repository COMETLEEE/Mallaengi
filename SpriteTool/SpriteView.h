
#pragma once
#include "JsonManager.h"
#include "ViewTree.h"

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};


class CSpriteViewTree : public CViewTree
{

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};

class CSpriteView : public CDockablePane
{
public:
	CSpriteView() noexcept;
	virtual ~CSpriteView();

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	CClassToolBar mWndToolBar;
	CSpriteViewTree mWndSpriteView;
	CImageList mSpriteViewImages;
	UINT mCurrSort;
	INT mCount;

public:
	map<UINT, SpriteInfo> mSpriteList;

	void FillSpriteView();

	// 재정의입니다.
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

public:
	void Init();
	void Insert(UINT imageID, const CD2DRectF& imageRect, double duration = 0.1, CPoint pivot = {}, const ColliderInfo& collider = {});

	void SaveFile(const string& path);
	string SaveFile();
	void LoadFile(const string& path);
	void LoadFileForMFC(const string& data);
};