#pragma once

#include "LFigure.h"

class LPawn final
	: public LFigure
{
public:
	LPawn(int color);

	void draw(LSquare* position, bool reverse) override;
	bool isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;

};
