#pragma once

#include "LFigure.h"

class LRook final
	: public LFigure
{
private:
	bool isWalked;

public:
	LRook(int color);

	void draw(LSquare* position, bool reverse) override;
	bool isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;

};
