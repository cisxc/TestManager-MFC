// WebDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestManager.h"
#include "WebDlg.h"
#include "afxdialogex.h"


// WebDlg 대화 상자입니다.

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


// WebDlg 메시지 처리기입니다.


BOOL WebDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CComVariant var(_T("http://ctl2.jbnu.ac.kr/"));
	m_WebCtl.Navigate2(&var,NULL,NULL,NULL,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
