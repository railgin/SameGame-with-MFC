
// SameGameView.cpp: реализация класса CSameGameView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(Level1, &CSameGameView::OnLevel1)
	ON_UPDATE_COMMAND_UI(Level1, &CSameGameView::OnUpdateLevel1)
	ON_COMMAND(Level2, &CSameGameView::OnLevel2)
	ON_UPDATE_COMMAND_UI(Level2, &CSameGameView::OnUpdateLevel2)
	ON_COMMAND(Level3, &CSameGameView::OnLevel3)
	ON_UPDATE_COMMAND_UI(Level3, &CSameGameView::OnUpdateLevel3)
	ON_COMMAND(Level4, &CSameGameView::OnLevel4)
	ON_UPDATE_COMMAND_UI(Level4, &CSameGameView::OnUpdateLevel4)
	ON_COMMAND(Level5, &CSameGameView::OnLevel5)
	ON_UPDATE_COMMAND_UI(Level5, &CSameGameView::OnUpdateLevel5)
END_MESSAGE_MAP()




// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
	// TODO: добавьте код создания

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* pDC)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int nDCSave = pDC->SaveDC();

	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);


	pDC->FillSolidRect(&rcClient, clr);

	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{

			clr = pDoc->GetBoardSpace(row, col);

			// Вычисляем размер и позицию игрового пространства
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			// Заполняем блок соответствующим цветом
			pDC->FillSolidRect(&rcBlock, clr);

			// Рисуем контур
			pDC->Rectangle(&rcBlock);
		}
	}

	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSameGameView


void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	ResizeWindow();

	// TODO: добавьте специализированный код или вызов базового класса
}

void CSameGameView::ResizeWindow()
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// Изменяем размеры окна, исходя из размеров нашей доски
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;

	// Функция MoveWindow() изменяет размер окна фрейма
	GetParentFrame()->MoveWindow(&rcWindow);
}


void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;//возврат из метода, передача управления вызывающему методу

	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();

	int count = pDoc->DeleteBlocks(row, col);

	if (count > 0)
	{
		Invalidate();
		UpdateWindow();


		if (pDoc->isGameOver())
		{
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"), remaining);

			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}




	CView::OnLButtonDown(nFlags, point);
}


void CSameGameView::OnLevel1()
{
	setColorCount(3);
}


void CSameGameView::OnUpdateLevel1(CCmdUI* pCmdUI)
{
	SetChecker(3, pCmdUI);
}


void CSameGameView::OnLevel2()
{

	setColorCount(4);
}


void CSameGameView::OnUpdateLevel2(CCmdUI* pCmdUI)
{
	SetChecker(4, pCmdUI);
}


void CSameGameView::OnLevel3()
{
	setColorCount(5);
}


void CSameGameView::OnUpdateLevel3(CCmdUI* pCmdUI)
{
	SetChecker(5, pCmdUI);
}


void CSameGameView::OnLevel4()
{
	setColorCount(6);
}


void CSameGameView::OnUpdateLevel4(CCmdUI* pCmdUI)
{
	SetChecker(6, pCmdUI);
}


void CSameGameView::OnLevel5()
{
	setColorCount(7);
}


void CSameGameView::OnUpdateLevel5(CCmdUI* pCmdUI)
{
	SetChecker(7, pCmdUI);
}

void CSameGameView::setColorCount(int numColors)
{
	// Сначала получаем указатель на документ
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// Устанавливаем количество цветов 
	pDoc->SetNumColors(numColors);
	// Перерисовываем View
	Invalidate();
	UpdateWindow();
}

void CSameGameView::SetChecker(int level, CCmdUI* pCmdUI)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == level);
}

