#pragma once

class ControlProperty;

// Control 폼 보기

/// <summary>
/// 타일 및 오브젝트 선택하는 View 영역
/// 
/// 2022. 02. 07
/// </summary>
class Control : public CFormView
{
	DECLARE_DYNCREATE(Control)

#pragma region MyVariable
public:
	// Form 시트
	ControlProperty* mControlSheet;
#pragma endregion

protected:
	Control();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Control();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Control };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

#pragma region MyFunction

#pragma endregion

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
};