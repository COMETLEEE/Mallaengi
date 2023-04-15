#pragma once
#include "ViewTree.h"
#include <map>

using std::map;

// ImageIDGetterDlg 대화 상자

class ImageIDGetterDlg : public CDialog
{
	DECLARE_DYNAMIC(ImageIDGetterDlg)

public:
	ImageIDGetterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ImageIDGetterDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ImageID_Getter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit mGetImageID;
	UINT mImageID;

	afx_msg void OnBnClickedOk();
};

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

/// <summary>
/// 이미지 정보를 다루기 위한 구조체
/// 
/// 2022. 02. 15 JK
/// </summary>
struct ImageInfo
{
	UINT imageID;
	CString name;
	CString path;
};

class CFileViewTree : public CViewTree
{
public:
	map<CString, ImageInfo> mImages;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};

class CFileView : public CDockablePane
{
	// 생성입니다.
public:
	CFileView() noexcept;

	void AdjustLayout();
	void OnChangeVisualStyle();

	// 특성입니다.
public:

protected:
	CFileViewTree mWndFileView;
	CImageList mFileViewImages;
	CFileViewToolBar mWndToolBar;

	CFileDialog mLoadDlg;
	ImageIDGetterDlg mImgIDGetterDlg;

protected:
	void FillFileView();

	// 구현입니다.
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};