#pragma once

#include "LBotGame.h"

class LBeginBot :
	public LBotGame
{
protected:
	virtual LPath* calculateBestMove() override;

public:
	LBeginBot(int color) : LBotGame(color) {}


};
