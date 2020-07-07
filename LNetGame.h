#pragma once

#include "LGame.h"

class LFigure;

class LNetGame :
	public LGame
{
private:


public:
	LNetGame(int color);

	LFigure* getFigure(int vertical, int horizontal) override;
	void draw() override;

	int isCheck(int color) override;
	int isCheck(int color, int v, int h, int vK = -1, int hK = -1) override;
	int getIsCheck() const override;

	//int isMat(int color) override;

	void mousePress(int vertical, int horizontal) override;
	void mouseRelease(int vertical, int horizontal) override;
	void mouseMotionMove(int vertical, int horizontal) override;
	void mouseMove(int vertical, int horizontal) override;

	void checked() override;
	void unchecked() override;

	void clear() override;

};
