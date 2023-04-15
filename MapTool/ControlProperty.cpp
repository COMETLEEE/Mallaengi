// ControlProperty.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "ControlProperty.h"

// ControlProperty

IMPLEMENT_DYNAMIC(ControlProperty, CPropertySheet)

ControlProperty::ControlProperty(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
{
	AddPage(&mTerrain);
	AddPage(&mObject);
}

ControlProperty::ControlProperty(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

ControlProperty::~ControlProperty()
{

}

/// <summary>
/// 활성화된 페이지의 선택 대상을 가져온다.
/// </summary>
const ItemData& ControlProperty::GetSelectedItemData()
{
	PageManager* currPage = dynamic_cast<PageManager*>(GetActivePage());

	return currPage->mSelectedData;
}

eItemType ControlProperty::GetItemType()
{
	PageManager* currPage = dynamic_cast<PageManager*>(GetActivePage());

	if (currPage->mType.compare("Terrain") == 0)
	{
		return eItemType::Terrain;
	}
	else if (currPage->mType.compare("Object") == 0)
	{
		return eItemType::Object;
	}

	return eItemType::NONE;
}

const string& ControlProperty::GetItemTypeString()
{
	PageManager* currPage = dynamic_cast<PageManager*>(GetActivePage());

	return currPage->mType;
}

BEGIN_MESSAGE_MAP(ControlProperty, CPropertySheet)
END_MESSAGE_MAP()

// ControlProperty 메시지 처리기