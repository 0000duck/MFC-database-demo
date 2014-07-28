
// MFC database demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC database demo.h"
#include "MFC database demoDlg.h"
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


// CMFCdatabasedemoDlg �Ի���




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


// CMFCdatabasedemoDlg ��Ϣ�������

BOOL CMFCdatabasedemoDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | 
		LVS_EX_HEADERDRAGDROP | LVS_EX_TWOCLICKACTIVATE);

	//����m_list����
	CRect rect; 
	m_list.GetClientRect(rect); 
	int listWidth = rect.Width(); 
	m_list.InsertColumn(0,_T("����"),LVCFMT_LEFT,listWidth  /  2); 
	m_list.InsertColumn(1,_T("�Ա�"),LVCFMT_LEFT,listWidth  /  2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCdatabasedemoDlg::OnPaint()
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
HCURSOR CMFCdatabasedemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCdatabasedemoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(!m_db.IsOpen() && !m_db.OpenEx(_T( "DSN=odbc_test;UID=admin;PWD=admin"),   
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))  
	{ 
		MessageBox(_T("���Ӵ���"));  
		return ;  
	}
	m_set.m_pDatabase = &m_db;
	m_set.Open(CRecordset::forwardOnly,_T("SELECT * from family"),
		CRecordset::readOnly); 
	CDBVariant var; 
	m_list.DeleteAllItems(); 
	short  nFields = m_set.GetODBCFieldCount();
	int row = 0;
	//access����Ч���ݵ�offset
	int column_offset = 1;
	while(!m_set.IsEOF())  
	{ 
		for(int column = column_offset; column < nFields; column++)  
		{ 
			m_set.GetFieldValue(column, var );  
			// ���һ�м�¼ 
			if (column == column_offset) 
				m_list.InsertItem(row, VariantToCString(&var));  
			// �������м�¼��һ�е�ֵ 
			else  
				//ע��m_list��ʾ��ʱ�򲢲���Ҫoffset
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
	CString str;  // ת���Ժ���ַ��� 
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