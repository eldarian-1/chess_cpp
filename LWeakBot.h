#pragma once

#include "LBotGame.h"

class LWeakBot :
	public LBotGame
{
protected:
	virtual LPath* calculateBestMove() override;

public:
	LWeakBot(int color) : LBotGame(color) {}


};
