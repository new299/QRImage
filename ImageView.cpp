// ImageView.cpp : CImageView �N���X �C���v�������e�[�V�����t�@�C��
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"
#include "MainFrm.h"
#include "ImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNCREATE(CImageView, CView)

CImageView::CImageView()
{
}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CView)
	//{{AFX_MSG_MAP(CImageView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView �`��

void CImageView::OnDraw(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);

	if (pMainFrame->m_bDataEncoded)
	{
		int nSrcSize = pMainFrame->m_nSymbleSize;
		int nDstSize = min(rcClient.Width(), rcClient.Height());

		// �������̂��߈�U���������ŃX�g���b�`���Ă����ʂɕ\��
		CDC* pWorkDC = new CDC;
		pWorkDC->CreateCompatibleDC(NULL);

		CBitmap* pWorkBitmap = new CBitmap;
		pWorkBitmap->CreateBitmap(nDstSize, nDstSize, 1, 1, NULL);

		CBitmap* pOldBitmap = pWorkDC->SelectObject(pWorkBitmap);
		pWorkDC->StretchBlt(0, 0, nDstSize, nDstSize, pMainFrame->m_pSymbleDC, 0, 0, nSrcSize, nSrcSize, SRCCOPY);

		pDC->BitBlt(0, 0, nDstSize, nDstSize, pWorkDC, 0, 0, SRCCOPY);

		pWorkDC->SelectObject(pOldBitmap);
		delete pWorkBitmap;
		delete pWorkDC;
	}
	else
	{
		pDC->FillSolidRect(&rcClient, RGB(255, 255, 255));
	}

}

BOOL CImageView::OnEraseBkgnd(CDC* pDC) 
{
	CRect rcClient;
	GetClientRect(&rcClient);

	// �V���{���\���G���A�ȊO�𔒂œh��ׂ�
	if (rcClient.Width() != rcClient.Height())
	{
		if (rcClient.Width() > rcClient.Height())
			rcClient.left += rcClient.Height();
		else
			rcClient.top += rcClient.Width();

		pDC->FillSolidRect(&rcClient, RGB(255, 255, 255));
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CImageView �f�f

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CImageView ���b�Z�[�W �n���h��

/////////////////////////////////////////////////////////////////////////////
// �}�E�X�E�{�^���N���b�N�ɂ��|�b�v�A�b�v���j���[�\��

void CImageView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu Menu;

	// ���j���[�i���\�[�X�j�����[�h
	Menu.LoadMenu(IDR_IMAGEMENU);

	// �T�u�i�|�b�v�A�b�v �j���j���[�擾
	CMenu* pPopupMenu = Menu.GetSubMenu(0);

	// ���j���[���ڂ̗L���^������
	pPopupMenu->EnableMenuItem(ID_EDIT_COPY, ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bDataEncoded ? MF_ENABLED : MF_GRAYED);

	// �|�b�v�A�b�v���j���[��\��
	pPopupMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTBUTTON, point.x, point.y, this);
}


/////////////////////////////////////////////////////////////////////////////
// ���j���[���ڍX�V

void CImageView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CImageView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CImageView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bDataEncoded);
}

void CImageView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// ���j���[���s

void CImageView::OnEditCopy() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->CopyImage();
}


/////////////////////////////////////////////////////////////////////////////
// OLE �h���b�O���h���b�v����

void CImageView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bDataEncoded)
	{
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->CopyImage(&m_OleDataSource);
	}

	CView::OnLButtonDown(nFlags, point);
}
