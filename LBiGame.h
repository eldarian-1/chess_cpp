#pragma once

#include "LGame.h"

#include <QString>

class LSquare;
class LFigure;

class LBiGame :
	public LGame
{
private:
	QString name1, name2;
	int color1, color2;
	LSquare*** squares;
	LFigure*** figures;
	bool isActive1;

	LSquare* activeSquare;
	LFigure* activeFigure;
	LSquare* focusedSquare;

public:
	LBiGame(QString name1, QString name2, int color);

	LFigure* getFigure(int vertical, int horizontal) override;
	void draw() override;

	void mousePress(int vertical, int horizontal) override;
	void mouseRelease(int vertical, int horizontal) override;
	void mouseMotionMove(int vertical, int horizontal) override;
	void mouseMove(int vertical, int horizontal) override;

	void setFigure(int vertical, int horizontal, LFigure* figure);

	void checked() override;
	void unchecked() override;

	void clear() override;

};
