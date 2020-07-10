#include "LBiGame.h"

#include "LConst.h"
#include "LPlayer.h"
#include "LSquare.h"

LBiGame::LBiGame(QString n1, QString n2, int c)
{
	this->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		(c == L_COLOR_ANY) ? ((rand() % 2) ? n1 : n2) : ((c == L_COLOR_WHITE) ? n1 : n2)
	);

	this->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(this->playerWhite->getName() == n1) ? n2 : n1
	);
}

void LBiGame::draw()
{
	LGame::draw();
}

void LBiGame::mousePress(int vertical, int horizontal)
{
	LGame::mousePress(vertical, horizontal);
}

void LBiGame::mouseRelease(int vertical, int horizontal)
{
	LGame::mouseRelease(vertical, horizontal);

	if (this->activeSquare)
	{
		this->activeSquare->setState(L_SQUARE_NATIVE);
		this->activeSquare = nullptr;
		this->activeFigure = nullptr;
	}
}

void LBiGame::mouseMotionMove(int vertical, int horizontal)
{
	LGame::mouseMotionMove(vertical, horizontal);
}

void LBiGame::mouseMove(int vertical, int horizontal)
{
	LGame::mouseMove(vertical, horizontal);
}

void LBiGame::actionAfterPath()
{
	this->areWhiteActive = !this->areWhiteActive;
}

void LBiGame::clear()
{
	LGame::clear();
}
