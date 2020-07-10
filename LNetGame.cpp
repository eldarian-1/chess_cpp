#include "LNetGame.h"

#include "LFigure.h"
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

void LNetGame::draw()
{
	LGame::draw();
}

void LNetGame::mousePress(int vertical, int horizontal)
{
	LGame::mousePress(vertical, horizontal);
}

void LNetGame::mouseRelease(int vertical, int horizontal)
{
	if (!this->isBlocked)
	{
		LGame::mouseRelease(vertical, horizontal);
	}

	if (this->activeSquare)
	{
		this->activeSquare->setState(L_SQUARE_NATIVE);
		this->activeSquare = nullptr;
		this->activeFigure = nullptr;
	}
}

void LNetGame::mouseMotionMove(int vertical, int horizontal)
{
	LGame::mouseMotionMove(vertical, horizontal);
}

void LNetGame::mouseMove(int vertical, int horizontal)
{
	LGame::mouseMove(vertical, horizontal);
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

void LNetGame::clear()
{
	LGame::clear();
}
