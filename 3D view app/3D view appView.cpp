
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
	frame.DrawGLScene();
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
	CRect rect;
	GetWindowRect(&rect);
	frame.Init(GetDC()->m_hDC,rect.right-rect.left,rect.bottom - rect.top);
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
	frame.ReSizeGLScene(cx,cy);
}
