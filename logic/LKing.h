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
	int isPossiblePath(LPath* path) override;

	virtual int getType() const override;
	virtual int getValue() const override;
	virtual QString getName() const override;

	bool isCastled() const;
	void setCastled(bool isCastled);

};
