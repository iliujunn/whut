
#include "pch.h"
#include "framework.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "CGameDlg.h"
#include "CSettingDlg.h"

#include <Vfw.H>
#include "Windows.h"
#include "mmsystem.h"
#pragma comment(lib, "WINMM.LIB")

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString CLLKDlg::BGM[] = {
		_T("D:\\LLKBGM\\JNTM.mp3"),
		_T("D:\\LLKBGM\\KAITUAN.mp3")
};

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg 对话框



CLLKDlg::CLLKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLLKDlg::~CLLKDlg() {
	if (m_dataExchange) {
		delete m_dataExchange;
	}
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnBnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CLLKDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_RANK, &CLLKDlg::OnClickedBtnRank)
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序
void CLLKDlg::InitBackground() {
	CBitmap bmpMain;//位图对象
	bmpMain.LoadBitmapW(IDB_MAIN_BG);

	//获得当前对话框的视频内存
	CClientDC dc(this);

	//创建与视频内存兼容的内存DC
	m_dcMem.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMem.SelectObject(bmpMain);

	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);  //获得窗口大小
	this->GetClientRect(rtClient);//获得客户区大小

	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800+nSpanWidth, 600+nSpanHeight);
	CenterWindow();
}

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	/*AllocConsole();//打开测试的输出窗口，
	freopen("CONOUT$", "w", stdout);*/
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	this->InitBackground();
	int id = 0;
	PlayMusic(id);
	SetVolumn(50,id);
	m_dataExchange = new MyDataExchange();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLLKDlg::OnPaint()
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
		CPaintDC dc(this);
		dc.BitBlt(0, 0, 800, 600,&m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CLLKDlg::OnBnClickedBtnBasic()
{
	this->ShowWindow(SW_HIDE);

	CGameDlg dlg(this, m_dataExchange);
	this->ShowWindow(SW_SHOW);
	dlg.DoModal();


}


void CLLKDlg::OnBnClickedBtnSetting()
{
	CSettingDlg m_Setting;
	m_Setting.volumn = CurrentBGMVolumn;
	if (m_Setting.DoModal() == IDOK) {
		if (m_Setting.BGMID != CurrentBGMID) {
			StopMusic(CurrentBGMID);
			PlayMusic(m_Setting.BGMID);
		}
		SetVolumn(m_Setting.volumn,CurrentBGMID);
	}
		


}

void CLLKDlg::PlayMusic(int id)
{
	MCIERROR result;
	WCHAR errorMessage[256];

	CurrentBGMID = id;

	CString BGMcmd = L"open " + BGM[id];
	result = mciSendString(BGMcmd, NULL, 0, NULL);
	if (result == 0)
	{
		result = mciSendString(L"play "+BGM[id] + L" repeat", NULL, 0, NULL);
		if (result != 0)
		{
			
			mciGetErrorString(result, errorMessage, sizeof(errorMessage));
			MessageBox(errorMessage);
		}


	}
	else {
		mciGetErrorString(result, errorMessage, sizeof(errorMessage));
		MessageBox(errorMessage);
	}

}

void CLLKDlg::StopMusic(int  id) {

	mciSendString(L"stop "+BGM[id], NULL, 0, NULL);
	mciSendString(L"close " + BGM[id], NULL, 0, NULL);
}

void CLLKDlg::SetVolumn(int Volumn , int id) {
	CurrentBGMVolumn = Volumn;
	CString VolumnCmd;
	VolumnCmd.Format(L"setaudio "+BGM[id]+L" volume to % d",Volumn);
	//MessageBox(VolumnCmd);
	mciSendString(VolumnCmd, NULL, 0, NULL);
}

void CLLKDlg::OnClickedBtnRank()
{
	//传入连接 ，否则程序会崩溃


		CRankDialog rankdlg(this, m_dataExchange);
		rankdlg.DoModal();

	// TODO: 在此添加控件通知处理程序代码
}


