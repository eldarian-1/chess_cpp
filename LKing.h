#pragma once

#include "LFigure.h"

class LKing final
	: public LFigure
{
private:
	bool isWalked;

public:
	LKing(int color);

	void draw(LSquare* position, bool reverse) override;
	bool isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;

};
