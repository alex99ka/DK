#pragma once
#include "Item.h"
#include<iostream>

static constexpr int BORDER_HIGHT = 27;
static constexpr int BORDER_WIDTH = 82;

class CBoard
{
	static constexpr int SIZE_LEVEL_STOCK = 7;
	static constexpr int UNUSED_LEVEL = -1;
	static constexpr char BOARDER_SYMB = 'Q';
	static constexpr char FLOOR_SYMB = '=';
	static constexpr char MOVE_RIGHT_SYMB = '>';
	static constexpr char MOVE_LEFT_SYMB = '<';
	static constexpr char LADDER_SYMB = 'H';
	static constexpr char SPACE_SYMB = ' ';
	static constexpr CColorPoint::c_color BoarderColor = CColoredPrint::c_color::RED;
	static constexpr CColorPoint::c_color FloorColor = CColoredPrint::c_color::YELLOW;
	static constexpr CColorPoint::c_color ArrowColor = CColoredPrint::c_color::MAGENTA;
	static constexpr CColorPoint::c_color LadderColor = CColoredPrint::c_color::BLUE;

	
public:
	enum Board_Place { BOARDER, FLOOR, LADDER, FREE, OUT_OB, ARROW_RIGHT, ARROW_LEFT };

	void Init(bool isColored, char board[][BORDER_WIDTH - 2]);
	void SetColored(bool isColored) { m_IsColored = isColored; }
	void Draw() const;
	enum Board_Place GetBoardPlace(CPoint& const point) const ;
	bool GetBoardSymbol(CPoint& coord, char* symbol, CColorPoint::c_color* color) const;
	void operator=(const char board[][BORDER_WIDTH - 2])
	{
		for (int i = 1 , k = 0; k < BORDER_HIGHT - 2; k++, i++)
		{
			for (int j = 1, l = 0; l < BORDER_WIDTH -2;  l++ ,j++)
			{
				WorkBoard[i][j] = board[k][l];
				PrintBoard[k][l] = board[k][l];
			}
		} 
	}
private:
	//void RestoreBoard
	void DrawOneChar(char ch) const;
	// creates an array that inicates for each floor where to create white spaces
	bool ValidatePoint(CPoint& const point) const;
	CColorPoint::c_color GetCharColor(char ch) const;

	char WorkBoard[BORDER_HIGHT][BORDER_WIDTH] = {};
	char PrintBoard[BORDER_HIGHT-2][BORDER_WIDTH-2] = {};
	bool m_IsColored = true;
};



