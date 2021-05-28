#include "LBiGame.h"
#define LCHILD
#include "LGame.cpp"
#undef LCHILD

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
	m->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		((c == L_COLOR_WHITE) ? n1 : n2)
	);

	m->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(m->playerWhite->getName() == n1) ? n2 : n1
	);
}

void LBiGame::actionAfterPath(LPath* path)
{
	m->areWhiteActive = !m->areWhiteActive;
}

int LBiGame::getTypeOfGame()
{
	return L_TYPE_BI;
}
