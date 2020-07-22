#pragma once

#include "LFigure.h"

class LHorse final
	: public LFigure
{
public:
	LHorse(int color);

	void draw(LSquare* position, bool reverse) override;
	int isPossiblePath(LPath* path) override;

	virtual int getType() const override;
	virtual int getValue() const override;
	QString getName() const override;

};
