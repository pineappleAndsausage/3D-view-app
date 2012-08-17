
// 3D view appView.cpp : CMy3DviewappView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CMy3DviewappView ����/�Ҹ�

CMy3DviewappView::CMy3DviewappView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy3DviewappView::~CMy3DviewappView()
{
}

BOOL CMy3DviewappView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy3DviewappView �׸���

void CMy3DviewappView::OnDraw(CDC* /*pDC*/)
{
	CMy3DviewappDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	
}


// CMy3DviewappView ����

#ifdef _DEBUG
void CMy3DviewappView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DviewappView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DviewappDoc* CMy3DviewappView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DviewappDoc)));
	return (CMy3DviewappDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DviewappView �޽��� ó����


int CMy3DviewappView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMy3DviewappView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	Frame::GetInstance()->ReSizeGLScene(cx,cy);
}


void CMy3DviewappView::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_rbclk = true;
	CView::OnRButtonDown(nFlags, point);
}


void CMy3DviewappView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	double M_PI = 3.14159265358979323846264338327950288;
	RECT rect;	
	GetWindowRect(&rect);		

	int dx = point.x - m_lastpt.x;
	int dy = m_lastpt.y - point.y;
	
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	Frame::GetInstance()->set_fov(zDelta / 100.0f);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMy3DviewappView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_rbclk = false;
	CView::OnRButtonUp(nFlags, point);
}


void CMy3DviewappView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Frame::GetInstance()->DrawGLScene();
	CView::OnTimer(nIDEvent);
}


void CMy3DviewappView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_mbclk = true;
	CView::OnMButtonDown(nFlags, point);
}


void CMy3DviewappView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_mbclk = false;
	CView::OnMButtonUp(nFlags, point);
}
