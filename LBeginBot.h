#pragma once

#include "LBotGame.h"

class LBeginBot :
	public LBotGame
{
public:
	LBeginBot(int color) : LBotGame(color) {}

protected:
	virtual LPath* calculateBestMove() override;


};
