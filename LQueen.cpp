#include "LQueen.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

#include "LPath.h"
#include "LSquare.h"

LQueen::LQueen(int color)
	: LFigure(color)
{
	this->type = L_FIGURE_QUEEN;
}

void LQueen::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawQueen(this->color, position, reverse);
}

int LQueen::isPossiblePath(LPath* path)
{
	LGame* game = LGame::getInstance();
	int flag = L_PATH_TRUE;

	int xC = path->getFrom()->getHorizontal();
	int yC = path->getFrom()->getVertical();
	int xT = path->getTo()->getHorizontal();
	int yT = path->getTo()->getVertical();

	LQueen* target = (LQueen*)game->getFigure(yT, xT);

	flag = (((target == nullptr) || (target->color != this->color)) && (((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT)) || (xC == xT) || (yC == yT)))
		? (L_PATH_TRUE) : (L_PATH_FALSE);

	if ((xC == xT) || (yC == yT))
	{
		if (xC < xT)
		{
			for (int i = xC + 1; i < xT && flag; i++)
				flag = (game->getFigure(yC, i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if (xC > xT)
		{
			for (int i = xT + 1; i < xC && flag; i++)
				flag = (game->getFigure(yC, i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if (yC < yT)
		{
			for (int i = yC + 1; i < yT && flag; i++)
				flag = (game->getFigure(i, xC) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if (yC > yT)
		{
			for (int i = yT + 1; i < yC && flag; i++)
				flag = (game->getFigure(i, xC) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
	}
	else if ((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT))
	{
		if ((xC < xT) && (yC < yT))
		{
			for (int i = 1; i < (xT - xC) && flag; i++)
				flag = (game->getFigure(yC + i, xC + i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC < xT) && (yC > yT))
		{
			for (int i = 1; i < (xT - xC) && flag; i++)
				flag = (game->getFigure(yC - i, xC + i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC > xT) && (yC > yT))
		{
			for (int i = 1; i < (xC - xT) && flag; i++)
				flag = (game->getFigure(yC - i, xC - i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC > xT) && (yC < yT))
		{
			for (int i = 1; i < (xC - xT) && flag; i++)
				flag = (game->getFigure(yC + i, xC - i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
	}

	if (game->getIsCheck() & this->color)
	{
		if ((flag & L_PATH_TRUE) && (game->isCheck(this->getColor(), yT, xT, yC, xC) & L_PATH_CHECK))
			flag = L_PATH_FALSE;
	}
	else
	{
		if ((flag & L_PATH_TRUE) && (game->isCheck(this->getColor(), yC, xC) & L_PATH_CHECK))
			flag = L_PATH_FALSE;
	}

	return flag;
}

QString LQueen::getName() const
{
	return "Queen";
}
