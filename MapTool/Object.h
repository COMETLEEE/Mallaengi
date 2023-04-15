#pragma once
#include "PageManager.h"

// Object 대화 상자

/// <summary>
/// 객체와 관련된 타일을 모아두는 Page
/// 
/// 2022. 02. 07 JK
/// </summary>
class Object : public PageManager
{
	DECLARE_DYNAMIC(Object)

public:
	Object();
	virtual ~Object();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Object };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl mObjectTree;
	CStatic mSelected;
	CStatic mImageID;
	CStatic mPath;
	afx_msg void OnDestroy();
	afx_msg void OnTvnSelchangedObjecttree(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};