#pragma once

#include "LGame.h"

template<class T>
class QVector;

class LPath;
class LFigure;

class LBotGame :
	public LGame
{
private:
	friend class LSaveKeeper;

	LPlayer* me;
	LPlayer* bot;

	bool isBlocked;

	void waitBot();

protected:
	virtual QVector<LPath*> uglyMoves(bool itsMe = false, LBoard* board = nullptr) final;
	virtual LPath* calculateBestMove() = 0;

public:
	LBotGame();
	LBotGame(int color);
	~LBotGame();

	static LBotGame* newGame(int botPower);
	static LBotGame* newGame(int botPower, int color);

	virtual void actionAfterPath(LPath* path) override;

	void setBlocked(bool block);

	virtual int getFigureTransformation() override;

	virtual int getTypeOfGame() override final;
	virtual int getTypeOfBot() = 0;

	virtual void clear() override;
};
