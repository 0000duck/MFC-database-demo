
// MFC database demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC database demo.h"
#include "MFC database demoDlg.h"
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


// CMFCdatabasedemoDlg 对话框




CMFCdatabasedemoDlg::CMFCdatabasedemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCdatabasedemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCdatabasedemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMFCdatabasedemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCdatabasedemoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCdatabasedemoDlg 消息处理程序

BOOL CMFCdatabasedemoDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | 
		LVS_EX_HEADERDRAGDROP | LVS_EX_TWOCLICKACTIVATE);

	//设置m_list的列
	CRect rect; 
	m_list.GetClientRect(rect); 
	int listWidth = rect.Width(); 
	m_list.InsertColumn(0,_T("姓名"),LVCFMT_LEFT,listWidth  /  2); 
	m_list.InsertColumn(1,_T("性别"),LVCFMT_LEFT,listWidth  /  2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCdatabasedemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCdatabasedemoDlg::OnPaint()
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
HCURSOR CMFCdatabasedemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCdatabasedemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if(!m_db.IsOpen() && !m_db.OpenEx(_T( "DSN=odbc_test;UID=admin;PWD=admin"),   
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))  
	{ 
		MessageBox(_T("连接错误"));  
		return ;  
	}
	m_set.m_pDatabase = &m_db;
	m_set.Open(CRecordset::forwardOnly,_T("SELECT * from family"),
		CRecordset::readOnly); 
	CDBVariant var; 
	m_list.DeleteAllItems(); 
	short  nFields = m_set.GetODBCFieldCount();
	int row = 0;
	//access表有效数据的offset
	int column_offset = 1;
	while(!m_set.IsEOF())  
	{ 
		for(int column = column_offset; column < nFields; column++)  
		{ 
			m_set.GetFieldValue(column, var );  
			// 添加一行记录 
			if (column == column_offset) 
				m_list.InsertItem(row, VariantToCString(&var));  
			// 插入这行记录中一列的值 
			else  
				//注意m_list显示的时候并不需要offset
				m_list.SetItemText(row, column - column_offset, VariantToCString(&var)); 
		} 
		m_set.MoveNext();  
		row++;  
	} 
	m_set.Close();  
	m_db.Close();   

	//CDialogEx::OnOK();
}
CString CMFCdatabasedemoDlg::VariantToCString(CDBVariant* var)
{
	CString str;  // 转换以后的字符串 
	if(!var)  
	{ 
		str = _T("NULL Var Parameter");  
		return str;  
	} 
	switch(var->m_dwType) 
	{ 
	case DBVT_SHORT:  
		str.Format(_T("%d"),(int)var->m_iVal); 
		break; 
	case DBVT_LONG: 
		str.Format(_T("%d"),var->m_lVal); 
		break; 
	case DBVT_SINGLE: 
		str.Format(_T("%10.6f"),(double)var->m_fltVal);  
		break; 
	case DBVT_DOUBLE:  
		str.Format(_T("%10.6f"),var->m_dblVal); 
		break; 
	case DBVT_BOOL: 
		str = (var->m_boolVal==0) ? _T("FALSE") : _T("TRUE"); 
		break; 
	case DBVT_STRING: 
		str = var->m_pstring->GetBuffer();  
		break; 
	case DBVT_ASTRING:  
		str = var->m_pstringA->GetBuffer();   
		break;   
	case DBVT_WSTRING:   
		str = var->m_pstringW->GetBuffer();   
		break; 
	case DBVT_DATE: 
		str.Format(_T("%d-%d-%d"),(var->m_pdate)->year,(var->m_pdate)->month,(var->
			m_pdate)->day);  
		break; 
	default: 
		str.Format(_T("Unk type %d\n"),var->m_dwType);  
		TRACE(_T("Unknown type %d\n"),var->m_dwType);  
	} 
	return str;
}