#pragma once
#include "cwebbrowser2.h"


// WebDlg ��ȭ �����Դϴ�.

class WebDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WebDlg)

public:
	WebDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~WebDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2 m_WebCtl;
	virtual BOOL OnInitDialog();
};
