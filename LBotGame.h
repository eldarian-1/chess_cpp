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
	LPlayer* me;
	LPlayer* bot;

	bool isBlocked;

	void waitBot();

protected:
	virtual QVector<LPath*> uglyMoves(bool itsMe = false, LBoard* board = nullptr) final;
	virtual LPath* calculateBestMove() = 0;

public:
	LBotGame(int color);
	~LBotGame();

	virtual void actionAfterPath(LPath* path) override;

	void setBlocked(bool block);

	virtual int getFigureTransformation() override;

	virtual void clear() override;
};
