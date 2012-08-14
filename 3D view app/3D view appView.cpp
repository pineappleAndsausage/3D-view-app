
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
	frame.DrawGLScene();
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
	CRect rect;
	GetWindowRect(&rect);
	frame.Init(GetDC()->m_hDC,rect.right-rect.left,rect.bottom - rect.top);
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
	frame.ReSizeGLScene(cx,cy);
}
