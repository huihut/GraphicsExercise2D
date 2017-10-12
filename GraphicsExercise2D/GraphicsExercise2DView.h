
// GraphicsExercise2DView.h : CGraphicsExercise2DView 类的接口
//

#pragma once

// 支持绘制的函数类型
enum Function { Sin, Cos };

class CGraphicsExercise2DView : public CView
{
protected: // 仅从序列化创建
	CGraphicsExercise2DView();
	DECLARE_DYNCREATE(CGraphicsExercise2DView)

// 特性
public:
	CGraphicsExercise2DDoc* GetDocument() const;

// 操作
public:
	void SetPlotSin(float startX, float endX, float step);
	void SetDrawFunction(Function fun);
	void SetScale(int scale);

	float TransformScale(float num);
	float TransformCoordinateScaleX(float x);
	float TransformCoordinateScaleY(float y);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphicsExercise2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	int scale;
	float startX, endX, step;
	Function fun;
};

#ifndef _DEBUG  // GraphicsExercise2DView.cpp 中的调试版本
inline CGraphicsExercise2DDoc* CGraphicsExercise2DView::GetDocument() const
   { return reinterpret_cast<CGraphicsExercise2DDoc*>(m_pDocument); }
#endif

