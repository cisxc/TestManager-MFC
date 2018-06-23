
// TestManagerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "atltime.h"


// CTestManagerDlg ��ȭ ����
class CTestManagerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTestManagerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	 static UINT ThreadTaskKill(LPVOID _mothod); //Thread ����

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TESTMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	void tkStart(void);
	afx_msg void OnBnClickedButtonEnd();
	void tkEnd(void);
	CWinThread* p1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_EditTime;
	int m_TestTime;
	CButton m_StartBtn;
	void RemoveSF(void);
	afx_msg void OnBnClickedButtonCtl();
	void ProcessKill(CString processName);
	void TimeSetting(void);
	void MakeDataFile(void);
	void SaveDataFile(void);
	CTime cTime;
	CString m_strEvent;
	CString m_strTime;
	CFile DataFile;
	CString m_strLog;
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void MakeLog(CString log);
	CButton m_CtlBtn;
	CButton m_EndBtn;
	void SetXor();
};
