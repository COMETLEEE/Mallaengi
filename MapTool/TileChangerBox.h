#pragma once


// TileChangerBox 대화 상자

/// <summary>
/// Doc에서 타일 변경을 시도할 때 출력하는 대화상자
/// 
/// 2022. 03. 01 JK
/// </summary>
class TileChangerBox : public CDialogEx
{
	DECLARE_DYNAMIC(TileChangerBox)

public:
	// 대화 상자의 Static Text 컨트롤 리소스와 연동되는 변수
	CEdit mXInput;
	CEdit mYInput;

	// 위 대화상자의 변수로부터 값을 받아서 저장해두는 변수
	CString mX;
	CString mY;

public:
	TileChangerBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TileChangerBox();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TileChange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
};