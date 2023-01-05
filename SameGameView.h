
// SameGameView.h: интерфейс класса CSameGameView
//

#pragma once


class CSameGameView : public CView
{
protected: // создать только из сериализации
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

// Атрибуты
public:
	CSameGameDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	void ResizeWindow();

	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLevel1();
	afx_msg void OnUpdateLevel1(CCmdUI* pCmdUI);
	afx_msg void OnLevel2();
	afx_msg void OnUpdateLevel2(CCmdUI* pCmdUI);
	afx_msg void OnLevel3();
	afx_msg void OnUpdateLevel3(CCmdUI* pCmdUI);
	afx_msg void OnLevel4();
	afx_msg void OnUpdateLevel4(CCmdUI* pCmdUI);
	afx_msg void OnLevel5();
	afx_msg void OnUpdateLevel5(CCmdUI* pCmdUI);
	void setColorCount(int numColors);
	void SetChecker(int level, CCmdUI* pCmdUI);

};

#ifndef _DEBUG  // версия отладки в SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

