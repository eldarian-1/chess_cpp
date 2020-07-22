#pragma once

#include "LFigure.h"

class LQueen final
	: public LFigure
{
public:
	LQueen(int color);

	void draw(LSquare* position, bool reverse) override;
	int isPossiblePath(LPath* path) override;

	virtual int getType() const override;
	virtual int getValue() const override;
	QString getName() const override;

};
