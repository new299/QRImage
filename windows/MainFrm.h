// MainFrm.h : CMainFrame �N���X�錾����уC���^�[�t�F�C�X��`
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_MAINFRM_H__F7C4DD34_15EF_41C5_8907_C79B3F8FF648__INCLUDED_)
#define AFX_MAINFRM_H__F7C4DD34_15EF_41C5_8907_C79B3F8FF648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QR_Encode.h"
#include "ImageView.h"
#include "RightView.h"
#include "BottomView.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// �A�g���r���[�g
public:
	// �p�q�R�[�h�\���p
	int m_bDataEncoded;
	int m_nSymbleSize;

	CDC* m_pSymbleDC;
	CBitmap* m_pSymbleBitmap;
	CBitmap* m_pOldBitmap;

	// �����E�B���h�E�֘A
	BOOL m_bInitSplit;

	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;

	CSize m_sizeBottomView;
	CSize m_sizeRightView;

	CBottomView* m_pwndBottomView;
	CRightView*  m_pwndRightView;

	// �t�@�C���ۑ��p�X
	CString m_strSavePath;

// �I�y���[�V����
public:
	void ShowImage();
	void ShowBitmapSize();
	void CopyImage(COleDataSource* pOleDataSource = NULL);
	void SaveAsImage();
	void SaveImage();

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �R���g���[���o�[�p�����o
	CStatusBar m_wndStatusBar;
	CToolBar   m_wndToolBar;

// �������ꂽ���b�Z�[�W�}�b�v�֐�
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MAINFRM_H__F7C4DD34_15EF_41C5_8907_C79B3F8FF648__INCLUDED_)
