#include "LFigure.h"

LFigure::LFigure(int c)
	:
	color(c)
{

}

int LFigure::getColor() const
{
	return this->color;
}

int LFigure::getType() const
{
	return this->type;
}
