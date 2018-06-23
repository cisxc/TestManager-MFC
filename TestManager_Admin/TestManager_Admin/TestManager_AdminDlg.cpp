
// TestManager_AdminDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TestManager_Admin.h"
#include "TestManager_AdminDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTestManager_AdminDlg 대화 상자




CTestManager_AdminDlg::CTestManager_AdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestManager_AdminDlg::IDD, pParent)
	, m_strLog(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestManager_AdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOG, m_strLog);
}

BEGIN_MESSAGE_MAP(CTestManager_AdminDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTestManager_AdminDlg 메시지 처리기

BOOL CTestManager_AdminDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestManager_AdminDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestManager_AdminDlg::OnPaint()
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
HCURSOR CTestManager_AdminDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestManager_AdminDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nFiles;


	wchar_t szPathName[MAX_PATH];  // 파일 경로명이 들어간다.


	CString strFileName;


	// 드래그앤드롭된 파일의 갯수

	nFiles = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, szPathName, MAX_PATH);



	for (int i = 0; i < nFiles; i++)

	{

		// 파일의 경로 얻어옴

		::DragQueryFile(hDropInfo, i, szPathName, MAX_PATH);

		//MessageBox(szPathName);
		strFileName = (CString)szPathName;

	}

	WORD wd = 0xFEFF;
	int xor = 85;
	CString tmpSt,str;

	CFile DataFile;
	CFile SaveFile;
	SaveFile.Open(_T("Testmanager.txt"),CFile::modeCreate);
	SaveFile.Close();
	DataFile.Open(strFileName, CFile::modeRead);
	SaveFile.Open(_T("Testmanager.txt"),CFile::modeWrite);

	CArchive ar(&DataFile, CArchive::load);
	while(ar.ReadString(str)) tmpSt +=str + _T("\n");
	DataFile.Close();
	ar.Close();
	
   for(int i=0; i< tmpSt.GetLength()-1 ;i++)
   {
	   tmpSt.SetAt(i,tmpSt.GetAt(i)^xor);
   }
   m_strLog = tmpSt;
   UpdateData(FALSE);
	
	SaveFile.Write(&wd,2);   //유니코드 인코딩
	SaveFile.SeekToEnd();
	SaveFile.Write(tmpSt, tmpSt.GetLength()*sizeof(TCHAR)-1);
	SaveFile.Close();
     


	CDialogEx::OnDropFiles(hDropInfo);
}
