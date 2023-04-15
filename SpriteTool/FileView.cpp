
#include "pch.h"
#include "framework.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "SpriteTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


// ImageIDGetterDlg 대화 상자

IMPLEMENT_DYNAMIC(ImageIDGetterDlg, CDialog)

ImageIDGetterDlg::ImageIDGetterDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ImageID_Getter, pParent)
	, mImageID(0)
{

}

ImageIDGetterDlg::~ImageIDGetterDlg()
{
}

void ImageIDGetterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mGetImageID);
}

BEGIN_MESSAGE_MAP(ImageIDGetterDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ImageIDGetterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ImageIDGetterDlg 메시지 처리기

void ImageIDGetterDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;

	mGetImageID.GetWindowText(str);

	mImageID = atoi(CT2CA(str));

	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView() noexcept
	: mLoadDlg(true, _T("png"), _T("*.png"), 6U, _T("Png File (*.png)|*.png||"))
{

}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 메시지 처리기

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 뷰를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!mWndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("파일 뷰를 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// 뷰 이미지를 로드합니다.
	mFileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	mWndFileView.SetImageList(&mFileViewImages, TVSIL_NORMAL);

	//mWndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	//mWndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 잠금 */);

	OnChangeVisualStyle();

	//mWndToolBar.SetPaneStyle(mWndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//mWndToolBar.SetPaneStyle(mWndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//mWndToolBar.SetOwner(this);

	//// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	//mWndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 정적 트리 뷰 데이터를 더미 코드로 채웁니다.
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
	mWndFileView.hRoot = mWndFileView.InsertItem(_T("원본 이미지 파일"), 0, 0);
	mWndFileView.SetItemState(mWndFileView.hRoot, TVIS_BOLD, TVIS_BOLD);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&mWndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 클릭한 항목을 선택합니다.
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != nullptr)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = mWndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//mWndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	mWndFileView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("속성...."));

}

void CFileView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if (mLoadDlg.DoModal() == IDOK)
	{
		if (mImgIDGetterDlg.DoModal() == IDOK)
		{
			UINT imageID = mImgIDGetterDlg.mImageID;

			mWndFileView.mImages[mLoadDlg.GetFileTitle()] = { imageID, mLoadDlg.GetFileTitle(), mLoadDlg.GetPathName() };
			mWndFileView.InsertItem(mLoadDlg.GetFileTitle(), 1, 1, mWndFileView.hRoot);
			mWndFileView.Expand(mWndFileView.hRoot, TVE_EXPAND);

			CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

			if (mainFrame != nullptr)
			{
				CSpriteToolView* mainView = dynamic_cast<CSpriteToolView*>(mainFrame->GetActiveView());

				if (mainView != nullptr)
				{
					mainView->AddImage(imageID, mLoadDlg.GetPathName());
					mainFrame->mWndAnimationView.AddImage(imageID, mLoadDlg.GetPathName());
				}
			}
		}
	}
	else
	{
		// 창을 그냥 닫았을 때의 버그를 해결해야함..
	}
}

void CFileView::OnFileOpenWith()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnDummyCompile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnEditCut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnEditClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CRect rectTree;
	mWndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	mWndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	//mWndToolBar.CleanUpLockedImages();
	//mWndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 잠금 */);

	mFileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("비트맵을 로드할 수 없습니다. %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	mFileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	mFileViewImages.Add(&bmp, RGB(255, 0, 255));

	mWndFileView.SetImageList(&mFileViewImages, TVSIL_NORMAL);
}

BEGIN_MESSAGE_MAP(CFileViewTree, CViewTree)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CFileViewTree::OnTvnSelchanged)
END_MESSAGE_MAP()


void CFileViewTree::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (hRoot != pNMTreeView->itemNew.hItem)
	{
		CMainFrame* mainFrame = dynamic_cast<CMainFrame*>(theApp.m_pMainWnd);

		if (mainFrame != nullptr)
		{
			CSpriteToolView* mainView = dynamic_cast<CSpriteToolView*>(mainFrame->GetActiveView());

			if (mainView != nullptr)
			{
				CString strItem = GetItemText(pNMTreeView->itemNew.hItem);

				mainView->SetImageID(mImages[strItem].imageID);
			}
		}
	}

	*pResult = 0;
}