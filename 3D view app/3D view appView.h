
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
};

#ifndef _DEBUG  // 3D view appView.cpp�� ����� ����
inline CMy3DviewappDoc* CMy3DviewappView::GetDocument() const
   { return reinterpret_cast<CMy3DviewappDoc*>(m_pDocument); }
#endif
