
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 창입니다.

class CViewTree : public CTreeCtrl
{
// 생성입니다.
public:
	CViewTree() noexcept;

// 재정의입니다.
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	HTREEITEM hRoot;

// 구현입니다.
public:
	virtual ~CViewTree();
	//virtual void OnSelected(NMHDR* pNMHDR, LRESULT* pResult) abstract;

protected:
	DECLARE_MESSAGE_MAP()
};
