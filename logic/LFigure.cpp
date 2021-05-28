#include "LFigure.h"

#include "LConst.h"
#include "LKing.h"
#include "LQueen.h"
#include "LElephant.h"
#include "LHorse.h"
#include "LRook.h"
#include "LPawn.h"

LFigure::LFigure(int c)
	:
	color(c)
{

}

LFigure* LFigure::create(int type, int color)
{
	LFigure* figure;

	switch (type)
	{

	case L_FIGURE_KING:
		figure = new LKing(color);
		break;

	case L_FIGURE_QUEEN:
		figure = new LQueen(color);
		break;

	case L_FIGURE_ELEPHANT:
		figure = new LElephant(color);
		break;

	case L_FIGURE_HORSE:
		figure = new LHorse(color);
		break;

	case L_FIGURE_ROOK:
		figure = new LRook(color);
		break;

	case L_FIGURE_PAWN:
		figure = new LPawn(color);
		break;

	}

	return figure;
}

int LFigure::getColor() const
{
	return this->color;
}
