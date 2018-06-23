
// TestManagerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "atltime.h"


// CTestManagerDlg 대화 상자
class CTestManagerDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestManagerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	 static UINT ThreadTaskKill(LPVOID _mothod); //Thread 생성

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TESTMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
