#pragma once

#include "LSquare.h"
#include "LFigure.h"

class LChessBoard
{
private:
	static LChessBoard* instance;

	LSquare* activeSquare;
	LFigure* activeFigure;
	LSquare* focusedSquare;

	LSquare*** squares;
	LFigure*** figures;

protected:
	LChessBoard();

public:
	static LChessBoard* getInstance();

	static void swapFigurePlace(LSquare* oldPlace, LSquare* newPlace, int activePlayer, int passivePlayer);

	void setReverseOf(LChessBoard* board);

	LChessBoard* setFigure(int vertical, int horizontal, LFigure* figure);

	void draw();

	LSquare* getSquare(int vertical, int horizontal);
	LFigure* getFigure(int vertical, int horizontal);

	void getPlace(LSquare*& square, LFigure*& figure, int x, int y);
	bool isTakenPlace(int vertical, int horizontal);

	void mousePress(int v, int h);
	bool mouseRelease(int v, int h);
	void mouseMotionMove(int v, int h);
	void mouseMove(int v, int h);

};
