// CRankDialog.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CRankDialog.h"


// CRankDialog 对话框

IMPLEMENT_DYNAMIC(CRankDialog, CDialogEx)

CRankDialog::CRankDialog(CWnd* pParent /*=nullptr*/ ,MyDataExchange* dataExchange)
	: CDialogEx(RANK_DIALOG, pParent)
{
	m_dataExchange =dataExchange;
}
CRankDialog::CRankDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(RANK_DIALOG, pParent)
{

}
CRankDialog::~CRankDialog()
{
}

void CRankDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, RANK_LIST, m_rankList);
}


BEGIN_MESSAGE_MAP(CRankDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRankDialog 消息处理程序

void CRankDialog::InitBackground() {
	//CPaintDC   dc(this);
	
}
BOOL CRankDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitBackground();

	// 设置 List Control 的背景色为透明
	m_brushBackground.CreateStockObject(HOLLOW_BRUSH);
	m_rankList.SetBkColor(TRANSPARENT);
	m_rankList.SetExtendedStyle(LVS_EX_TRANSPARENTBKGND);

	CRect rect;
	m_rankList.GetClientRect(rect);
	m_rankList.SetExtendedStyle(m_rankList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	


	m_rankList.InsertColumn(0, L"排名", LVCFMT_CENTER, rect.Width() / 2, 0);
	m_rankList.InsertColumn(1, L"用时", LVCFMT_CENTER, rect.Width() / 2, 1);

	int rank = 0, timeCost;
	std::vector<int>data  ; 
	try {
		m_dataExchange->getData(data);
	}
	catch (sql::SQLException &e) {
		CString errorMessage(e.what());
		AfxMessageBox(errorMessage);
	}
	CString col1, col2;
	m_rankList.SubclassDlgItem(RANK_LIST, &m_rankList);
	for (; rank < (int)data.size(); ++ rank) {
		timeCost = data[rank];
		col1.Format(L"%d", rank+1);
		col2.Format(L"%d", timeCost);
		//MessageBox(col2);
		m_rankList.InsertItem(rank, NULL); //插入行
		m_rankList.SetItemText(rank,0, col1);
		m_rankList.SetItemText(rank, 1, col2);  // 表的数据是从第0行开始， 表头不包括在内
	}
	m_rankList.ModifyStyle(0, LVS_REPORT);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}




void CRankDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(RANK_BG);  //对话框的背景图片  

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpOld = m_dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


HBRUSH CRankDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//pWnd = &m_rankList;
	/*static int x = 0; 
	if(x == 0 ) pWnd = &m_rankList;*/
	/*CString i;
	i.Format(L"%d", x);
	MessageBox(i);*/
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	

	//MessageBox(i);
	
	
	// TODO:  在此更改 DC 的任何特性
	if (pWnd == &m_rankList) //控件可以为static，checkbox，button，edit等

	{
		pDC->SetBkMode(TRANSPARENT);

		pDC->SetTextColor(RGB(0, 0, 0)); //字体颜色，黑色
		return (HBRUSH)GetStockObject(NULL_BRUSH);

	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


