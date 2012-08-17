
// 3D view appView.h : CMy3DviewappView 클래스의 인터페이스
//

#pragma once
#include "Frame.h"

class CMy3DviewappView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy3DviewappView();
	DECLARE_DYNCREATE(CMy3DviewappView)

protected:
	Frame frame;
	bool m_rbclk;
	bool m_mbclk;
	CPoint m_lastpt;

// 특성입니다.
public:
	CMy3DviewappDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy3DviewappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 3D view appView.cpp의 디버그 버전
inline CMy3DviewappDoc* CMy3DviewappView::GetDocument() const
   { return reinterpret_cast<CMy3DviewappDoc*>(m_pDocument); }
#endif

