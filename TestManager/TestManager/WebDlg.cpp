// WebDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TestManager.h"
#include "WebDlg.h"
#include "afxdialogex.h"


// WebDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(WebDlg, CDialogEx)

WebDlg::WebDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WebDlg::IDD, pParent)
{

}

WebDlg::~WebDlg()
{
}

void WebDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebCtl);
}


BEGIN_MESSAGE_MAP(WebDlg, CDialogEx)
END_MESSAGE_MAP()


// WebDlg �޽��� ó�����Դϴ�.


BOOL WebDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CComVariant var(_T("http://ctl2.jbnu.ac.kr/"));
	m_WebCtl.Navigate2(&var,NULL,NULL,NULL,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
