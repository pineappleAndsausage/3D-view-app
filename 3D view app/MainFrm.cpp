
// MainFrm.cpp : CMainFrame 클래스의 구현
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

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

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


// CMainFrame 메시지 처리기


void CMainFrame::OnShadingGouraud()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Frame::GetInstance()->m_shading = 1;
	CMenu *menu = GetMenu();
	menu->CheckMenuItem(ID_SHADING_GOURAUD,MF_CHECKED);
	menu->CheckMenuItem(ID_SHADING_FLAT,MF_UNCHECKED);
}


void CMainFrame::OnShadingFlat()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Frame::GetInstance()->m_shading = 0;
	CMenu *menu = GetMenu();	
	menu->CheckMenuItem(ID_SHADING_FLAT,MF_CHECKED);
	menu->CheckMenuItem(ID_SHADING_GOURAUD,MF_UNCHECKED);
}
