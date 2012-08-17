
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "3D view app.h"

#include "MainFrm.h"
#include "Frame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_SHADING_GOURAUD, &CMainFrame::OnShadingGouraud)
	ON_COMMAND(ID_SHADING_FLAT, &CMainFrame::OnShadingFlat)
END_MESSAGE_MAP()

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����


void CMainFrame::OnShadingGouraud()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Frame::GetInstance()->m_shading = 1;
	CMenu *menu = GetMenu();
	menu->CheckMenuItem(ID_SHADING_GOURAUD,MF_CHECKED);
	menu->CheckMenuItem(ID_SHADING_FLAT,MF_UNCHECKED);
}


void CMainFrame::OnShadingFlat()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Frame::GetInstance()->m_shading = 0;
	CMenu *menu = GetMenu();	
	menu->CheckMenuItem(ID_SHADING_FLAT,MF_CHECKED);
	menu->CheckMenuItem(ID_SHADING_GOURAUD,MF_UNCHECKED);
}
