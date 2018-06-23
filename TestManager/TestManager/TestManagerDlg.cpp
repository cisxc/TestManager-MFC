
// TestManagerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TestManager.h"
#include "TestManagerDlg.h"
#include "afxdialogex.h"
#include <tlhelp32.h>
#include "WebDlg.h"
#define TASKILL 100
#define TEST 101
#define RMSF 102
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <LMShare.h>                   //공유폴더
#include <Lmapibuf.h>
#pragma comment(lib, "Netapi32.lib")

#include <Dbt.h> //usb 헤더


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CTestManagerDlg 대화 상자




CTestManagerDlg::CTestManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestManagerDlg::IDD, pParent)
	, p1(NULL)
	, m_TestTime(0)
	, cTime(0)
	, m_strEvent(_T(""))
	, m_strTime(_T(""))
	, m_strLog(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIME, m_EditTime);
	DDX_Text(pDX, IDC_EDIT_TIME, m_TestTime);
	DDX_Control(pDX, IDC_BUTTON_START, m_StartBtn);
	DDX_Control(pDX, IDC_BUTTON_CTL, m_CtlBtn);
	DDX_Control(pDX, IDC_BUTTON_END, m_EndBtn);
}

BEGIN_MESSAGE_MAP(CTestManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTestManagerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_END, &CTestManagerDlg::OnBnClickedButtonEnd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CTL, &CTestManagerDlg::OnBnClickedButtonCtl)
END_MESSAGE_MAP()


// CTestManagerDlg 메시지 처리기

BOOL CTestManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	p1=NULL;
	MakeDataFile();
	m_CtlBtn.EnableWindow(FALSE);
	m_EndBtn.EnableWindow(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestManagerDlg::TimeSetting(void)
{
   cTime = CTime::GetCurrentTime();
   m_strTime.Format(_T("%02d : %02d : %02d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
}


void CTestManagerDlg::MakeDataFile(void)
{
    DataFile.Open(_T("TestLog.rpt"), CFile::modeCreate);
    DataFile.Close();
}

void CTestManagerDlg::SaveDataFile(void)
{
	     

   DataFile.Open(_T("TestLog.rpt"), CFile::modeWrite);
   SetXor();
   DataFile.Write(m_strLog, m_strLog.GetLength()*sizeof(TCHAR));
   DataFile.Close();
}

void CTestManagerDlg::MakeLog(CString log)
{
	TimeSetting();
	m_strLog = m_strLog + _T("\r\n") + m_strTime + _T(" / ") + log ;
}

void CTestManagerDlg::ProcessKill(CString processName)
{
	HANDLE hProcess;
	PROCESSENTRY32 pe32 = {0};
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcess == (HANDLE)-1) return;

	if(Process32First(hProcess,&pe32))
	{
		while(_tcscmp(pe32.szExeFile,processName))
		{
			if(Process32Next(hProcess,&pe32)==false) return;
		}
		HANDLE hCloseProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);

		if(TerminateProcess(hCloseProcess,0)){
			unsigned long nExitCode;
			GetExitCodeProcess(hProcess,&nExitCode);
			MakeLog(processName+_T("종료"));
			TRACE(_T("EXIT code is %f \n"),nExitCode);
		}
		CloseHandle(hCloseProcess);
	}
	CloseHandle(hProcess);
}


void CTestManagerDlg::OnBnClickedButtonStart()
{
 
	UpdateData(TRUE);
	if(m_TestTime<=0)
	{
		MessageBox(_T("0 이상의 수를 입력하세요"));
		return;
	}
	SetTimer(TASKILL , 10000 , 0);
	SetTimer(TEST , m_TestTime*1000 , 0);
	SetTimer(RMSF , 60000 , 0);
	m_EditTime.EnableWindow(FALSE);
	m_StartBtn.EnableWindow(FALSE);
	m_CtlBtn.EnableWindow(TRUE);
	m_EndBtn.EnableWindow(TRUE);
	MakeLog(_T("시험시작"));
	
}

void CTestManagerDlg::tkEnd(void)
{
	if (MessageBox( _T("시험을 끝내겠습니까?"),_T("시험 종료"),MB_YESNO)==IDYES) 
	{
		m_EndBtn.EnableWindow(FALSE);
		KillTimer(TASKILL);
		KillTimer(TEST);
		KillTimer(RMSF);
		MakeLog(_T("시험종료"));
		SaveDataFile();
	}
	else 
	{
	
	}
	
}

void CTestManagerDlg::OnBnClickedButtonEnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	tkEnd();
	
}





void CTestManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(nIDEvent)
	{
	case TASKILL:
		ProcessKill(_T("chrome.exe"));
		ProcessKill(_T("iexplore.exe"));
		ProcessKill(_T("opera.exe"));
		ProcessKill(_T("firefox.exe"));
		ProcessKill(_T("MicrosoftEdge.exe"));
		break;
	case TEST:
		m_TestTime--;
		UpdateData(FALSE);
		if(m_TestTime==5)
			SaveDataFile();
		if(m_TestTime==0)
		{
			tkEnd();
		}
		break;
	case RMSF:
		RemoveSF();
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CTestManagerDlg::RemoveSF(void)
{
PSHARE_INFO_502 BufPtr;
NET_API_STATUS res;
LPTSTR lpszServer = NULL;
DWORD er = 0, tr = 0, resume = 0;
DWORD total = 0;

do
{
    res = NetShareEnum(lpszServer, 502, (LPBYTE *)&BufPtr, MAX_PREFERRED_LENGTH, &er, &tr, &resume);
    if (res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
    {
        total += er;
        PSHARE_INFO_502 p = BufPtr;

        DWORD i = 0;
        for (i = 1; i <= er; i++)
        {
            if (STYPE_IPC != (p->shi502_type & 0x000000FF))
            {
                TCHAR ParamBuf[128] = {0,};
                TCHAR *pFormat = _T("share \"%s\" /delete");
				
                wsprintf(ParamBuf, pFormat, p->shi502_netname);

                SHELLEXECUTEINFO rSEI = {0};
                rSEI.cbSize = sizeof(rSEI);
                rSEI.lpVerb = _T("open");
                rSEI.lpFile = _T("net");
                rSEI.lpParameters = ParamBuf;
                rSEI.nShow = SW_HIDE;
                rSEI.fMask = SEE_MASK_NOCLOSEPROCESS;

                if (TRUE == ShellExecuteEx(&rSEI))
                {
                    //성공
					MakeLog(ParamBuf); // LOG쓰기
                }

                DWORD nStatus = WaitForSingleObject(rSEI.hProcess, INFINITE);
                if (WAIT_OBJECT_0 != nStatus)
                {
                }
            }
            p++;
        }

        NetApiBufferFree(BufPtr);
    }
} while (res == ERROR_MORE_DATA);


}


void CTestManagerDlg::OnBnClickedButtonCtl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MakeLog(_T("CTL2 접속"));
	WebDlg dlg;
	dlg.DoModal();
	

}


LRESULT CTestManagerDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	  
   if(message == WM_DEVICECHANGE)
   {
    
        UINT event = (UINT)wParam;

        switch(event){
            case DBT_DEVICEARRIVAL :
                // USB 연결시작
				m_strEvent.Format(_T("USB Connected"));
				MakeLog(m_strEvent);
                break;
            case DBT_DEVICEQUERYREMOVE :
                // USB 연결해제
				m_strEvent.Format(_T("USB DisConnected"));
				MakeLog(m_strEvent);
                break;
            }
   }
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}





void CTestManagerDlg::SetXor()
{
	int xor = 85;
   for(int i=0; i< m_strLog.GetLength() ;i++)
   {
	   m_strLog.SetAt(i,m_strLog.GetAt(i)^xor);
   }
}
