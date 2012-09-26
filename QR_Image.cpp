// QR_Image.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#include "stdafx.h"
#include "QR_Image.h"

#include "QR_Encode.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp

BEGIN_MESSAGE_MAP(CQR_ImageApp, CWinApp)
	//{{AFX_MSG_MAP(CQR_ImageApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp �N���X�̍\�z

CQR_ImageApp::CQR_ImageApp()
{
}


/////////////////////////////////////////////////////////////////////////////
// �B��� CQR_ImageApp �I�u�W�F�N�g

CQR_ImageApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CQR_ImageApp �N���X�̏�����

BOOL CQR_ImageApp::InitInstance()
{
	// OLE ������
	if (! AfxOleInit())
	   return FALSE;

// ���������[�N���o�p�`�F�b�N�|�C���g�ݒ�i�f�o�b�O���̂݁j
// ��ToolTip �֘A�̃��[�N�͖��Ȃ�
#ifdef _DEBUG
	mStart.Checkpoint();
#endif //_DEBUG

#if _MFC_VER <= 0x0600
	#ifdef _AFXDLL
		Enable3dControls();
	#else
		Enable3dControlsStatic();
	#endif
#endif

	// ���C���E�C���h�E�쐬
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// �t���[�������\�[�X���烍�[�h
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW, NULL, NULL);

	// �A�v���P�[�V�����A�C�R���Z�b�g
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pFrame->SetIcon(hIcon, TRUE);

	// ���C���E�B���h�E�\���A�X�V
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CQR_ImageApp::ExitInstance() 
{
// �������[���[�N���\���i�f�o�b�O���̂݁j
#ifdef _DEBUG
	mEnd.Checkpoint();

	if (mDiff.Difference(mStart, mEnd))
	{
		TRACE("\n-------- Detected memory leaks. DUMP(DumpStatistics) Start --------\n");
		mDiff.DumpStatistics();
		TRACE("-------- Detected memory leaks. DUMP(DumpStatistics) End --------\n");

		TRACE("\n-------- Detected memory leaks. DUMP(DumpAllObjectsSince) Start --------\n");
		mDiff.DumpAllObjectsSince();
		TRACE("-------- Detected memory leaks. DUMP(DumpAllObjectsSince) End --------\n\n");

//		AfxMessageBox("Detected memory leaks.", MB_OK | MB_ICONEXCLAMATION);
	}
	else
	{
		TRACE("\n-------- No detected memory leaks. OK !! --------\n\n");
	}
#endif //_DEBUG

	return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	HCURSOR m_hCurArrow, m_hCurWait, m_hCurHand;
	HFONT   m_hFont;  // URL/MailTo �\��������t�H���g

	// �ĕ`��}���̂��߂̃t���O
	BOOL m_bPointOnUrl;
	BOOL m_bPointOnMailTo;

	// �}�E�X�{�^�����㎞�ɃR�}���h���s���邽�߂̃t���O
	BOOL m_bBtnDownUrl;
	BOOL m_bBtnDownMailTo;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V�����R�}���h
void CQR_ImageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_hCurArrow = LoadCursor(NULL, IDC_ARROW);
	m_hCurWait  = LoadCursor(NULL, IDC_WAIT);
	m_hCurHand  = AfxGetApp()->LoadCursor(IDC_RHAND);

	m_bPointOnUrl = m_bPointOnMailTo = FALSE;
	m_bBtnDownUrl = m_bBtnDownMailTo = FALSE;

	// �t�H���g�쐬�i�A���_�[���C���t���j
	LOGFONT lf;
	lf.lfHeight			= 12;
	lf.lfWidth			= 0;
	lf.lfEscapement		= 0;
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_DONTCARE;
	lf.lfItalic			= FALSE;
	lf.lfUnderline		= TRUE;
	lf.lfStrikeOut		= FALSE;
	lf.lfCharSet		= SHIFTJIS_CHARSET;
	lf.lfOutPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= PROOF_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lstrcpy(lf.lfFaceName, "�l�r �o�S�V�b�N");

	m_hFont = CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATICURL)->SendMessage(WM_SETFONT, (WPARAM)m_hFont, TRUE);
	GetDlgItem(IDC_STATICMAILTO)->SendMessage(WM_SETFONT, (WPARAM)m_hFont, TRUE);

	return TRUE;
}

void CAboutDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	// �g�p�I�u�W�F�N�g�j��
	DeleteObject(m_hFont);
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int nID = pWnd->GetDlgCtrlID();

	if (nID == IDC_STATICURL)
		pDC->SetTextColor(m_bPointOnUrl ? RGB(255, 128, 0) : RGB(0, 0, 128));

	if (nID == IDC_STATICMAILTO)
		pDC->SetTextColor(m_bPointOnMailTo ? RGB(255, 128, 0) : RGB(0, 0, 128));

	return hbr;
}

void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// �}�E�X���W�ʒu�`�F�b�N
	ClientToScreen(&point);

	CRect rectUrl;
	GetDlgItem(IDC_STATICURL)->GetWindowRect(rectUrl);

	CRect rectMailTo;
	GetDlgItem(IDC_STATICMAILTO)->GetWindowRect(rectMailTo);

	// �J�[�\���ύX
	SetCursor(rectUrl.PtInRect(point) || rectMailTo.PtInRect(point) ? m_hCurHand : m_hCurArrow);

	if (m_bPointOnUrl != rectUrl.PtInRect(point))
	{
		// URL �\���e�L�X�g�F�ύX
		GetDlgItem(IDC_STATICURL)->InvalidateRect(NULL);
		m_bPointOnUrl = rectUrl.PtInRect(point);

		if (m_bPointOnUrl)
			SetCapture();
		else
			ReleaseCapture();
	}

	if (m_bPointOnMailTo != rectMailTo.PtInRect(point))
	{
		// mailto �\���e�L�X�g�F�ύX
		GetDlgItem(IDC_STATICMAILTO)->InvalidateRect(NULL);
		m_bPointOnMailTo = rectMailTo.PtInRect(point);

		if (m_bPointOnMailTo)
			SetCapture();
		else
			ReleaseCapture();
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// �}�E�X���W�ʒu�`�F�b�N
	ClientToScreen(&point);

	CRect rectUrl;
	GetDlgItem(IDC_STATICURL)->GetWindowRect(rectUrl);

	CRect rectMailTo;
	GetDlgItem(IDC_STATICMAILTO)->GetWindowRect(rectMailTo);

	// �J�[�\���ύX
	SetCursor(rectUrl.PtInRect(point) || rectMailTo.PtInRect(point) ? m_hCurHand : m_hCurArrow);

	m_bBtnDownUrl    = rectUrl.PtInRect(point);
	m_bBtnDownMailTo = rectMailTo.PtInRect(point);

	CDialog::OnLButtonDown(nFlags, point);
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bBtnDownUrl)
	{
		// �}�E�X���W�ʒu�`�F�b�N
		ClientToScreen(&point);

		CRect rectUrl;
		GetDlgItem(IDC_STATICURL)->GetWindowRect(rectUrl);

		if (rectUrl.PtInRect(point))
		{
			SetCursor(m_hCurWait);

			// �u���E�U�N��
			ShellExecute(m_hWnd, "open", "http://www.psytec.co.jp/", NULL, "", SW_SHOW);

			// �{�_�C�A���O���B�����ꍇ���l�����e�L�X�g���ĕ`��
			m_bPointOnUrl = FALSE;
			GetDlgItem(IDC_STATICURL)->InvalidateRect(NULL);

			SetCursor(m_hCurArrow);
		}

		m_bBtnDownUrl = FALSE;
	}
	else if (m_bBtnDownMailTo)
	{
		// �}�E�X���W�ʒu�`�F�b�N
		ClientToScreen(&point);

		CRect rectMailTo;
		GetDlgItem(IDC_STATICMAILTO)->GetWindowRect(rectMailTo);

		if (rectMailTo.PtInRect(point))
		{
			SetCursor(m_hCurWait);

			// ���[���N��
			ShellExecute(m_hWnd, "open", "mailto:info@psytec.co.jp", NULL, "", SW_SHOW);

			// �{�_�C�A���O���B�����ꍇ���l�����e�L�X�g���ĕ`��
			m_bPointOnMailTo = FALSE;
			GetDlgItem(IDC_STATICMAILTO)->InvalidateRect(NULL);

			SetCursor(m_hCurArrow);
		}

		m_bBtnDownMailTo = FALSE;
	}

	CDialog::OnLButtonUp(nFlags, point);
}
