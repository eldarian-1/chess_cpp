#pragma once

#include "LFigure.h"

class LKing final
	: public LFigure
{
private:
	bool _isCastled;

public:
	LKing(int color);

	void draw(LSquare* position, bool reverse) override;
	int isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;
	QString getName() const override;

};
