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
	bool isBlocked;

	int myColor;

	void waitBot();

	QVector<LPath*> uglyMoves();
	LPath* calculateBestMove();
	void completeMove();

public:
	LBotGame(int color);

	void actionAfterPath() override;

	void setBlocked(bool block);

};
