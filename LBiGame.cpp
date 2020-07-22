#include "LBiGame.h"

#include "LConst.h"
#include "LPlayer.h"
#include "LSquare.h"

LBiGame::LBiGame()
	:
	LGame()
{

}

LBiGame::LBiGame(QString n1, QString n2, int c)
	:
	LGame()
{
	this->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		((c == L_COLOR_WHITE) ? n1 : n2)
	);

	this->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(this->playerWhite->getName() == n1) ? n2 : n1
	);
}

void LBiGame::actionAfterPath(LPath* path)
{
	this->areWhiteActive = !this->areWhiteActive;
}

int LBiGame::getTypeOfGame()
{
	return L_TYPE_BI;
}
