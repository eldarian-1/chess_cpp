#include "LBotGame.h"

#include "LFigure.h"
#include "LPlayer.h"
#include "LOptions.h"

LBotGame::LBotGame(int c)
{
	QString n1 = LOptions::getInstance()->getName();
	QString n2 = "Computer";

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

void LBotGame::draw()
{
	LGame::draw();
}

void LBotGame::mousePress(int vertical, int horizontal)
{
	LGame::mousePress(vertical, horizontal);
}

void LBotGame::mouseRelease(int vertical, int horizontal)
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

void LBotGame::mouseMotionMove(int vertical, int horizontal)
{
	LGame::mouseMotionMove(vertical, horizontal);
}

void LBotGame::mouseMove(int vertical, int horizontal)
{
	LGame::mouseMove(vertical, horizontal);
}

void LBotGame::actionAfterPath()
{
	this->setBlocked(true);
	this->waitBot();
	this->setBlocked(false);
}

void LBotGame::setBlocked(bool block)
{
	this->isBlocked = block;
}

void LBotGame::waitBot()
{

}

void LBotGame::clear()
{
	LGame::clear();
}
