
// QQbombDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQbomb.h"
#include "QQbombDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CQQbombDlg 对话框



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


// CQQbombDlg 消息处理程序

BOOL CQQbombDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQbombDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQbombDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQbombDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	static bool bSend = true;
	UpdateData(TRUE);
	m_hFindWnd = ::FindWindow(L"TXGuiFoundation", m_Name);
	if (bSend == true)
	{
	
		if (m_hFindWnd != 0)
		{
			SetTimer(0,100,0);
			m_index = 0;
			SetDlgItemText(IDC_BUTTON1, L"停止");
		}
		else
		{
			MessageBox(L"未找到相应窗口！请重试");
		}
		bSend = false;
	}
	else
	{
		SetDlgItemText(IDC_BUTTON1, L"发送");
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	//wchar_t*pContent(L"帅哥你好");
	int len = m_Content.GetLength();
	

		SetClipboardWord(m_Content[(m_index++)%len]);//将文字放到粘贴板上
		::SendMessage(m_hFindWnd, WM_PASTE, 0, 0);//向FindWindow发送粘贴消息
		::SendMessage(m_hFindWnd, WM_KEYDOWN, VK_RETURN, 0);
	
	CDialogEx::OnTimer(nIDEvent);
}
