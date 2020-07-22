#pragma once

#include "LBotGame.h"

#include "LConst.h"

class LBotTree;

class LWeakBot :
	public LBotGame
{
private:
	static LBotTree* botTree;

public:
	LWeakBot() : LBotGame() {}
	LWeakBot(int color) : LBotGame(color) {}

protected:
	static void clearTree();

	virtual LPath* calculateBestMove() override;

	void minimax(LBotTree* botTree = nullptr, int depth = L_DEPTH_WEAK, bool itsMe = false);

	virtual int getTypeOfBot() override;

};
