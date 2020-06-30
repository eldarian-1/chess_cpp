#include "LHorse.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

LHorse::LHorse(int color)
	: LFigure(color)
{
	this->type = L_FIGURE_HORSE;
}

void LHorse::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawHorse(this->color, position, reverse);
}

bool LHorse::isPossiblePosition(LSquare* oldPosition, LSquare* newPosition)
{
	LGame* game = LGame::getInstance();
	bool flag = true;

	int xC = oldPosition->getHorizontal();
	int yC = oldPosition->getVertical();
	int xT = newPosition->getHorizontal();
	int yT = newPosition->getVertical();

	LHorse* target = (LHorse*)game->getFigure(yT, xT);

	flag = ((target == nullptr) || (target->color != this->color)) && (((abs(xT - xC) == 2) && (abs(yT - yC) == 1)) || ((abs(xT - xC) == 1) && (abs(yT - yC)) == 2));

	return flag;
}

QString LHorse::getName() const
{
	return "Horse";
}
