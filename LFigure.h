#pragma once

class QString;

class LPath;
class LSquare;

class LFigure
{
protected:
	int color;
	int type;

	LFigure(int color);

public:
	virtual void draw(LSquare* position, bool reverse) = 0;
	virtual int isPossiblePath(LPath* path) = 0;

	int getColor() const;
	int getType() const;

	virtual int getValue() const = 0;
	virtual QString getName() const = 0;

};
