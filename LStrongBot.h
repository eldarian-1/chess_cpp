#pragma once

#include "LBotGame.h"

class LStrongBot :
	public LBotGame
{
public:
	LStrongBot(int color) : LBotGame(color) {}

protected:
	virtual LPath* calculateBestMove() override;


};
