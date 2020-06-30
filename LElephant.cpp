#include "LElephant.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

LElephant::LElephant(int color)
	: LFigure(color)
{
	this->type = L_FIGURE_ELEPHANT;
}

void LElephant::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawElephant(this->color, position, reverse);
}

bool LElephant::isPossiblePosition(LSquare* oldPosition, LSquare* newPosition)
{
	LGame* game = LGame::getInstance();
	bool flag = true;

	int xC = oldPosition->getHorizontal();
	int yC = oldPosition->getVertical();
	int xT = newPosition->getHorizontal();
	int yT = newPosition->getVertical();

	LElephant* target = (LElephant*)game->getFigure(yT, xT);

	flag = ((target == nullptr) || (target->color != this->color)) && ((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT));

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

	return flag;
}

QString LElephant::getName() const
{
	return "Elephant";
}