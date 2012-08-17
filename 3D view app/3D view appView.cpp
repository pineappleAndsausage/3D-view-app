
// 3D view appView.cpp : CMy3DviewappView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "3D view app.h"
#endif

#include "3D view appDoc.h"
#include "3D view appView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DviewappView

IMPLEMENT_DYNCREATE(CMy3DviewappView, CView)

BEGIN_MESSAGE_MAP(CMy3DviewappView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN, &CMy3DviewappView::OnFileOpen)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	
	
END_MESSAGE_MAP()

// CMy3DviewappView 생성/소멸

CMy3DviewappView::CMy3DviewappView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy3DviewappView::~CMy3DviewappView()
{
}

BOOL CMy3DviewappView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy3DviewappView 그리기

void CMy3DviewappView::OnDraw(CDC* /*pDC*/)
{
	CMy3DviewappDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
}


// CMy3DviewappView 진단

#ifdef _DEBUG
void CMy3DviewappView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DviewappView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DviewappDoc* CMy3DviewappView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DviewappDoc)));
	return (CMy3DviewappDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DviewappView 메시지 처리기


int CMy3DviewappView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_rbclk = false;
	m_mbclk = false;
	m_shading = 0;

	CRect rect;
	GetWindowRect(&rect);
	Frame::GetInstance()->Init(GetDC()->m_hDC,rect.right-rect.left,rect.bottom - rect.top);

	SetTimer(0,8,NULL);
	return 0;
}


void CMy3DviewappView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMy3DviewappView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Frame::GetInstance()->ReSizeGLScene(cx,cy);
}


void CMy3DviewappView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString filename;
	LPCTSTR strFilter = { L"|All Files (*.*)|*.*||" };
	CFileDialog FileDlg(TRUE, L".*", NULL, 0, strFilter);
	if( FileDlg.DoModal() == IDOK )
	{		
		filename = FileDlg.GetPathName();
		CT2CA pszConvertedAnsiString(filename);
		std::string f(pszConvertedAnsiString);
		Frame::GetInstance()->m_stl.open(f);
	}
	
}


void CMy3DviewappView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_rbclk = true;
	CView::OnRButtonDown(nFlags, point);
}


void CMy3DviewappView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	double M_PI = 3.14159265358979323846264338327950288;
	RECT rect;	
	GetWindowRect(&rect);		

	int dx = point.x - m_lastpt.x;
	int dy = m_lastpt.y - point.y;
	
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint mid;
	mid.x = (rect.right - rect.left)/2;		
	mid.y = (rect.bottom - rect.top)/2;
	if( m_rbclk ) {
		Frame::GetInstance()->m_camera.rotate(m_lastpt.x - mid.x,m_lastpt.y - mid.y,point.x - mid.x,point.y - mid.y);
			

	}
	else if( m_mbclk ) 
	{		
		Frame::GetInstance()->m_camera.panning(dx,dy);		
	}

	m_lastpt.x = point.x;
	m_lastpt.y = point.y;
	CView::OnMouseMove(nFlags, point);
}


BOOL CMy3DviewappView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	Frame::GetInstance()->set_fov(zDelta / 100.0f);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMy3DviewappView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_rbclk = false;
	CView::OnRButtonUp(nFlags, point);
}


void CMy3DviewappView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Frame::GetInstance()->DrawGLScene();
	CView::OnTimer(nIDEvent);
}


void CMy3DviewappView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mbclk = true;
	CView::OnMButtonDown(nFlags, point);
}


void CMy3DviewappView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mbclk = false;
	CView::OnMButtonUp(nFlags, point);
}
