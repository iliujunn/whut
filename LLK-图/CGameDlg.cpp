// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)
CString CGameDlg::Effect[] = {
	L"D:\\LLKBGM\\ClickSound\\JI.mp3",
	L"D:\\LLKBGM\\ClickSound\\GANMA.mp3",
};

CString CGameDlg::Theme[][3] = {
	{L"theme\\picture\\fruit_element.bmp",L"theme\\picture\\fruit_mask.bmp",L"theme\\picture\\fruit_bg.bmp"},
	{L"theme\\picture\\ikun_element.bmp",L"theme\\picture\\ikun_mask.bmp",L"theme\\picture\\ikun_bg.bmp"},
};
CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = GAMETOP_X;
	m_ptGameTop.y = GAMETOP_Y;

	//初始化图片元素大小
	m_sizeElem.cx = ELEM_WIDTH;
	m_sizeElem.cy = ELEM_HEIGHT;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bFirstPoint = TRUE;

}
CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/,MyDataExchange  *dataExchange)
	: CDialogEx(IDD_GAME_DIALOG, pParent),m_dataExchange(dataExchange)
{
	//初始化起始点坐标
	m_ptGameTop.x = GAMETOP_X;
	m_ptGameTop.y = GAMETOP_Y;

	//初始化图片元素大小
	m_sizeElem.cx = ELEM_WIDTH;
	m_sizeElem.cy = ELEM_HEIGHT;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bFirstPoint = TRUE;

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_COUNTDOWN, m_staticCountdown);
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, start, StartBtn);
	DDX_Control(pDX, TIP_BUTTON, m_TipBtn);
	DDX_Control(pDX, RESET, m_ResetBtn);
	DDX_Control(pDX, GAME_SETTING, m_SettingBtn);
}

void CGameDlg::InitBackground() {
	HANDLE bmp = ::LoadImage(NULL, Theme[ThemeID][2], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//获得当前对话框的视频内容
	CClientDC dc(this);
	if (m_dcBG) m_dcBG.DeleteDC();
	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);

	//初始化内存DC
	if (m_dcMem) m_dcMem.DeleteDC();
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	
	ON_BN_CLICKED(start, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_COUNTDOWN, &CGameDlg::OnStnClickedStaticCountdown)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(GAME_SETTING, &CGameDlg::OnClickedGameSetting)
	ON_BN_CLICKED(RESET, &CGameDlg::OnClickedReset)
	ON_BN_CLICKED(TIP_BUTTON, &CGameDlg::OnClickedTipButton)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->InitBackground();
	this->UpdateWindow();
	this->InitElement();
	// TODO:  在此添加额外的初始化
	// 获取文本框控件
	//m_editText.SubclassDlgItem(IDC_STATIC_COUNTDOWN, this);

	// 创建并设置字体
	font.CreatePointFont(200, _T("Arial"));  // 设置字体为Arial，大小为12点（120缩放）
	GetDlgItem(IDC_STATIC_COUNTDOWN)->SetFont(&font);
	
	m_SettingBtn.EnableWindow(false);
	m_ResetBtn.EnableWindow(false);
	m_TipBtn.EnableWindow(false);



	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void CGameDlg::UpdateWindow() {

	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);  //获得窗口大小
	this->GetClientRect(rtClient);//获得客户区大小

	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDlg::InitElement() {
	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImage(NULL, Theme[ThemeID][0], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (m_dcElement) m_dcElement.DeleteDC();
	m_dcElement.CreateCompatibleDC(&dc);

	m_dcElement.SelectObject(hBmpBG);

	//掩码图加载
	HANDLE hMask = ::LoadImage(NULL, Theme[ThemeID][1], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频兼容的dc
	if (m_dcMask) m_dcMask.DeleteDC();
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图选入dc
	m_dcMask.SelectObject(hMask);

}




void CGameDlg::OnBnClickedBtnStart()
{

	StartBtn.EnableWindow(false);
	m_CountDownSeconds = TIMELIMIT;
	SetTimer(1, 1000, NULL);
	m_GameC.StartGame();
	m_SettingBtn.EnableWindow(true);
	m_ResetBtn.EnableWindow(true);
	m_TipBtn.EnableWindow(true);
	UpdateMap();
	EffectID = 0;
	m_Victory = 0; // 游戏进行中
	// TODO: 在此添加控件通知处理程序代码
}

void CGameDlg::UpdateMap() {
	
	int nRows = m_GameC.s_nRows;
	int nCols = m_GameC.s_nCols;	
	int nLeft = m_ptGameTop.x, nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx, nElemH = m_sizeElem.cy;
	m_rtGameRect.right = nLeft + nCols * nElemW, m_rtGameRect.bottom = nTop + nRows * nElemW;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			int nElemVal = m_GameC.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
	Invalidate(FALSE);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	
	int row = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	
	int col = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (row < 0 || row >= m_GameC.s_nRows || col < 0 || col >= m_GameC.s_nCols) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//DrawTipFrame(row, col);
	//点击音效
	

	bool bSuc = false;
	if (m_bFirstPoint) {
		DrawTipFrame(row, col);
		m_GameC.SetFirstPoint(row, col);
	}
	else {
		DrawTipFrame(row, col);
		m_GameC.SetSecondPoint(row, col);
		Vertex avPath[MAX_VERTEX_NUM];
		int nVexnum = 0;
		bSuc = m_GameC.Link(avPath,nVexnum);
		if (bSuc) {
			PlayEffect(EffectID);
			DrawTipLine(avPath,nVexnum);
			Sleep(450);
			this->UpdateMap();			
			StopEffect(EffectID);
		}
	}
	
	m_bFirstPoint = !m_bFirstPoint;
	//if (m_bFirstPoint == TRUE &&! bSuc ) this->UpdateMap();



}

void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233,43,43));
	CRect rtTipFrame;
	rtTipFrame.top = nRow * m_sizeElem.cy + m_ptGameTop.y;
	rtTipFrame.left = nCol * m_sizeElem.cx + m_ptGameTop.x;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	dc.FrameRect(rtTipFrame,&brush);

}

