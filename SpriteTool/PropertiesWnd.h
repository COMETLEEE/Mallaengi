
#pragma once
#include <vector>

using std::vector;

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
	enum class eProperty
	{
		BoarderLine,
		ImageID,
		ImageRect,
		ImageRectParts,
		Pivot,
		PivotParts,
		ColliderType,
		ColliderRect,
		ColliderRectParts,
		Duration
	};

// 생성입니다.
public:
	CPropertiesWnd() noexcept;

	void AdjustLayout();

// 특성입니다.
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		mWndPropList.SetVSDotNetLook(bSet);
		mWndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar mWndToolBar;
	CMFCPropertyGridCtrl mWndPropList;
	SpriteInfo* mSpriteInfo;

// 구현입니다.
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;

public:
	void SetSpriteProperty(SpriteInfo* spriteInfo);
	void SetColliderTypeFromSprite(ColliderInfo colliderInfo);
	void SetColliderRectFromProp(CMFCPropertyGridProperty* prop);
	void SetColliderTypeFromProp(CMFCPropertyGridProperty* prop);
	void SetImageID(UINT imageID);
	void SetImageRectFromSprite(CD2DRectF rect);
	void SetImageRectFromProp(CMFCPropertyGridProperty* prop);
	void SetPivotFromSprite(CPoint pivot);
	void SetPivotFromProp(CMFCPropertyGridProperty* prop);
	void SetDuration(double duration);
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);

	bool GetPrintBoarderLine();
};