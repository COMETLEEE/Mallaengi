
// MapToolDoc.cpp: CMapToolDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#endif

#include "MapToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMapToolDoc

IMPLEMENT_DYNCREATE(CMapToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapToolDoc, CDocument)
	ON_COMMAND(ID_GRID_VIEW, &CMapToolDoc::OnGridView)
	ON_COMMAND(ID_TILE_INDEX_VIEW, &CMapToolDoc::OnTileIndexView)
	ON_COMMAND(ID_TileChange, &CMapToolDoc::OnTileChange)
END_MESSAGE_MAP()


// CMapToolDoc 생성/소멸

CMapToolDoc::CMapToolDoc() noexcept
{
}

CMapToolDoc::~CMapToolDoc()
{
}

BOOL CMapToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// 새 파일을 눌렀을 때 에디터를 초기화한다.
	CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

	if (mainFrame != nullptr)
	{
		mainFrame->mEditorView->InitTiles();
		mainFrame->mEditorView->DrawAllTiles();
	}

	return TRUE;
}

// CMapToolDoc serialization

void CMapToolDoc::Serialize(CArchive& ar)
{
	CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

	ar.GetFile();

	if (ar.IsStoring())
	{
		// 저장하는 부분
		if (mainFrame != nullptr)
		{
			// Json형태의 문자열로 만들어서 CArchive로 저장한다.
			// 섞어쓴 이유는 일단 여기서 CArchive로 저장하고 클라이언트 쪽에서 Json으로 불러오는게 가능할 줄 알았는데
			// CArchive의 문자 저장방식이 독특해서 원하는대로 잘되지 않았다.
			CString str;
			str = mainFrame->mEditorView->SaveFile().c_str();
			ar << str;
		}
	}
	else
	{
		// 불러오는 부분
		if (mainFrame != nullptr)
		{
			// CArchive에서 파일을 읽어와서 string으로 변환 후 Json으로 역직렬화 작업을 한다.
			CString str;
			ar.ReadString(str);
			string data;
			data = CT2CA(str);
			mainFrame->mEditorView->LoadFileFromData(data);
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMapToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMapToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMapToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMapToolDoc 진단

#ifdef _DEBUG
void CMapToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CMapToolDoc 명령

/// <summary>
/// 에디터 뷰의 Grid를 On/Off 시키는 메뉴 버튼
/// </summary>
void CMapToolDoc::OnGridView()
{
	bool* targetVariable = &dynamic_cast<CMainFrame*>(theApp.m_pMainWnd)->mEditorView->mbIsGridOn;
	*targetVariable = !*targetVariable;

	theApp.m_pMainWnd->GetMenu()->CheckMenuItem(ID_GRID_VIEW, MF_UNCHECKED | (0x8L * *targetVariable));
}

void CMapToolDoc::OnTileIndexView()
{
	bool* targetVariable = &dynamic_cast<CMainFrame*>(theApp.m_pMainWnd)->mEditorView->mbIsTileIndexOn;
	*targetVariable = !*targetVariable;

	theApp.m_pMainWnd->GetMenu()->CheckMenuItem(ID_TILE_INDEX_VIEW, MF_UNCHECKED | (0x8L * *targetVariable));
}

void CMapToolDoc::OnTileChange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	TileChangerBox tcBox;

	// 타일 사이즈 변경하는 대화상자
	INT_PTR result = tcBox.DoModal();

	if (result == IDOK)
	{
		CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

		INT x = atoi(CT2CA(tcBox.mX));
		INT y = atoi(CT2CA(tcBox.mY));

		mainFrame->mEditorView->SizeChange(x, y);
	}
}