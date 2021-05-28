#pragma once

#include "LBotGame.h"

#include "LConst.h"

class LBotTree;

class LAverageBot :
	public LBotGame
{
private:
	static LBotTree* botTree;

public:
	LAverageBot() : LBotGame() {}
	LAverageBot(int color) : LBotGame(color) {}

protected:
	static void clearTree();

	virtual LPath* calculateBestMove() override;

	void minimax(LBotTree* botTree = nullptr, int depth = L_DEPTH_AVERAGE, bool itsMe = false);

	virtual int getTypeOfBot() override;

};
