
// QQbombDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQbomb.h"
#include "QQbombDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQQbombDlg �Ի���



CQQbombDlg::CQQbombDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQbombDlg::IDD, pParent)
	, m_Content(_T(""))
	, m_Name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQbombDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Content);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
}

BEGIN_MESSAGE_MAP(CQQbombDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CQQbombDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CQQbombDlg ��Ϣ�������

BOOL CQQbombDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQQbombDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQQbombDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQQbombDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQbombDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	static bool bSend = true;
	UpdateData(TRUE);
	m_hFindWnd = ::FindWindow(L"TXGuiFoundation", m_Name);
	if (bSend == true)
	{
	
		if (m_hFindWnd != 0)
		{
			SetTimer(0,100,0);
			m_index = 0;
			SetDlgItemText(IDC_BUTTON1, L"ֹͣ");
		}
		else
		{
			MessageBox(L"δ�ҵ���Ӧ���ڣ�������");
		}
		bSend = false;
	}
	else
	{
		SetDlgItemText(IDC_BUTTON1, L"����");
		KillTimer(0);
		bSend = true;
	}
}

void CQQbombDlg::SetClipboardWord(wchar_t word)
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		HLOCAL hGlobal = LocalAlloc(LMEM_MOVEABLE|LMEM_ZEROINIT, 4);
		wchar_t*pGlobal = (wchar_t*)LocalLock(hGlobal);
		wsprintf(pGlobal, L"%c", word);
		LocalUnlock(hGlobal);
		SetClipboardData(CF_UNICODETEXT, hGlobal);
		CloseClipboard();
		LocalFree(hGlobal);
	}
}

void CQQbombDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	//wchar_t*pContent(L"˧�����");
	int len = m_Content.GetLength();
	

		SetClipboardWord(m_Content[(m_index++)%len]);//�����ַŵ�ճ������
		::SendMessage(m_hFindWnd, WM_PASTE, 0, 0);//��FindWindow����ճ����Ϣ
		::SendMessage(m_hFindWnd, WM_KEYDOWN, VK_RETURN, 0);
	
	CDialogEx::OnTimer(nIDEvent);
}
