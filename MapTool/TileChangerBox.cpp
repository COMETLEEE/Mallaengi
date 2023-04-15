// TileChangerBox.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "TileChangerBox.h"
#include "afxdialogex.h"


// TileChangerBox 대화 상자

IMPLEMENT_DYNAMIC(TileChangerBox, CDialogEx)

TileChangerBox::TileChangerBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TileChange, pParent)
{

}

TileChangerBox::~TileChangerBox()
{

}

void TileChangerBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mXInput);
	DDX_Control(pDX, IDC_EDIT2, mYInput);
}


BEGIN_MESSAGE_MAP(TileChangerBox, CDialogEx)
END_MESSAGE_MAP()


// TileChangerBox 메시지 처리기


void TileChangerBox::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	mXInput.GetWindowText(mX);
	mYInput.GetWindowText(mY);

	CDialogEx::OnOK();
}