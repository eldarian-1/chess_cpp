#pragma once

#include "LGame.h"

#include <QString>

class LPlayer;
class LSquare;
class LFigure;

class LBiGame :
	public LGame
{
private:
	LPlayer* playerWhite;
	LPlayer* playerBlack;

	LSquare*** squares;
	LFigure*** figures;
	bool areWhiteActive;
	int _isShah;

	LSquare* activeSquare;
	LFigure* activeFigure;
	LSquare* focusedSquare;

public:
	LBiGame(QString name1, QString name2, int color);

	LFigure* getFigure(int vertical, int horizontal) override;
	void draw() override;

	int isShah(int color) override;
	int isShah(int color, int v, int h, int vK = -1, int hK = -1) override;

	void mousePress(int vertical, int horizontal) override;
	void mouseRelease(int vertical, int horizontal) override;
	void mouseMotionMove(int vertical, int horizontal) override;
	void mouseMove(int vertical, int horizontal) override;

	void setFigure(int vertical, int horizontal, LFigure* figure);

	void checked() override;
	void unchecked() override;

	void clear() override;

};
