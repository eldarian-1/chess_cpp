#include "LRook.h"

#include "LDesk.h"
//#include "LChessBoard.h"
#include "LGame.h"
#include "LConst.h"

LRook::LRook(int color)
	:
	LFigure(color),
	isWalked(false)
{
	this->type = L_FIGURE_ROOK;
}

void LRook::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawRook(this->color, position, reverse);
}

bool LRook::isPossiblePosition(LSquare* oldPosition, LSquare* newPosition)
{
	//LChessBoard* board = LChessBoard::getInstance();
	bool flag = true;

	int xC = oldPosition->getHorizontal();
	int yC = oldPosition->getVertical();
	int xT = newPosition->getHorizontal();
	int yT = newPosition->getVertical();

	/*LRook* target = (LRook*)board->getFigure(yT, xT);

	flag = ((target == nullptr) || (target->color != this->color)) && ((xC == xT) || (yC == yT));

	if (xC < xT)
	{
		for (int i = xC + 1; i < xT && flag; i++)
			flag = board->getFigure(yC, i) == nullptr;
	}
	else if (xC > xT)
	{
		for (int i = xT + 1; i < xC && flag; i++)
			flag = board->getFigure(yC, i) == nullptr;
	}
	else if (yC < yT)
	{
		for (int i = yC + 1; i < yT && flag; i++)
			flag = board->getFigure(i, xC) == nullptr;
	}
	else if (yC > yT)
	{
		for (int i = yT + 1; i < yC && flag; i++)
			flag = board->getFigure(i, xC) == nullptr;
	}*/

	return flag;
}
