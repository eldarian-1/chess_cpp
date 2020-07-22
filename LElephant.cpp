#include "LElephant.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

#include "LPath.h"
#include "LSquare.h"

LElephant::LElephant(int color)
	: LFigure(color)
{
	
}

void LElephant::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawElephant(this->color, position, reverse);
}

int LElephant::isPossiblePath(LPath* path)
{
	LGame* game = LGame::getInstance();
	int flag = L_PATH_TRUE;

	int xC = path->getFrom()->getHorizontal();
	int yC = path->getFrom()->getVertical();
	int xT = path->getTo()->getHorizontal();
	int yT = path->getTo()->getVertical();

	LElephant* target = (LElephant*)game->getFigure(yT, xT);

	flag = ((target == nullptr) || (target->color != this->color)) && ((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT));

	if ((xC < xT) && (yC < yT))
	{
		for (int i = 1; i < (xT - xC) && flag != L_PATH_FALSE; i++)
			flag = (game->getFigure(yC + i, xC + i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
	}
	else if ((xC < xT) && (yC > yT))
	{
		for (int i = 1; i < (xT - xC) && flag != L_PATH_FALSE; i++)
			flag = (game->getFigure(yC - i, xC + i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
	}
	else if ((xC > xT) && (yC > yT))
	{
		for (int i = 1; i < (xC - xT) && flag != L_PATH_FALSE; i++)
			flag = (game->getFigure(yC - i, xC - i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
	}
	else if ((xC > xT) && (yC < yT))
	{
		for (int i = 1; i < (xC - xT) && flag != L_PATH_FALSE; i++)
			flag = (game->getFigure(yC + i, xC - i) == nullptr) ? (L_PATH_TRUE) : (L_PATH_FALSE);
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

int LElephant::getType() const
{
	return L_FIGURE_ELEPHANT;
}

int LElephant::getValue() const
{
	return L_VALUE_ELEPHANT;
}

QString LElephant::getName() const
{
	return "Elephant";
}
