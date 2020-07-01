#pragma once

#include "LSquare.h"

class QString;

class LFigure
{
protected:
	int color;
	int type;

	LFigure(int color);

public:
	virtual void draw(LSquare* position, bool reverse) = 0;
	virtual int isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) = 0;

	int getColor() const;
	int getType() const;
	virtual QString getName() const = 0;

};
