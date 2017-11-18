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

// GLViewerView.cpp : implementation of the CGLViewerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GLViewer.h"
#endif

#include "GLViewerDoc.h"
#include "GLViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLViewerView

IMPLEMENT_DYNCREATE(CGLViewerView, CView)

BEGIN_MESSAGE_MAP(CGLViewerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGLViewerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

class CGLContextHelper
{
public:
	CGLContextHelper(HDC hDC)
		: m_hRC(nullptr)
		, m_bState(false)
	{
		ASSERT(hDC != nullptr);
		
		m_hRC = wglCreateContext(hDC);
		ASSERT(m_hRC != nullptr);

		if (m_hRC)
		{
			m_bState = wglMakeCurrent(hDC, m_hRC) == TRUE;
		}
		
		m_bState = m_hRC != nullptr;
		ASSERT(m_bState);
	}

	~CGLContextHelper()
	{
		m_bState = wglMakeCurrent(nullptr, nullptr) == TRUE;
		m_bState = wglDeleteContext(m_hRC) == TRUE;

		ASSERT(m_bState);
	}

private:
	bool	m_bState;
	HGLRC	m_hRC;
};

// CGLViewerView construction/destruction

CGLViewerView::CGLViewerView()
	: m_hRC(nullptr)
	, m_pDC(nullptr)
	, m_bEnableHUD(false)
	, m_unFrameTime(100)
	, m_nCurX(INT_MIN)
	, m_nCurY(INT_MIN)
{
	// TODO: add construction code here
	InitDefaultBackgroundColor();
}

CGLViewerView::~CGLViewerView()
{
}

BOOL CGLViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// WS_CLIPCHILDREN������������ʹ�õ�Windows��������ػ�ʱ�ü��Ӵ��������ǵ�����
	// WS_CLIPSIBLINGS�������Ӵ���ʹ�õ�Windows��������ػ�ʱ���������Ӵ��������ǵ�����
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

void CGLViewerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if (m_vBackgroundColor.size() == 4)
	{
		glClearColor(m_vBackgroundColor.at(0), m_vBackgroundColor.at(1), m_vBackgroundColor.at(2), m_vBackgroundColor.at(3));
	}
	else
	{
		ASSERT(m_vBackgroundColor.size() == 4);
	}
}

// CGLViewerView drawing

void CGLViewerView::OnDraw(CDC* /*pDC*/)
{
	CGLViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_hRC == nullptr)
	{
		m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	}
	
	ASSERT(m_hRC != nullptr);

	if (m_hRC)
	{
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	}

	OnRender();
	OnHUD();
}


// CGLViewerView printing


void CGLViewerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGLViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGLViewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGLViewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

BOOL CGLViewerView::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

void CGLViewerView::OnDestroy()
{
	CView::OnDestroy();

	if (m_hRC)
	{
		::wglDeleteContext(m_hRC);
		m_hRC = nullptr;
	}

	if (m_pDC)
	{
		delete m_pDC;
		m_pDC = nullptr;
	}
	
}

void CGLViewerView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case TIME_FRAME:
		InvalidateRect(nullptr);
		break;
	case TIME_CHECK_LICENSE:
		break;
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void CGLViewerView::OnPaint()
{
	CPaintDC dc(this);
	OnPrepareDC(&dc);
	OnDraw(&dc);
}


int CGLViewerView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CView::OnCreate(lpcs) == -1)
	{
		return -1;
	}

	if (InitializeOpenGL() == FALSE)
	{
		return -1;
	}

	SetTimer(TIME_FRAME, m_unFrameTime, nullptr);
	SetTimer(TIME_CHECK_LICENSE, m_unFrameTime * 100, nullptr);

	EnableHUD(true);

	return 0;
}

void CGLViewerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (nType == SIZE_MINIMIZED || cx <= 0 || cy <= 0)
	{
		return;
	}

	m_nWidth = cx;
	m_nHeight = cy;

	glViewport(0, 0, m_nWidth, m_nHeight);
}

// CGLViewerView diagnostics

#ifdef _DEBUG
void CGLViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CGLViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

