#pragma once
#include "Item.h"
#include<iostream>

static constexpr int BORDER_HIGHT = 27;
static constexpr int BORDER_WIDTH = 82;
// a node that states when to start and end a gap on the platform
typedef struct SPACES {
	int begining;
	int end;
	struct SPACES* next;
	enum directions { Left, Right };
	int direction;//direction type for the barrels for each floor '0'=Left '1'=right
}Spaces;

typedef struct LIST
{
	Spaces* head;
	Spaces* tail;
}List;

//a node that states where to put each Ladder and wich type of Ladder we need?
typedef struct Ladder {
	int level;
	enum LadderType { Full, Half, Broken };
	LadderType type;//FULL Ladder='0',HALF_A_Ladder='1',BROKEN Ladder='2';
	int index_of_Ladder;
	int size; //lenght of thr Ladder
	struct Ladder* next;
}Ladder;

typedef struct ListOfLadders
{
	Ladder* head;
	Ladder* tail;
}ListOfLadders;

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

	int levels[SIZE_LEVEL_STOCK] = { 24,22,19,15,9,7,4 };
public:
	enum Board_Place { BOARDER, FLOOR, LADDER, FREE, OUT_OB, ARROW_RIGHT, ARROW_LEFT };

	void Init(bool isColored, char board[][BORDER_WIDTH - 2]);
	void SetColored(bool isColored) { m_IsColored = isColored; }
	void Draw();
	int GetBorderHight() { return BORDER_HIGHT; };
	int GetBorderWidth() { return BORDER_WIDTH; };
	enum Board_Place GetBoardPlace(CPoint& const point);
	bool GetBoardSymbol(CPoint& coord, char* symbol, CColorPoint::c_color* color);
	void UpdateworkBoard(int x, int y, char symbol);
	void operator=(const char board[][BORDER_WIDTH - 2])
	{
		for (int i = 1 , k = 0; i < BORDER_HIGHT - 1; k++, i++)
		{
			for (int j = 1, l = 0; j < BORDER_WIDTH -1;  l++ ,j++)
			{
				workBoard[i][j] = board[k][l];
				PrintBoard[k][l] = board[k][l];
			}
		}

	
	}
private:
	//void RestoreBoard
	void DrawOneChar(char ch);
	// creates an array that inicates for each floor where to create white spaces
	bool ValidatePoint(CPoint& const point);
	CColorPoint::c_color GetCharColor(char ch);

	char workBoard[BORDER_HIGHT][BORDER_WIDTH] = {};
	char PrintBoard[BORDER_HIGHT-2][BORDER_WIDTH-2] = {};
	bool m_IsColored = true;
};



