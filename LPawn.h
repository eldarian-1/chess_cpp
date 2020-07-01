#pragma once

#include "LFigure.h"

class LPawn final
	: public LFigure
{
public:
	LPawn(int color);

	void draw(LSquare* position, bool reverse) override;
	int isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;
	QString getName() const override;

};
