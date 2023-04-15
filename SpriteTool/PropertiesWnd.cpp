
#include "pch.h"
#include "framework.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "SpriteTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd() noexcept
	: mSpriteInfo(nullptr)
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CPropertiesWnd::OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 메시지 처리기

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = mWndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	//mWndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	mWndPropList.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), rectClient.Height() - m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 콤보 상자를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("속성 콤보 상자를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	//m_wndObjectCombo.AddString(_T("애플리케이션"));
	m_wndObjectCombo.AddString(_T("속성 창"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect(&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!mWndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	InitPropList();

	//mWndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	//mWndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);
	//mWndToolBar.CleanUpLockedImages();
	//mWndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);

	//mWndToolBar.SetPaneStyle(mWndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//mWndToolBar.SetPaneStyle(mWndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	//mWndToolBar.SetOwner(this);

	//// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	//mWndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	mWndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	mWndPropList.SetAlphabeticMode(!mWndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mWndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	mWndPropList.EnableHeaderCtrl(FALSE);
	mWndPropList.EnableDescriptionArea();
	mWndPropList.SetVSDotNetLook();
	mWndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("이미지 정보"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("테두리 출력"), (_variant_t)true, _T("이미지의 테두리를 출력합니다.")));
	pGroup1->GetSubItem(0)->SetData(static_cast<DWORD>(eProperty::BoarderLine));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("이미지 ID"), (_variant_t)0, _T("해당 스프라이트의 원본 이미지 ID입니다.")));
	pGroup1->GetSubItem(1)->AllowEdit(false);
	pGroup1->GetSubItem(1)->SetData(static_cast<DWORD>(eProperty::ImageID));

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("이미지 영역"), 0, TRUE);

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("왼쪽"), (_variant_t)0, _T("왼쪽 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ImageRectParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("위"), (_variant_t)0, _T("위쪽 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ImageRectParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("오른쪽"), (_variant_t)0, _T("오른쪽 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ImageRectParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("아래"), (_variant_t)0, _T("아래쪽 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ImageRectParts));
	pSize->AddSubItem(pProp);

	pGroup1->AddSubItem(pSize);
	pGroup1->GetSubItem(2)->SetData(static_cast<DWORD>(eProperty::ImageRect));

	pSize = new CMFCPropertyGridProperty(_T("피봇"), (_variant_t)0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("X"), (_variant_t)0, _T("X 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::PivotParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Y"), (_variant_t)0, _T("Y 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::PivotParts));
	pSize->AddSubItem(pProp);

	pGroup1->AddSubItem(pSize);
	pGroup1->GetSubItem(3)->SetData(static_cast<DWORD>(eProperty::Pivot));

	mWndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("콜라이더 정보"));

	pProp = new CMFCPropertyGridProperty(_T("콜라이더 타입"), _T("없음"), _T("없음, 원형, 사각형 중 하나를 지정합니다."));
	pProp->AddOption(_T("없음"));
	pProp->AddOption(_T("원형"));
	pProp->AddOption(_T("사각형"));
	pProp->AllowEdit(false);

	pGroup2->AddSubItem(pProp);
	pGroup2->GetSubItem(0)->SetData(static_cast<DWORD>(eProperty::ColliderType));

	pSize = new CMFCPropertyGridProperty(_T("콜라이더 영역"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("중심 X"), (_variant_t)0, _T("X 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ColliderRectParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("중심 Y"), (_variant_t)0, _T("Y 좌표를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ColliderRectParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("반지름 X"), (_variant_t)0, _T("가로 길이를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ColliderRectParts));
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("반지름 Y"), (_variant_t)0, _T("세로 길이를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 0x80000000, 0x7fffffff);
	pProp->SetData(static_cast<DWORD>(eProperty::ColliderRectParts));
	pSize->AddSubItem(pProp);

	pGroup2->AddSubItem(pSize);
	pGroup2->GetSubItem(1)->SetData(static_cast<DWORD>(eProperty::ColliderRect));

	mWndPropList.AddProperty(pGroup2);

	pProp = new CMFCPropertyGridProperty(_T("출력시간"), (_variant_t)0.0, _T("해당 스프라이트의 출력 시간입니다."));
	mWndPropList.AddProperty(pProp);
	mWndPropList.GetProperty(2)->SetData(static_cast<DWORD>(eProperty::Duration));
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	mWndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	mWndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::SetSpriteProperty(SpriteInfo* spriteInfo)
{
	mSpriteInfo = spriteInfo;

	// 이미지 ID
	SetImageID(mSpriteInfo->imageID);

	// 이미지 Rect
	SetImageRectFromSprite(mSpriteInfo->imageRect);

	// 피봇
	SetPivotFromSprite(mSpriteInfo->pivot);

	// 콜라이더
	SetColliderTypeFromSprite(mSpriteInfo->collider);

	// 지속시간
	SetDuration(mSpriteInfo->duration);
}

void CPropertiesWnd::SetColliderTypeFromSprite(ColliderInfo colliderInfo)
{
	if (mSpriteInfo != nullptr)
	{
		mSpriteInfo->collider = colliderInfo;

		if (mSpriteInfo->collider.type == 0)
		{
			mWndPropList.GetProperty(1)->GetSubItem(0)->SetValue(_T("없음"));
			mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(3)->Show(true);
		}
		else if (mSpriteInfo->collider.type == 1)
		{
			mWndPropList.GetProperty(1)->GetSubItem(0)->SetValue(_T("원형"));
			mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(3)->Show(false);
		}
		else if (mSpriteInfo->collider.type == 2)
		{
			mWndPropList.GetProperty(1)->GetSubItem(0)->SetValue(_T("사각형"));
			mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(3)->Show(true);
		}

		_variant_t var = mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(0)->GetValue();
		var.intVal = mSpriteInfo->collider.rect.left;
		mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(0)->SetValue(var);

		var = mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(1)->GetValue();
		var.intVal = mSpriteInfo->collider.rect.top;
		mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(1)->SetValue(var);

		var = mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(2)->GetValue();
		var.intVal = mSpriteInfo->collider.rect.right;
		mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(2)->SetValue(var);

		var = mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(3)->GetValue();
		var.intVal = mSpriteInfo->collider.rect.bottom;
		mWndPropList.GetProperty(1)->GetSubItem(1)->GetSubItem(3)->SetValue(var);
	}
}

void CPropertiesWnd::SetColliderRectFromProp(CMFCPropertyGridProperty* prop)
{
	if (mSpriteInfo != nullptr)
	{
		_variant_t var = prop->GetSubItem(0)->GetValue();
		mSpriteInfo->collider.rect.left = var.intVal;

		var = prop->GetSubItem(1)->GetValue();
		mSpriteInfo->collider.rect.top = var.intVal;

		var = prop->GetSubItem(2)->GetValue();
		mSpriteInfo->collider.rect.right = var.intVal;

		if (mSpriteInfo->collider.type == 1)
		{
			int radius = var.intVal;

			var = prop->GetSubItem(3)->GetValue();
			var.intVal = radius;
			mSpriteInfo->collider.rect.bottom = radius;
			prop->GetSubItem(3)->SetValue(var);
		}
		else
		{
			var = prop->GetSubItem(3)->GetValue();
			mSpriteInfo->collider.rect.bottom = var.intVal;
		}
	}
}

void CPropertiesWnd::SetColliderTypeFromProp(CMFCPropertyGridProperty* prop)
{
	if (mSpriteInfo != nullptr)
	{
		CString str;
		str.Format(_T("%s"), prop->GetValue().bstrVal);

		if (str == _T("없음"))
		{
			mSpriteInfo->collider.type = 0;
			prop->GetParent()->GetSubItem(1)->GetSubItem(3)->Show(true);
		}
		else if (str == _T("원형"))
		{
			mSpriteInfo->collider.type = 1;
			prop->GetParent()->GetSubItem(1)->GetSubItem(3)->Show(false);
		}
		else if (str == _T("사각형"))
		{
			mSpriteInfo->collider.type = 2;
			prop->GetParent()->GetSubItem(1)->GetSubItem(3)->Show(true);
		}
	}
}

void CPropertiesWnd::SetImageID(UINT imageID)
{
	if (mSpriteInfo != nullptr)
	{
		mSpriteInfo->imageID = imageID;

		_variant_t var = mWndPropList.GetProperty(0)->GetSubItem(1)->GetValue();
		var.intVal = mSpriteInfo->imageID;
		mWndPropList.GetProperty(0)->GetSubItem(1)->SetValue(var);
	}
}

void CPropertiesWnd::SetImageRectFromSprite(CD2DRectF rect)
{
	if (mSpriteInfo != nullptr)
	{
		mSpriteInfo->imageRect = rect;

		_variant_t var = mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(0)->GetValue();
		var.intVal = mSpriteInfo->imageRect.left;
		mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(0)->SetValue(var);

		var = mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(1)->GetValue();
		var.intVal = mSpriteInfo->imageRect.top;
		mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(1)->SetValue(var);

		var = mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(2)->GetValue();
		var.intVal = mSpriteInfo->imageRect.right;
		mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(2)->SetValue(var);

		var = mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(3)->GetValue();
		var.intVal = mSpriteInfo->imageRect.bottom;
		mWndPropList.GetProperty(0)->GetSubItem(2)->GetSubItem(3)->SetValue(var);
	}
}

void CPropertiesWnd::SetImageRectFromProp(CMFCPropertyGridProperty* prop)
{
	if (mSpriteInfo != nullptr)
	{
		_variant_t var = prop->GetSubItem(0)->GetValue();
		mSpriteInfo->imageRect.left = var.intVal;

		var = prop->GetSubItem(1)->GetValue();
		mSpriteInfo->imageRect.top = var.intVal;

		var = prop->GetSubItem(2)->GetValue();
		mSpriteInfo->imageRect.right = var.intVal;

		var = prop->GetSubItem(3)->GetValue();
		mSpriteInfo->imageRect.bottom = var.intVal;
	}
}

void CPropertiesWnd::SetPivotFromSprite(CPoint pivot)
{
	if (mSpriteInfo != nullptr)
	{
		mSpriteInfo->pivot = pivot;

		_variant_t var = mWndPropList.GetProperty(0)->GetSubItem(3)->GetSubItem(0)->GetValue();
		var.intVal = mSpriteInfo->pivot.x;
		mWndPropList.GetProperty(0)->GetSubItem(3)->GetSubItem(0)->SetValue(var);

		var = mWndPropList.GetProperty(0)->GetSubItem(3)->GetSubItem(1)->GetValue();
		var.intVal = mSpriteInfo->pivot.y;
		mWndPropList.GetProperty(0)->GetSubItem(3)->GetSubItem(1)->SetValue(var);
	}
}

void CPropertiesWnd::SetPivotFromProp(CMFCPropertyGridProperty* prop)
{
	if (mSpriteInfo != nullptr)
	{
		_variant_t var = prop->GetSubItem(0)->GetValue();
		mSpriteInfo->pivot.x = var.intVal;

		var = prop->GetSubItem(1)->GetValue();
		mSpriteInfo->pivot.y = var.intVal;
	}
}

void CPropertiesWnd::SetDuration(double duration)
{
	if (mSpriteInfo != nullptr)
	{
		mSpriteInfo->duration = duration;

		_variant_t var = mWndPropList.GetProperty(2)->GetValue();
		var.dblVal = mSpriteInfo->duration;
		mWndPropList.GetProperty(2)->SetValue(var);
	}
}

afx_msg LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;

	if (pProp != nullptr)
	{
		switch (static_cast<eProperty>(pProp->GetData()))
		{
		case eProperty::BoarderLine:
			OutputDebugString(_T("\n BoarderLine \n"));
			break;
		case eProperty::ImageID:
			OutputDebugString(_T("\n ImageID \n"));
			SetImageID(pProp->GetValue().intVal);
			break;
		case eProperty::ImageRect:
			OutputDebugString(_T("\n ImageRect \n"));
			SetImageRectFromProp(pProp);
			break;
		case eProperty::ImageRectParts:
			OutputDebugString(_T("\n ImageRectParts \n"));
			SetImageRectFromProp(pProp->GetParent());
			break;
		case eProperty::Pivot:
			OutputDebugString(_T("\n Pivot \n"));
			SetPivotFromProp(pProp);
			break;
		case eProperty::PivotParts:
			OutputDebugString(_T("\n PivotParts \n"));
			SetPivotFromProp(pProp->GetParent());
			break;
		case eProperty::ColliderType:
			OutputDebugString(_T("\n ColliderType \n"));
			SetColliderTypeFromProp(pProp);
			break;
		case eProperty::ColliderRect:
			OutputDebugString(_T("\n ColliderRect \n"));
			SetColliderRectFromProp(pProp);
			break;
		case eProperty::ColliderRectParts:
			OutputDebugString(_T("\n ColliderRectParts \n"));
			SetColliderRectFromProp(pProp->GetParent());
			break;
		case eProperty::Duration:
			OutputDebugString(_T("\n Duration \n"));
			SetDuration(pProp->GetValue().dblVal);
			break;
		}
	}

	return true;
}

bool CPropertiesWnd::GetPrintBoarderLine()
{
	return mWndPropList.GetProperty(0)->GetSubItem(0)->GetValue().boolVal;
}