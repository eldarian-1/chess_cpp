#pragma once

#include "LBotGame.h"

#include "LConst.h"

class LBotTree;

class LStrongBot :
	public LBotGame
{
private:
	static LBotTree* botTree;

public:
	LStrongBot() : LBotGame() {}
	LStrongBot(int color) : LBotGame(color) {}

protected:
	static void clearTree();

	virtual LPath* calculateBestMove() override;

	void minimax(LBotTree* botTree = nullptr, int depth = L_DEPTH_STRONG, bool itsMe = false);

	virtual int getTypeOfBot() override;

};
