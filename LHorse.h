#pragma once

#include "LFigure.h"

class LHorse final
	: public LFigure
{
public:
	LHorse(int color);

	void draw(LSquare* position, bool reverse) override;
	bool isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;

};
