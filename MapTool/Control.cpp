// Control.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "Control.h"

// Control

IMPLEMENT_DYNCREATE(Control, CFormView)

Control::Control()
	: CFormView(IDD_Control)
	, mControlSheet(nullptr)
{

}

Control::~Control()
{

}

// Control 진단

#ifdef _DEBUG
void Control::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Control::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void Control::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Control, CFormView)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// Control 메시지 처리기

void Control::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	static bool callOnce = true;

	if (callOnce == true)
	{
		// 스크롤바 없애기
		SetScrollSizes(MM_TEXT, CSize(0, 0));

		// 시트 생성
		CRect rect;
		GetClientRect(rect);
		mControlSheet = new ControlProperty(IDD_Control, this);
		mControlSheet->Create(this, WS_CHILD | WS_VISIBLE);
		mControlSheet->MoveWindow(0, 0, rect.Width() - 10, 600, TRUE);
		mControlSheet->SetActivePage(0); // Terrain page

		callOnce = false;
	}
}

void Control::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (mControlSheet != nullptr)
	{
		delete mControlSheet;
		mControlSheet = nullptr;
	}
}