#pragma once
class CSameGameBoard
{
public:
	CSameGameBoard();
	~CSameGameBoard();

	

	void SetupBoard();

	COLORREF GetBoardSpace(int row, int col);

	int GetWidth() const 
	{ 
		return m_nWidth; 
	}

	int GetHeight() const
	{
		return m_nHeight;
	}

	int GetColumns() const
	{
		return m_nColumns;
	}

	int GetRows() const
	{
		return m_nRows;
	}

	void DeleteBoard();

	bool IsGameOver() const;

	int GetRemainingCount() const 
	{ 
		return m_nRemaining; 
	}

	int DeleteBlocks(int row, int col);

	int GetNumColors() { return m_nColors; }
	void SetNumColors(int nColors)
	{
		m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;
	}

private:
	
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	int m_nRemaining;
	int m_nColors;

	COLORREF m_arrColors[8];
	int** m_ArrBoard;

	void CreateBoard();

	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);

	void CompactBoard(void);

	//bool IsGameOver() const;
};

