#pragma once
#include "cwebbrowser2.h"


// WebDlg 대화 상자입니다.

class WebDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WebDlg)

public:
	WebDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~WebDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2 m_WebCtl;
	virtual BOOL OnInitDialog();
};
