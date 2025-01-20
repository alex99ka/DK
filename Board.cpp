
#include "Board.h"
#include "ColorPoint.h"

void CBoard::Init(bool isColored, char board[][BORDER_WIDTH - 2])
{
	int i;
	m_IsColored = isColored;
	*this = board;
	// filling the workBoard with Q around it incase the 
	for (i = 0; i < BORDER_HIGHT; i++)
	{
		workBoard[i][0] = BOARDER_SYMB;
		workBoard[i][BORDER_WIDTH-1] = BOARDER_SYMB;
	}
	for ( i = 0; i < BORDER_WIDTH; i++)
	{
		workBoard[0][i] = BOARDER_SYMB;
		workBoard[BORDER_HIGHT - 1][i] = FLOOR_SYMB; // allows barrels to work properly 
	}

}

void CBoard::Draw() const
{

	if (m_IsColored)
	{
		for (int y = 0; y < BORDER_HIGHT - 2; y++)
		{ 
			for (int x = 0; x < BORDER_WIDTH - 2; x++)
			{
				DrawOneChar(PrintBoard[y][x]);
			}
			cout << y <<endl; //DEBUG
		}
	}
	else
	{
		for (int y = 0; y < BORDER_HIGHT - 2; y++)
		{
			for (int x = 0; x < BORDER_WIDTH - 2; x++)
			{
				cout << PrintBoard[y][x];
			}
			cout << y << endl; //DEBUG
		}
	}


}

void CBoard::DrawOneChar(char ch) const
{
	if (ch == BOARDER_SYMB)
		CColoredPrint::pr(ch, BoarderColor, CColoredPrint::c_decoration::BOLD);
	else if (ch == LADDER_SYMB)
		CColoredPrint::pr(ch, LadderColor, CColoredPrint::c_decoration::BOLD);
	else  if (ch == FLOOR_SYMB)
		CColoredPrint::pr(ch, FloorColor, CColoredPrint::c_decoration::BOLD);
	else  if (ch == MOVE_LEFT_SYMB || ch == MOVE_RIGHT_SYMB)
		CColoredPrint::pr(ch, ArrowColor, CColoredPrint::c_decoration::BOLD);
	else
		CColoredPrint::pr(ch);
}


bool CBoard::ValidatePoint(CPoint& const point) const
{
	if (point.GetX() >= 0 && point.GetX() < BORDER_WIDTH &&
		point.GetY() >= 0 && point.GetY() < BORDER_HIGHT)
		return true;

	return false;
}

enum CBoard::Board_Place CBoard::GetBoardPlace(CPoint& const point) const
{
	int y = point.GetY() + 1; // the one is there because workBoard is a bit bigger thus the offset
	int x = point.GetX() + 1;

	if (ValidatePoint(point) == false)
		return OUT_OB;
	if (workBoard[y][x] == LADDER_SYMB)
		return LADDER;
	if (workBoard[y][x] == BOARDER_SYMB)
		return BOARDER;
	if (workBoard[y][x] == FLOOR_SYMB)
		return FLOOR;
	if (workBoard[y][x] == MOVE_LEFT_SYMB)
		return ARROW_LEFT;
	if (workBoard[y][x] == MOVE_RIGHT_SYMB)
		return ARROW_RIGHT;

	return FREE;
}

CColorPoint::c_color CBoard::GetCharColor(char ch) const
{
	switch (ch)
	{
	case FLOOR_SYMB:
		return FloorColor;
	case BOARDER_SYMB:
		return  BoarderColor;
	case LADDER_SYMB:
		return LadderColor;
	case MOVE_RIGHT_SYMB:
	case MOVE_LEFT_SYMB:
		return ArrowColor;
	}
	return CColoredPrint::c_color::WHITE;
}

// a function that helps to reprint to the og board after somthing runs over it 
bool CBoard::GetBoardSymbol(CPoint& coord, char* symbol, CColorPoint::c_color* color) const
{
	if (ValidatePoint(coord) == false)
		return false;

	*symbol = PrintBoard[coord.GetY()][coord.GetX()];
	if (m_IsColored)
		*color = GetCharColor(*symbol);
	else
		*color = CColoredPrint::c_color::WHITE;
	return true;
}

