#pragma once
#include "PageManager.h"

// Terrain 대화 상자

/// <summary>
/// 지형과 관련된 타일을 모아두는 Page
/// 
/// 2022. 02. 07 JK
/// </summary>
class Terrain : public PageManager
{
	DECLARE_DYNAMIC(Terrain)

public:
	Terrain();
	virtual ~Terrain();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Terrain };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl mTerrainTree;
	CStatic mSelected;
	CStatic mImageID;
	CStatic mPath;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTvnSelchangedTerraintree(NMHDR* pNMHDR, LRESULT* pResult);
};