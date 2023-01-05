#include "pch.h"
#include "CSameGameBoard.h"


CSameGameBoard::CSameGameBoard() : m_ArrBoard(nullptr), m_nColumns(15), m_nRows(15), m_nHeight(35), m_nWidth(35), m_nRemaining(0), m_nColors(3)
{
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(255, 0, 0); 
	m_arrColors[2] = RGB(255, 255, 64); 
	m_arrColors[3] = RGB(0, 0, 255); 

	m_arrColors[4] = RGB(0, 255, 0);
	m_arrColors[5] = RGB(0, 255, 255);
	m_arrColors[6] = RGB(255, 0, 128);
	m_arrColors[7] = RGB(0, 64, 0);

	//SetupBoard();
}


CSameGameBoard::~CSameGameBoard()
{
	DeleteBoard();
}

void CSameGameBoard::SetupBoard()
{
	if (m_ArrBoard == nullptr)
	{
		CreateBoard();
	}

	for (int i = 0; i < m_nRows; ++i)
	{
		for (int j = 0; j < m_nColumns; ++j)
		{
			m_ArrBoard[i][j] = (rand() % m_nColors) + 1;
		}
	}
	m_nRemaining = m_nRows * m_nColumns;
}

COLORREF CSameGameBoard::GetBoardSpace(int row, int col)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
	{
		return m_arrColors[0];
	}
	return m_arrColors[m_ArrBoard[row][col]];
}


void CSameGameBoard::DeleteBoard()
{
	if (m_ArrBoard != nullptr)
	{
		for (int i = 0; i < m_nRows; ++i)
		{
			if (m_ArrBoard[i] != nullptr)
			{
				delete[] m_ArrBoard[i];
				m_ArrBoard[i] = nullptr;
			}
		}
	}
	delete[] m_ArrBoard;
	m_ArrBoard = nullptr;
}



void CSameGameBoard::CreateBoard()
{
	if (m_ArrBoard != nullptr)
	{
		DeleteBoard();
	}

	m_ArrBoard = new int* [m_nRows];

	for (int i = 0; i < m_nRows; ++i)
	{
		m_ArrBoard[i] = new int[m_nColumns];

		for (int j = 0; j < m_nColumns; ++j)
		{
			m_ArrBoard[i][j] = 0;
		}
	}
}

int CSameGameBoard::DeleteNeighborBlocks(int row, int col, int color, Direction direction)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return 0;

	// Проверка на то, что блок имеет тот же цвет
	if (m_ArrBoard[row][col] != color)
		return 0;
	int nCount = 1;
	m_ArrBoard[row][col] = 0;

	// Выполняем проверку направлений

	if (direction != DIRECTION_UP)
		nCount += DeleteNeighborBlocks(row - 1, col, color, DIRECTION_DOWN);
	if (direction != DIRECTION_DOWN)
		nCount += DeleteNeighborBlocks(row + 1, col, color, DIRECTION_UP);
	if (direction != DIRECTION_LEFT)
		nCount += DeleteNeighborBlocks(row, col - 1, color, DIRECTION_RIGHT);
	if (direction != DIRECTION_RIGHT)
		nCount += DeleteNeighborBlocks(row, col + 1, color, DIRECTION_LEFT);

	return nCount;
}



int CSameGameBoard::DeleteBlocks(int row, int col)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return -1;

	int nColor = m_ArrBoard[row][col];
	if (nColor == 0)
		return -1;

	int nCount = -1;
	if ((row - 1 >= 0 && m_ArrBoard[row - 1][col] == nColor) ||
		(row + 1 < m_nRows && m_ArrBoard[row + 1][col] == nColor) ||
		(col - 1 >= 0 && m_ArrBoard[row][col - 1] == nColor) ||
		(col + 1 < m_nColumns && m_ArrBoard[row][col + 1] == nColor))
	{
		m_ArrBoard[row][col] = 0;
		nCount = 1;

		nCount += DeleteNeighborBlocks(row - 1, col, nColor, DIRECTION_DOWN);

		nCount += DeleteNeighborBlocks(row + 1, col, nColor, DIRECTION_UP);

		nCount += DeleteNeighborBlocks(row, col - 1, nColor, DIRECTION_RIGHT);

		nCount += DeleteNeighborBlocks(row, col + 1, nColor, DIRECTION_LEFT);

		CompactBoard();

		m_nRemaining -= nCount;
	}

	return nCount;
}


void CSameGameBoard::CompactBoard()
{
	for (int col = 0; col < m_nColumns; col++)
	{
		int nNextEmptyRow = m_nRows - 1;
		int nNextOccupiedRow = nNextEmptyRow;
		while (nNextOccupiedRow >= 0 && nNextEmptyRow >= 0)
		{
			
			while (nNextEmptyRow >= 0 &&
				m_ArrBoard[nNextEmptyRow][col] != 0)
				nNextEmptyRow--;
			if (nNextEmptyRow >= 0)
			{
				
				nNextOccupiedRow = nNextEmptyRow - 1;
				while (nNextOccupiedRow >= 0 &&
					m_ArrBoard[nNextOccupiedRow][col] == 0)
					nNextOccupiedRow--;
				if (nNextOccupiedRow >= 0)
				{
					
					m_ArrBoard[nNextEmptyRow][col] =
						m_ArrBoard[nNextOccupiedRow][col];
					m_ArrBoard[nNextOccupiedRow][col] = 0;
				}
			}
		}
	}
	
	int nNextEmptyCol = 0;
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns)
	{
		
		while (nNextEmptyCol < m_nColumns &&
			m_ArrBoard[m_nRows - 1][nNextEmptyCol] != 0)
			nNextEmptyCol++;
		if (nNextEmptyCol < m_nColumns)
		{
			
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < m_nColumns &&
				m_ArrBoard[m_nRows - 1][nNextOccupiedCol] == 0)
				nNextOccupiedCol++;
			if (nNextOccupiedCol < m_nColumns)
			{
				
				for (int row = 0; row < m_nRows; row++)
				{
					m_ArrBoard[row][nNextEmptyCol] = m_ArrBoard[row][nNextOccupiedCol];
					m_ArrBoard[row][nNextOccupiedCol] = 0;
				}
			}
		}
	}
}

bool CSameGameBoard::IsGameOver() const
{
	for (int col = 0; col < m_nColumns; col++)
	{
		
		for (int row = m_nRows - 1; row >= 0; row--)
		{
			int nColor = m_ArrBoard[row][col];

			
			if (nColor == 0)
				break;
			else
			{
				
				if (row - 1 >= 0 &&
					m_ArrBoard[row - 1][col] == nColor)
					return false;
				else if (col + 1 < m_nColumns &&
					m_ArrBoard[row][col + 1] == nColor)
					return false;
			}
		}
	}
	
	return true;
}