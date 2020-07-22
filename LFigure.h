#pragma once

class QString;

class LPath;
class LSquare;

class LFigure
{
protected:
	int color;
	LFigure(int color);

public:
	static LFigure* create(int type, int color);

	virtual void draw(LSquare* position, bool reverse) = 0;
	virtual int isPossiblePath(LPath* path) = 0;

	virtual int getColor() const final;
	virtual int getType() const = 0;

	virtual int getValue() const = 0;
	virtual QString getName() const = 0;

};
