// ImageView.h : CImageView �N���X�錾����уC���^�[�t�F�C�X��`
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_IMAGEVIEW_H__F393D9E2_40E7_4288_A236_61AB8812E193__INCLUDED_)
#define AFX_IMAGEVIEW_H__F393D9E2_40E7_4288_A236_61AB8812E193__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImageView �N���X

class CImageView : public CView
{
protected:
	CImageView();
	DECLARE_DYNCREATE(CImageView)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	COleDataSource m_OleDataSource;

// �I�[�o�[���C�h
	//{{AFX_VIRTUAL(CImageView)
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CImageView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CImageView)
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_IMAGEVIEW_H__F393D9E2_40E7_4288_A236_61AB8812E193__INCLUDED_)
