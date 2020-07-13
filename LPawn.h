#pragma once

#include "LFigure.h"

class LPawn final
	: public LFigure
{
public:
	LPawn(int color);

	void draw(LSquare* position, bool reverse) override;
	int isPossiblePath(LPath* path) override;

	virtual int getValue() const override;
	QString getName() const override;

};
