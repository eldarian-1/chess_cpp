#pragma once

#include "LGame.h"

class LFigure;

class LNetGame :
	public LGame
{
private:
	bool isBlocked;

	void waitNet();

public:
	LNetGame(int color);

	void draw() override;

	virtual void mousePress(int vertical, int horizontal) override;
	virtual void mouseRelease(int vertical, int horizontal) override;
	virtual void mouseMotionMove(int vertical, int horizontal) override;
	virtual void mouseMove(int vertical, int horizontal) override;

	void actionAfterPath() override;

	void setBlocked(bool block);

	void clear() override;

};
