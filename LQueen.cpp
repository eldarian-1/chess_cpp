#include "LQueen.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

LQueen::LQueen(int color)
	: LFigure(color)
{
	this->type = L_FIGURE_QUEEN;
}

void LQueen::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawQueen(this->color, position, reverse);
}

bool LQueen::isPossiblePosition(LSquare* oldPosition, LSquare* newPosition)
{
	LGame* game = LGame::getInstance();
	bool flag = true;

	int xC = oldPosition->getHorizontal();
	int yC = oldPosition->getVertical();
	int xT = newPosition->getHorizontal();
	int yT = newPosition->getVertical();

	LQueen* target = (LQueen*)game->getFigure(yT, xT);

	flag = ((target == nullptr) || (target->color != this->color)) && (((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT)) || (xC == xT) || (yC == yT));

	if ((xC == xT) || (yC == yT))
	{
		if (xC < xT)
		{
			for (int i = xC + 1; i < xT && flag; i++)
				flag = game->getFigure(yC, i) == nullptr;
		}
		else if (xC > xT)
		{
			for (int i = xT + 1; i < xC && flag; i++)
				flag = game->getFigure(yC, i) == nullptr;
		}
		else if (yC < yT)
		{
			for (int i = yC + 1; i < yT && flag; i++)
				flag = game->getFigure(i, xC) == nullptr;
		}
		else if (yC > yT)
		{
			for (int i = yT + 1; i < yC && flag; i++)
				flag = game->getFigure(i, xC) == nullptr;
		}
	}
	else if ((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT))
	{
		if ((xC < xT) && (yC < yT))
		{
			for (int i = 1; i < (xT - xC) && flag; i++)
				flag = game->getFigure(yC + i, xC + i) == nullptr;
		}
		else if ((xC < xT) && (yC > yT))
		{
			for (int i = 1; i < (xT - xC) && flag; i++)
				flag = game->getFigure(yC - i, xC + i) == nullptr;
		}
		else if ((xC > xT) && (yC > yT))
		{
			for (int i = 1; i < (xC - xT) && flag; i++)
				flag = game->getFigure(yC - i, xC - i) == nullptr;
		}
		else if ((xC > xT) && (yC < yT))
		{
			for (int i = 1; i < (xC - xT) && flag; i++)
				flag = game->getFigure(yC + i, xC - i) == nullptr;
		}
	}

	return flag;
}

QString LQueen::getName() const
{
	return "Queen";
}