void CGameDlg::DrawTipLine(Vertex avPath[],int nVexnum) {
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].Col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].Row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 1; i < nVexnum ; i++)
	{
		int x = m_ptGameTop.x + avPath[i].Col * m_sizeElem.cx + m_sizeElem.cx / 2;
		int y = m_ptGameTop.y + avPath[i].Row * m_sizeElem.cy + m_sizeElem.cy / 2;
		dc.LineTo(x,y);
	}
	dc.SelectObject(pOldPen);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1 && m_Victory == 0 )
	{
		m_CountDownSeconds--;  // 更新倒计时时间

		// 更新窗口显示
		CString strCountdown;
		strCountdown.Format(_T("倒计时：%d"), m_CountDownSeconds);
		m_staticCountdown.SetWindowTextW(strCountdown);
		GetDlgItem(IDC_STATIC_COUNTDOWN)->SetWindowText(strCountdown);
		Invalidate(false);
		// 检查是否倒计时结束
		if (m_CountDownSeconds  == 0 || m_Victory != 0 )
		{
			// 做倒计时结束的处理
			KillTimer(1);  // 停止定时器
		}
		
		
		m_Victory = m_GameC.IsWin(m_CountDownSeconds);
		UINT i;
		if (m_Victory == 1) {
			int m_TimeCost = TIMELIMIT - m_CountDownSeconds;
			CString message(_T("Victory!\n鸡格！"));
	
			MessageBox(message);
			i = MessageBox(_T("再整一把？"), _T("提示"), MB_YESNO | MB_ICONQUESTION);
			InsertIntoDataBase(m_TimeCost);
			if (i == IDYES)
			{
				OnBnClickedBtnStart();
			}
			else {
				OnCancel();
			}
			return;
		}
		else if (m_Victory == -1) {
			CString message(_T("Defeat!\n修炼两年半才能成为真正的MAN！"));
			MessageBox(message);
			i = MessageBox(_T("再整一把？"), _T("提示"), MB_YESNO | MB_ICONQUESTION);
			 
			if (i == IDYES)
			{
				OnBnClickedBtnStart();
			}
			else {
				OnCancel();
			}
			return;
		}
		
	}

}


void CGameDlg::OnStnClickedStaticCountdown()
{
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC_COUNTDOWN))
	{
		//pDC->SetTextColor(RGB(255, 255, 255));//设置文本框字体颜色
		pDC->SetBkMode(TRANSPARENT);//设透明
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//这句话不能掉
	}


	return hbr;
}


void CGameDlg::OnClickedGameSetting()
{
	CGameSettingDlg setting;
	if (setting.DoModal() == IDOK) {
		EffectID = setting.effectID;
		ThemeID = setting.themeID;
		InitBackground();
		InitElement();
		
		UpdateMap();
	}
	// TODO: 在此添加控件通知处理程序代码
}

void CGameDlg::PlayEffect(int id) {
	EffectID = id;
	MCIERROR result;
	WCHAR errorMessage[256];

	CString openCmd = L"open " + Effect[id];
	result = mciSendString(openCmd, NULL, 0, NULL);
	if (result == 0)
	{
		result = mciSendString(L"play " + Effect[id], NULL, 0, NULL);
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

void CGameDlg::StopEffect(int  id) {

	mciSendString(L"stop " + Effect[id], NULL, 0, NULL);
	mciSendString(L"close " + Effect[id], NULL, 0, NULL);
}

//重排
void CGameDlg::OnClickedReset()
{
	m_GameC.Shuffle();
	UpdateMap();
	// TODO: 在此添加控件通知处理程序代码
}

//提示
void CGameDlg::OnClickedTipButton()
{
	Vertex avPath[MAX_VERTEX_NUM];
	int nVexnum = 0;
	bool bSuc = m_GameC.ForEach(avPath, nVexnum);
	

	if (bSuc) {
		Vertex First = avPath[0], Last = avPath[nVexnum - 1];
		DrawTipFrame(First.Row, First.Col);
		DrawTipFrame(Last.Row, Last.Col);
		PlayEffect(EffectID);
		DrawTipLine(avPath,nVexnum);
		Sleep(400);
		UpdateMap();
		StopEffect(EffectID);

	}
	else {
		MessageBox(L"没有可消去的了！");
	}
	// TODO: 在此添加控件通知处理程序代码
}

void CGameDlg::InsertIntoDataBase(int time) {
	try {
		m_dataExchange->insertIntoDB(time);
	}
	catch (sql::SQLException& e) {
		CString errorMessage(e.what());
		AfxMessageBox(errorMessage);
	}
}