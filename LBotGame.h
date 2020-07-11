#pragma once

#include "LGame.h"

template<class T>
class QVector;

class LFigure;

struct LPath;

class LBotGame :
	public LGame
{
private:
	bool isBlocked;

	int myColor;

	void waitBot();

	QVector<LPath> uglyMoves();
	LPath calculateBestMove();
	void completeMove();
	void completeMove(LPath path);

public:
	LBotGame(int color);

	void draw() override;

	virtual void mousePress(int vertical, int horizontal) override;
	virtual void mouseRelease(int vertical, int horizontal) override;
	virtual void mouseMotionMove(int vertical, int horizontal) override;
	virtual void mouseMove(int vertical, int horizontal) override;

	void actionAfterPath() override;

	void setBlocked(bool block);

	void clear() override;

};

struct LPath
{
	LSquare* from;
	LSquare* to;
	int result;
};
