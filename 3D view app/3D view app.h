
// 3D view app.h : 3D view app ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy3DviewappApp:
// �� Ŭ������ ������ ���ؼ��� 3D view app.cpp�� �����Ͻʽÿ�.
//

class CMy3DviewappApp : public CWinApp
{
public:
	CMy3DviewappApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3DviewappApp theApp;
