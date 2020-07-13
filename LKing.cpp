#include "LKing.h"

#include "LDesk.h"
#include "LGame.h"
#include "LConst.h"
#include "LRook.h"

#include "LPath.h"
#include "LSquare.h"

LKing::LKing(int color)
	:
	LFigure(color),
	_isCastled(false)
{
	this->type = L_FIGURE_KING;
}

void LKing::draw(LSquare* position, bool reverse)
{
	LDesk::getInstance()->drawKing(this->color, position, reverse);
}

int LKing::isPossiblePath(LPath* path)
{
	LGame* game = LGame::getInstance();
	int flag = L_PATH_TRUE;

	int xC = path->getFrom()->getHorizontal();
	int yC = path->getFrom()->getVertical();
	int xT = path->getTo()->getHorizontal();
	int yT = path->getTo()->getVertical();

	LKing* target = (LKing*)game->getFigure(yT, xT);

	if (!this->_isCastled && yC == yT)
	{
		if (xT - xC == 2 && !game->getFigure(yC, xC + 1) && !game->getFigure(yC, xC + 2)
			&& (!game->getFigure(yC, xC + 3) || (game->getFigure(yC, xC + 3)->getType() == L_FIGURE_ROOK && !((LRook*)game->getFigure(yC, xC + 3))->isWalked()))
			&& (!game->getFigure(yC, xC + 4) || (game->getFigure(yC, xC + 4)->getType() == L_FIGURE_ROOK && !((LRook*)game->getFigure(yC, xC + 4))->isWalked())))
		{
			return L_PATH_TRUE | L_PATH_CASTLING;
		}
		else if (xC - xT == 2 && !game->getFigure(yC, xC - 1) && !game->getFigure(yC, xC - 2)
			&& (!game->getFigure(yC, xC - 3) || (game->getFigure(yC, xC - 3)->getType() == L_FIGURE_ROOK && !((LRook*)game->getFigure(yC, xC - 3))->isWalked()))
			&& (!game->getFigure(yC, xC - 4) || (game->getFigure(yC, xC - 4)->getType() == L_FIGURE_ROOK && !((LRook*)game->getFigure(yC, xC - 4))->isWalked())))
		{
			return L_PATH_TRUE | L_PATH_CASTLING;
		}
	}

	flag = (((target == nullptr) || (target->color != this->color)) && (((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT)) || (xC == xT) || (yC == yT)))
		? (L_PATH_TRUE) : (L_PATH_FALSE);

	if ((xC == xT) || (yC == yT))
	{
		if ((xC < xT) && (xT - xC == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yC, xT);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC > xT) && (xC - xT == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yC, xT);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((yC < yT) && (yT - yC == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yT, xC);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((yC > yT) && (yC - yT == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yT, xC);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else
		{
			flag = L_PATH_FALSE;
		}
	}
	else if ((xC - yC) == (xT - yT) || (xC + yC) == (xT + yT))
	{
		if ((xC < xT) && (yC < yT) && (xT - xC == 1) && (yT - yC == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yC + 1, xC + 1);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC < xT) && (yC > yT) && (xT - xC == 1) && (yC - yT == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yC - 1, xC + 1);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC > xT) && (yC > yT) && (xC - xT == 1) && (yC - yT == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yC - 1, xC - 1);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else if ((xC > xT) && (yC < yT) && (yT - yC == 1) && (xC - xT == 1))
		{
			LKing* temp = (LKing*)game->getFigure(yC + 1, xC - 1);
			flag = (temp == nullptr || temp->color != this->color) ? (L_PATH_TRUE) : (L_PATH_FALSE);
		}
		else
		{
			flag = L_PATH_FALSE;
		}
	}

	if (!(flag & L_PATH_FALSE) && !this->_isCastled)
		this->_isCastled = true;

	if ((flag & L_PATH_TRUE) && (game->isCheck(this->getColor(), yT, xT, yC, xC) & L_PATH_CHECK))
		flag = L_PATH_FALSE;

	return flag;
}

int LKing::getValue() const
{
	return L_VALUE_KING;
}

QString LKing::getName() const
{
	return "King";
}
