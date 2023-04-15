// Terrain.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "Terrain.h"
#include "afxdialogex.h"
#include "JsonManager.h"

// Terrain 대화 상자

IMPLEMENT_DYNAMIC(Terrain, CPropertyPage)

Terrain::Terrain()
	: PageManager(IDD_Terrain, &mTerrainTree, &mSelected, &mImageID, &mPath)
{
	mType = "Terrain";
}

Terrain::~Terrain()
{

}

void Terrain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TerrainTree, mTerrainTree);
	DDX_Control(pDX, IDC_TerrainSelected, mSelected);
	DDX_Control(pDX, IDC_TerrainImageID, mImageID);
	DDX_Control(pDX, IDC_TerrainPath, mPath);
}

BEGIN_MESSAGE_MAP(Terrain, CPropertyPage)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TerrainTree, &Terrain::OnTvnSelchangedTerraintree)
END_MESSAGE_MAP()

// Terrain 메시지 처리기

BOOL Terrain::OnInitDialog()
{
	PageManager::OnInitDialog();

	CreateD2D();

	// Json으로부터 이미지 로딩
	ImageJson imageJson;
	imageJson.DeserializeFromFile("Json\\ImageResourceTable.json");

	for (auto iter = imageJson.mImageList.begin(); iter != imageJson.mImageList.end(); iter++)
		AddImage(iter->imageID, iter->path);

	// Json으로부터 타일 로딩
	ItemJson tileJson;
	tileJson.DeserializeFromFile("Json\\TileResourceTable.json");

	HTREEITEM hRoot = nullptr;

	for (auto iter = tileJson.mItemList.begin(); iter != tileJson.mItemList.end(); iter++)
	{
		CString name;
		name = iter->name.c_str();

		if (iter->imageID == 0)
			hRoot = AddItem(name);
		else
			AddItem(name, hRoot, *iter);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void Terrain::OnDestroy()
{
	PageManager::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Terrain::OnTvnSelchangedTerraintree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	SelectedItem(pNMTreeView);
}