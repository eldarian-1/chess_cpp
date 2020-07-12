#include "LNetGame.h"

#include "LConst.h"
#include "LFigure.h"
#include "LSquare.h"
#include "LPlayer.h"
#include "LOptions.h"

LNetGame::LNetGame(int c)
{
	QString n1 = LOptions::getInstance()->getName();
	QString n2 = "Internet player";

	this->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		(c == L_COLOR_ANY) ? ((rand() % 2) ? n1 : n2) : ((c == L_COLOR_WHITE) ? n1 : n2)
	);

	this->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(this->playerWhite->getName() == n1) ? n2 : n1
	);

	this->areWhiteActive = this->playerWhite->getName() == n1;
	this->isBlocked = !this->areWhiteActive;
}

void LNetGame::actionAfterPath()
{
	this->setBlocked(true);
	this->waitNet();
	this->setBlocked(false);
}

void LNetGame::setBlocked(bool block)
{
	this->isBlocked = block;
}

void LNetGame::waitNet()
{
	
}
