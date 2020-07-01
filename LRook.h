#pragma once

#include "LFigure.h"

class LRook final
	: public LFigure
{
private:
	bool _isWalked;

public:
	LRook(int color);

	void draw(LSquare* position, bool reverse) override;
	int isPossiblePosition(LSquare* oldPosition, LSquare* newPosition) override;
	QString getName() const override;
	bool isWalked() const;

};
