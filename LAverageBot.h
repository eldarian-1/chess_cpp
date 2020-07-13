#pragma once

#include "LBotGame.h"

class LAverageBot :
	public LBotGame
{
public:
	LAverageBot(int color) : LBotGame(color) {}

protected:
	virtual LPath* calculateBestMove() override;


};
