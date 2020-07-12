#include "LHorse.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"

#include "LPath.h"
#include "LSquare.h"

LHorse::LHorse(int color)
	: LFigure(color)
{
	this->type = L_FIGURE_HORSE;
}

void LHorse::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawHorse(this->color, position, reverse);
}

int LHorse::isPossiblePath(LPath* path)
{
	LGame* game = LGame::getInstance();
	int flag = L_PATH_TRUE;

	int xC = path->getFrom()->getHorizontal();
	int yC = path->getFrom()->getVertical();
	int xT = path->getTo()->getHorizontal();
	int yT = path->getTo()->getVertical();

	LHorse* target = (LHorse*)game->getFigure(yT, xT);

	flag = (((target == nullptr) || (target->color != this->color)) && (((abs(xT - xC) == 2) && (abs(yT - yC) == 1)) || ((abs(xT - xC) == 1) && (abs(yT - yC)) == 2)))
		? (L_PATH_TRUE) : (L_PATH_FALSE);

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

QString LHorse::getName() const
{
	return "Horse";
}
