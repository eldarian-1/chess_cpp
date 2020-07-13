#pragma once

class LSquare;
class LFigure;

class LBoard
{
private:
	LSquare*** squares;
	LFigure*** figures;

public:
	LBoard();
	LBoard(const LBoard* board);
	~LBoard();

	LBoard* getClone();

	LSquare*& getSquare(int v, int h) const;
	LFigure*& getFigure(int v, int h) const;

	void setFigure(LFigure* figure, int v, int h);

};
