
// TestManager_Admin.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTestManager_AdminApp:
// �� Ŭ������ ������ ���ؼ��� TestManager_Admin.cpp�� �����Ͻʽÿ�.
//

class CTestManager_AdminApp : public CWinApp
{
public:
	CTestManager_AdminApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestManager_AdminApp theApp;