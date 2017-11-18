// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// GLViewerView.h : interface of the CGLViewerView class
//

#pragma once

class CGLViewerView : public CView
{
protected: // create from serialization only
	CGLViewerView();
	DECLARE_DYNCREATE(CGLViewerView)

// Attributes
public:
	CGLViewerDoc* GetDocument() const;

// Operations
public:
	bool	SetFrameTime(unsigned int unFrameTime) { m_unFrameTime = unFrameTime; return true; }

	enum ErrHUD
	{
		ErrHUD_GL_CONTEXT = -3,
		ErrHUD_DC_CONTEXT = -2,
		ErrHUD_OFF = -1,
		ErrHUD_ON = 0,
	};
	virtual ErrHUD OnHUD();
	void	EnableHUD(bool bEnable) { m_bEnableHUD = bEnable; }
	bool	IsEnableHUD() { return m_bEnableHUD; }

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate() override;
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGLViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	enum TIMER_ID
	{
		TIME_FRAME = 1,
		TIME_CHECK_LICENSE,
	};

	virtual void OnRender();

	BOOL InitializeOpenGL();    //初始化 OpenGL  
	BOOL SetupPixelFormat();    //设置像素格式  
	//void RenderScene();         //绘制场景

	void drawUnitAxes();

	void SetCursor(CPoint pnt);

	void InitDefaultBackgroundColor()
	{
		m_vBackgroundColor.push_back(0.2f);
		m_vBackgroundColor.push_back(0.3f);
		m_vBackgroundColor.push_back(0.5f);
		m_vBackgroundColor.push_back(1.0f);
	}

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT fFlags, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	HGLRC		m_hRC;			//Rendering Context着色描述表
	CClientDC*	m_pDC;			//Device Context设备描述表

	int m_nWidth;
	int m_nHeight;

	std::vector<float>	m_vBackgroundColor;

	unsigned int m_unFrameTime;

	bool	m_bEnableHUD;

	int		m_nCurX;
	int		m_nCurY;
};

#ifndef _DEBUG  // debug version in GLViewerView.cpp
inline CGLViewerDoc* CGLViewerView::GetDocument() const
   { return reinterpret_cast<CGLViewerDoc*>(m_pDocument); }
#endif

