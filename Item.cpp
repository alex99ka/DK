#include "Item.h"

void CMovingItem::SetDirection(Directions direction)
{
	if (m_FallCounter > 0) // we don't change direction during falling the character
		return;
	m_direction = direction;
	switch (direction)
	{
	case STOP:
		m_Xdirection = 0;
		m_Ydirection = 0;
		break;
	case RIGHT:
		m_Xdirection = 1;
		m_Ydirection = 0;
		break;
	case LEFT:
		m_Xdirection = -1;
		m_Ydirection = 0;
		break;
	case UP:
		m_Ydirection = -2;
		break;
	case DOWN:
		m_Xdirection = 0;
		m_Ydirection = 1;
		break;
	}
}
