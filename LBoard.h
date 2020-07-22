#pragma once

#include <QTextStream>

class LPath;
class LSquare;
class LFigure;

class LBoard
{
private:
	LSquare*** squares;
	LFigure*** figures;

public:
	LBoard();
	LBoard(const LBoard& board);
	~LBoard();

	LBoard* getClone();

	LSquare*& getSquare(int v, int h) const;
	LFigure*& getFigure(int v, int h) const;

	void setFigures();
	void setFigure(LFigure* figure, int v, int h);

	void completePath(LPath* path);

	friend QTextStream& operator >> (QTextStream& out, LBoard& board);
	friend QTextStream& operator << (QTextStream& in, const LBoard& board);

};
