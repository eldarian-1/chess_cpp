#include "LSquare.h"

#include "LConst.h"
#include "LDesk.h"

LSquare::LSquare(int v, int h, int c)
	:
	vertical(v),
	horizontal(h),
	color(c),
	state(L_SQUARE_NATIVE)
{

}

int LSquare::getVertical()
{
	return this->vertical;
}

int LSquare::getHorizontal()
{
	return this->horizontal;
}

int LSquare::getColor()
{
	return this->color;
}

int LSquare::getState()
{
	return this->state;
}

void LSquare::setState(int state)
{
	this->state = state;
}

void LSquare::setPosition(int vertical, int horizontal)
{
	this->vertical = vertical;
	this->horizontal = horizontal;
}

void LSquare::draw(bool reverse)
{
	LDesk::getInstance()->drawSquare(this, reverse);
}
