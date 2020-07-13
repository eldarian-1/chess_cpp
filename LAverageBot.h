#pragma once

#include "LBotGame.h"

class LAverageBot :
	public LBotGame
{
protected:
	virtual LPath* calculateBestMove() override;

public:
	LAverageBot(int color) : LBotGame(color) {}


};
