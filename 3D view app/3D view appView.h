
// 3D view appView.h : CMy3DviewappView Ŭ������ �������̽�
//

#pragma once
#include "Frame.h"

class CMy3DviewappView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy3DviewappView();
	DECLARE_DYNCREATE(CMy3DviewappView)

protected:
	Frame frame;
	bool m_rbclk;
	bool m_mbclk;
	CPoint m_lastpt;

// Ư���Դϴ�.
public:
	CMy3DviewappDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMy3DviewappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // 3D view appView.cpp�� ����� ����
inline CMy3DviewappDoc* CMy3DviewappView::GetDocument() const
   { return reinterpret_cast<CMy3DviewappDoc*>(m_pDocument); }
#endif

