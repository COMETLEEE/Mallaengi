
// SpriteToolDoc.cpp: CSpriteToolDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "JsonManager.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SpriteTool.h"
#endif

#include "SpriteToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSpriteToolDoc

IMPLEMENT_DYNCREATE(CSpriteToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpriteToolDoc, CDocument)
END_MESSAGE_MAP()


// CSpriteToolDoc 생성/소멸

CSpriteToolDoc::CSpriteToolDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSpriteToolDoc::~CSpriteToolDoc()
{
}

BOOL CSpriteToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

	if (mainFrame != nullptr)
	{
		mainFrame->mWndSpriteView.Init();
		mainFrame->mWndAnimationView.mSpriteID = 0;
	}

	return TRUE;
}

// CSpriteToolDoc serialization

void CSpriteToolDoc::Serialize(CArchive& ar)
{
	ar.GetFile();

	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.

		CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

		if (mainFrame != nullptr)
		{
			CString str;
			str = mainFrame->mWndSpriteView.SaveFile().c_str();
			ar << str;
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.

		CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

		if (mainFrame != nullptr)
		{
			mainFrame->mWndSpriteView.Init();
			mainFrame->mWndAnimationView.mSpriteID = 0;

			CString str;
			ar.ReadString(str);
			string data;
			data = CT2CA(str);
			mainFrame->mWndSpriteView.LoadFileForMFC(data);
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSpriteToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSpriteToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSpriteToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSpriteToolDoc 진단

#ifdef _DEBUG
void CSpriteToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpriteToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSpriteToolDoc 명령
