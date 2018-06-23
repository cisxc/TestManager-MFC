
// TestManagerDlg.cpp : ���� ����
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

#include <LMShare.h>                   //��������
#include <Lmapibuf.h>
#pragma comment(lib, "Netapi32.lib")

#include <Dbt.h> //usb ���


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CTestManagerDlg ��ȭ ����




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


// CTestManagerDlg �޽��� ó����

BOOL CTestManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	p1=NULL;
	MakeDataFile();
	m_CtlBtn.EnableWindow(FALSE);
	m_EndBtn.EnableWindow(FALSE);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
			MakeLog(processName+_T("����"));
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
		MessageBox(_T("0 �̻��� ���� �Է��ϼ���"));
		return;
	}
	SetTimer(TASKILL , 10000 , 0);
	SetTimer(TEST , m_TestTime*1000 , 0);
	SetTimer(RMSF , 60000 , 0);
	m_EditTime.EnableWindow(FALSE);
	m_StartBtn.EnableWindow(FALSE);
	m_CtlBtn.EnableWindow(TRUE);
	m_EndBtn.EnableWindow(TRUE);
	MakeLog(_T("�������"));
	
}

void CTestManagerDlg::tkEnd(void)
{
	if (MessageBox( _T("������ �����ڽ��ϱ�?"),_T("���� ����"),MB_YESNO)==IDYES) 
	{
		m_EndBtn.EnableWindow(FALSE);
		KillTimer(TASKILL);
		KillTimer(TEST);
		KillTimer(RMSF);
		MakeLog(_T("��������"));
		SaveDataFile();
	}
	else 
	{
	
	}
	
}

void CTestManagerDlg::OnBnClickedButtonEnd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	tkEnd();
	
}





void CTestManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
                    //����
					MakeLog(ParamBuf); // LOG����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MakeLog(_T("CTL2 ����"));
	WebDlg dlg;
	dlg.DoModal();
	

}


LRESULT CTestManagerDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	  
   if(message == WM_DEVICECHANGE)
   {
    
        UINT event = (UINT)wParam;

        switch(event){
            case DBT_DEVICEARRIVAL :
                // USB �������
				m_strEvent.Format(_T("USB Connected"));
				MakeLog(m_strEvent);
                break;
            case DBT_DEVICEQUERYREMOVE :
                // USB ��������
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
