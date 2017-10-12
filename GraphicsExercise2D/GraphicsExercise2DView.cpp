
// GraphicsExercise2DView.cpp : CGraphicsExercise2DView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GraphicsExercise2D.h"
#endif

#include "GraphicsExercise2DDoc.h"
#include "GraphicsExercise2DView.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicsExercise2DView

IMPLEMENT_DYNCREATE(CGraphicsExercise2DView, CView)

BEGIN_MESSAGE_MAP(CGraphicsExercise2DView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsExercise2DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphicsExercise2DView 构造/析构

CGraphicsExercise2DView::CGraphicsExercise2DView()
{
	// TODO: 在此处添加构造代码

	// -------------------- 初始化设置 -------------------------

	// 设置规模比例
	SetScale(70);

	// 设置绘制的函数
	SetDrawFunction(Sin);

	// 设置自变量x范围[startX, endX]、取样步长step
	SetPlotSin((float)0.0, (float)6.3, (float)0.01);
}

CGraphicsExercise2DView::~CGraphicsExercise2DView()
{
}

BOOL CGraphicsExercise2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// 设置范围和步长
void CGraphicsExercise2DView::SetPlotSin(float startX, float endX, float step)
{
	this->startX = startX;
	this->endX = endX;
	this->step = step;
}

// 设置绘制的函数
void CGraphicsExercise2DView::SetDrawFunction(Function fun)
{
	this->fun = fun;
}

// 设置规模
void CGraphicsExercise2DView::SetScale(int scale)
{
	this->scale = scale;
}

// 变换规模
float CGraphicsExercise2DView::TransformScale(float num)
{
	return num * scale;
}

// 变换x的坐标和规模
float CGraphicsExercise2DView::TransformCoordinateScaleX(float x)
{
	return TransformScale(x + 2);
}

// 变换y的坐标和规模
float CGraphicsExercise2DView::TransformCoordinateScaleY(float y)
{
	return TransformScale(y + 4);
}

// CGraphicsExercise2DView 绘制

void CGraphicsExercise2DView::OnDraw(CDC* pDC)
{
	CGraphicsExercise2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	// -------------------- 绘制坐标系 -------------------------

	float endPointX = 2 + endX + 2;

	// 坐标y轴
	pDC->MoveTo((int)TransformScale(2), (int)TransformScale(2));
	pDC->LineTo((int)TransformScale(2), (int)TransformScale(6));

	// 坐标x轴
	pDC->MoveTo((int)TransformScale(2), (int)TransformScale(4));
	pDC->LineTo((int)TransformScale(endPointX), (int)TransformScale(4));

	// 坐标y轴的箭头
	pDC->MoveTo((int)TransformScale((float)1.8), (int)TransformScale((float)2.2));
	pDC->LineTo((int)TransformScale(2), (int)TransformScale(2));
	pDC->LineTo((int)TransformScale((float)2.2), (int)TransformScale((float)2.2));

	// 坐标x轴的箭头
	pDC->MoveTo((int)TransformScale(endPointX - (float)0.2), (int)TransformScale((float)3.8));
	pDC->LineTo((int)TransformScale(endPointX), (int)TransformScale(4));
	pDC->LineTo((int)TransformScale(endPointX - (float)0.2), (int)TransformScale((float)4.2));

	// -------------------- 绘制刻度线 -------------------------

	// 绘制y轴刻度线
	for (float scaleY = 3; scaleY <= 5; scaleY += 0.2)
	{
		pDC->MoveTo((int)TransformScale(2), (int)TransformScale(scaleY));
		pDC->LineTo((int)TransformScale((float)2.1), (int)TransformScale(scaleY));
	}

	// 绘制x轴刻度线
	for (float scaleX = 2.2; scaleX < endPointX - 1; scaleX += 0.2)
	{
		pDC->MoveTo((int)TransformScale(scaleX), (int)TransformScale(4));
		pDC->LineTo((int)TransformScale(scaleX), (int)TransformScale(3.9));
	}


	// -------------------- 绘制文字 -------------------------

	// 绘制y轴的y
	pDC->TextOutW((int)TransformScale(1.8), (int)TransformScale(2.3), CString("y"));
	// 绘制x轴的x
	pDC->TextOutW((int)TransformScale(endPointX - (float)0.5), (int)TransformScale(4.1), CString("x"));

	CString s;
	// 绘制y轴刻度文字
	for (float ScaleTextY = 2.9, text = 1.0; ScaleTextY <= 4.9; ScaleTextY += 0.2, text -= 0.2)
	{
		s.Format(_T("%.1f"), text);
		pDC->TextOutW((int)TransformScale(1.6), (int)TransformScale(ScaleTextY), s);
	}

	// 绘制x轴刻度文字
	for (float ScaleTextX = 2.3; ScaleTextX < endPointX - 1; ScaleTextX += 0.4)
	{
		s.Format(_T("%.1f"), ScaleTextX - 1.9);
		pDC->TextOutW((int)TransformScale(ScaleTextX), (int)TransformScale(4.1), s);
	}

	// 绘制函数图的Title
	// 判断调用的函数
	switch (fun)
	{
	case Sin:
		pDC->TextOutW((int)TransformScale(4), (int)TransformScale(6), CString("y = sin( x )"));
		break;
	case Cos:
		pDC->TextOutW((int)TransformScale(4), (int)TransformScale(6), CString("y = cos( x )"));
		break;
	default:
		break;
	}


	// -------------------- 绘制函数 -------------------------

	// 不改变坐标和规模的xy
	float x, y;

	for (x = startX; x <= endX; x += step)
	{
		// 判断调用的函数
		switch (fun)
		{
		case Sin:
			y = (float)sin(x);
			break;
		case Cos:
			y = (float)cos(x);
			break;
		default:
			break;
		}

		// 对xy改变坐标和规模再显示点
		pDC->SetPixel((int)TransformCoordinateScaleX(x), (int)TransformCoordinateScaleY(y), 0);
	}
}


// CGraphicsExercise2DView 打印


void CGraphicsExercise2DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicsExercise2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphicsExercise2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphicsExercise2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGraphicsExercise2DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicsExercise2DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicsExercise2DView 诊断

#ifdef _DEBUG
void CGraphicsExercise2DView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsExercise2DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsExercise2DDoc* CGraphicsExercise2DView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsExercise2DDoc)));
	return (CGraphicsExercise2DDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicsExercise2DView 消息处理程序
