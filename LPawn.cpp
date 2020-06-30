#include "LPawn.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

LPawn::LPawn(int color)
	: LFigure(color)
{
	this->type = L_FIGURE_PAWN;
}

void LPawn::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawPawn(this->color, position, reverse);
}

bool LPawn::isPossiblePosition(LSquare* oldPosition, LSquare* newPosition)
{
	LGame* game = LGame::getInstance();
	bool flag = true;

	int xC = oldPosition->getHorizontal();
	int yC = oldPosition->getVertical();
	int xT = newPosition->getHorizontal();
	int yT = newPosition->getVertical();

	LPawn* target = (LPawn*)game->getFigure(yT, xT);

	if ((xC == xT) && (yC == 6) && (yT == 5 || yT == 4))
	{
		flag = ((yT == 5) && (!target)) || ((yT == 4) && (!target) && !(LPawn*)game->getFigure(5, xT));
	}
	else if (target && (target->color != this->color) && ((abs(xC - xT) == 1) && abs((yC - yT) == 1)))
	{
		flag = true;
	}
	else if (!target && (xC == xT) && (yC - yT == 1))
	{
		flag = true;
	}
	else
	{
		flag = false;
	}

	return flag;
}

QString LPawn::getName() const
{
	return "Pawn";
}
