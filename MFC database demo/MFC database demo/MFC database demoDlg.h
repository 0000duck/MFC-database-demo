
// MFC database demoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CMFCdatabasedemoDlg �Ի���
class CMFCdatabasedemoDlg : public CDialogEx
{
// ����
public:
	CMFCdatabasedemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCDATABASEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString VariantToCString(CDBVariant* var);
private:
	CListCtrl m_list;
	::CDatabase m_db;
	::CRecordset m_set;
};
