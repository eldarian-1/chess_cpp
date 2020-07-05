#pragma once

#include "LGame.h"

class LFigure;

class LBotGame :
	public LGame
{
private:


public:
	LBotGame(int color);

	LFigure* getFigure(int vertical, int horizontal) override;
	void draw() override;

	int isShah(int color) override;
	int isShah(int color, int v, int h, int vK = -1, int hK = -1) override;

	void mousePress(int vertical, int horizontal) override;
	void mouseRelease(int vertical, int horizontal) override;
	void mouseMotionMove(int vertical, int horizontal) override;
	void mouseMove(int vertical, int horizontal) override;

	void checked() override;
	void unchecked() override;

	void clear() override;

};
