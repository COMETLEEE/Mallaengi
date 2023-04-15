// Object.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "Object.h"
#include "afxdialogex.h"

// Object 대화 상자

IMPLEMENT_DYNAMIC(Object, CPropertyPage)

Object::Object()
	: PageManager(IDD_Object, &mObjectTree, &mSelected, &mImageID, &mPath)
{
	mType = "Object";
}

Object::~Object()
{

}

void Object::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ObjectTree, mObjectTree);
	DDX_Control(pDX, IDC_ObjectSelected, mSelected);
	DDX_Control(pDX, IDC_ImageID, mImageID);
	DDX_Control(pDX, IDC_ObjectPath, mPath);
}

BEGIN_MESSAGE_MAP(Object, CPropertyPage)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_ObjectTree, &Object::OnTvnSelchangedObjecttree)
END_MESSAGE_MAP()

// Object 메시지 처리기

void Object::OnDestroy()
{
	PageManager::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Object::OnTvnSelchangedObjecttree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	SelectedItem(pNMTreeView);
}

BOOL Object::OnInitDialog()
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
	tileJson.DeserializeFromFile("Json\\ObjectResourceTable.json");

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