BOOL CGLViewerView::InitializeOpenGL()
{
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != nullptr);

	PIXELFORMATDESCRIPTOR pfd;

	if (!SetupPixelFormat())
	{
		return FALSE;
	}

	int nRet = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), nRet, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	return TRUE;
}

BOOL CGLViewerView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // pfd�ṹ�Ĵ�С   
		1,                              // �汾��   
		PFD_DRAW_TO_WINDOW |            // ֧���ڴ����л�ͼ   
		PFD_SUPPORT_OPENGL |            // ֧�� OpenGL   
		PFD_DOUBLEBUFFER,               // ˫����ģʽ   
		PFD_TYPE_RGBA,                  // RGBA ��ɫģʽ   
		24,                             // 24 λ��ɫ���   
		0, 0, 0, 0, 0, 0,               // ������ɫλ   
		0,                              // û�з�͸���Ȼ���   
		0,                              // ������λλ   
		0,                              // ���ۼƻ���   
		0, 0, 0, 0,                     // �����ۼ�λ   
		32,                             // 32 λ��Ȼ���       
		0,                              // ��ģ�建��   
		0,                              // �޸�������   
		PFD_MAIN_PLANE,                 // ����   
		0,                              // ����   
		0, 0, 0                         // ���Բ�,�ɼ��Ժ������ģ   

	};
	int pixelFormat;
	// Ϊ�豸������õ���ƥ������ظ�ʽ   
	if ((pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox(_T("ChoosePixelFormat failed"));
		return FALSE;
	}
	// ������ƥ������ظ�ʽΪ��ǰ�����ظ�ʽ   
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) == FALSE)
	{
		MessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}
	return TRUE;
}

void CGLViewerView::OnRender()
{
	// �����ɫ  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(m_vBackgroundColor.at(0), m_vBackgroundColor.at(1), m_vBackgroundColor.at(2), m_vBackgroundColor.at(3));

	// ���Ƴ���  
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		// ��������ϵ  
		drawUnitAxes();
	}
	glPopMatrix();
	// ����������  
	SwapBuffers(wglGetCurrentDC());
}

void CGLViewerView::drawUnitAxes()
{
	const GLfloat max = (GLfloat)1.0f;//INT_MAX;  
									  // ʵ�߲���  
	glBegin(GL_LINES);
	// x  
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(max, 0.0, 0.0);
	// y  
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, max, 0.0);
	// z  
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, max);
	glEnd();
	// ���߲���  
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 0xAAAA);
	glBegin(GL_LINES);
	// x  
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-max, 0.0, 0.0);
	// y  
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -max, 0.0);
	// z  
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -max);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

CGLViewerDoc* CGLViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLViewerDoc)));
	return (CGLViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CGLViewerView message handlers

CGLViewerView::ErrHUD CGLViewerView::OnHUD()
{
	if (m_bEnableHUD == false)
	{
		return ErrHUD_OFF;
	}

	if (m_hRC == nullptr)
	{
		ASSERT(m_hRC);
		return ErrHUD_GL_CONTEXT;
	}

	if (m_pDC == nullptr)
	{
		ASSERT(m_pDC);
		return ErrHUD_DC_CONTEXT;
	}

	CRect	rectView;
	GetClientRect(rectView);

	rectView.bottom;
	rectView.top;
	rectView.left;
	rectView.right;

	CPoint	pnt;
	GetCursorPos(&pnt);

	pnt.x;
	pnt.y;

	SetCursor(pnt);

	return ErrHUD_ON;
}

void CGLViewerView::SetCursor(CPoint pnt)
{
	m_nCurX = pnt.x;
	m_nCurY = pnt.y;
}

void CGLViewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	SetCursor(point);

	CView::OnMouseMove(nFlags, point);
}

void CGLViewerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 'h':
	case 'H':
	{
		bool bRet = GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT);
		if (bRet)
		{
			EnableHUD(true);
		}		
	}
	default:
		break;
	}
}

BOOL CGLViewerView::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{
	return CView::OnMouseWheel(fFlags, zDelta, point);
}

