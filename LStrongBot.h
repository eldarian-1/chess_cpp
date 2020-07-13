#pragma once

#include "LBotGame.h"

class LStrongBot :
	public LBotGame
{
protected:
	virtual LPath* calculateBestMove() override;

public:
	LStrongBot(int color) : LBotGame(color) {}


};
