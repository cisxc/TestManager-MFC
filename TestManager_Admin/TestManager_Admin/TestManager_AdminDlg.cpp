
// TestManager_AdminDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TestManager_Admin.h"
#include "TestManager_AdminDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTestManager_AdminDlg ��ȭ ����




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


// CTestManager_AdminDlg �޽��� ó����

BOOL CTestManager_AdminDlg::OnInitDialog()
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestManager_AdminDlg::OnPaint()
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
HCURSOR CTestManager_AdminDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestManager_AdminDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int nFiles;


	wchar_t szPathName[MAX_PATH];  // ���� ��θ��� ����.


	CString strFileName;


	// �巡�׾ص�ӵ� ������ ����

	nFiles = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, szPathName, MAX_PATH);



	for (int i = 0; i < nFiles; i++)

	{

		// ������ ��� ����

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
	
	SaveFile.Write(&wd,2);   //�����ڵ� ���ڵ�
	SaveFile.SeekToEnd();
	SaveFile.Write(tmpSt, tmpSt.GetLength()*sizeof(TCHAR)-1);
	SaveFile.Close();
     


	CDialogEx::OnDropFiles(hDropInfo);
}
