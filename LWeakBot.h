#pragma once

#include "LBotGame.h"

class LWeakBot :
	public LBotGame
{
public:
	LWeakBot(int color) : LBotGame(color) {}

protected:
	virtual LPath* calculateBestMove() override;


};
