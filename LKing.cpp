#include "LKing.h"

#include "LDesk.h"
//#include "LChessBoard.h"
#include "LGame.h"
#include "LConst.h"

LKing::LKing(int color)
	:
	LFigure(color),
	isWalked(false)
{
	this->type = L_FIGURE_KING;
}

void LKing::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawKing(this->color, position, reverse);
}

bool LKing::isPossiblePosition(LSquare* oldPosition, LSquare* newPosition)
{
	//LChessBoard* board = LChessBoard::getInstance();
	bool flag = true;

	int xC = oldPosition->getHorizontal();
	int yC = oldPosition->getVertical();
	int xT = newPosition->getHorizontal();
	int yT = newPosition->getVertical();

	/*LKing* target = (LKing*)board->getFigure(yT, xT);

	flag = ((target == nullptr) || (target->color != this->color)) && (((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT)) || (xC == xT) || (yC == yT));

	if ((xC == xT) || (yC == yT))
	{
		if ((xC < xT) && (xT - xC == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yC, xT);
			flag = temp == nullptr || temp->color != this->color;
		}
		else if ((xC > xT) && (xC - xT == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yC, xT);
			flag = temp == nullptr || temp->color != this->color;
		}
		else if ((yC < yT) && (yT - yC == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yT, xC);
			flag = temp == nullptr || temp->color != this->color;
		}
		else if ((yC > yT) && (yC - yT == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yT, xC);
			flag = temp == nullptr || temp->color != this->color;
		}
		else
		{
			flag = false;
		}
	}
	else if ((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT))
	{
		if ((xC < xT) && (yC < yT) && (xT - xC == 1) && (yT - yC == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yC + 1, xC + 1);
			flag = temp == nullptr || temp->color != this->color;
		}
		else if ((xC < xT) && (yC > yT) && (xT - xC == 1) && (yC - yT == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yC - 1, xC + 1);
			flag = temp == nullptr || temp->color != this->color;
		}
		else if ((xC > xT) && (yC > yT) && (xC - xT == 1) && (yC - yT == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yC - 1, xC - 1);
			flag = temp == nullptr || temp->color != this->color;
		}
		else if ((xC > xT) && (yC < yT) && (yT - yC == 1) && (xC - xT == 1))
		{
			LKing* temp = (LKing*)board->getFigure(yC + 1, xC - 1);
			flag = temp == nullptr || temp->color != this->color;
		}
		else
		{
			flag = false;
		}
	}*/

	return flag;
}
