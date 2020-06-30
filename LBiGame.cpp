#include "LBiGame.h"

#include <QString>

#include "LConst.h"
#include "LMainWidget.h"
#include "LDesk.h"
#include "LSquare.h"

#include "LFigure.h"
#include "LKing.h"
#include "LQueen.h"
#include "LElephant.h"
#include "LHorse.h"
#include "LRook.h"
#include "LPawn.h"

LBiGame::LBiGame(QString n1, QString n2, int c)
	:
	name1(n1),
	name2(n2),
	color1((c == L_COLOR_ANY)?(rand()%2+L_COLOR_WHITE):(c)),
	color2((color1 == L_COLOR_WHITE)?(L_COLOR_BLACK):(L_COLOR_WHITE)),
	isActive1(color1 == L_COLOR_WHITE),
	squares(new LSquare**[L_CHESS_BOARD_SIZE]),
	figures(new LFigure**[L_CHESS_BOARD_SIZE]),
	activeSquare(nullptr),
	activeFigure(nullptr),
	focusedSquare(nullptr)
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		this->squares[i] = new LSquare * [L_CHESS_BOARD_SIZE];
		this->figures[i] = new LFigure * [L_CHESS_BOARD_SIZE];
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			int color = (i + j + color1 % 2) % 2 + L_COLOR_WHITE;
			this->squares[i][j] = new LSquare(i, j, color);
			this->figures[i][j] = nullptr;
		}
	}

	int xKing = isActive1 ? 4 : 3;
	int xQueen = isActive1 ? 3 : 4;

	int color1 = isActive1 ? this->color1 : this->color2;
	int color2 = isActive1 ? this->color2 : this->color1;

	this->setFigure(0, xKing, new LKing(color2));
	this->setFigure(0, xQueen, new LQueen(color2));
	this->setFigure(0, 2, new LElephant(color2));
	this->setFigure(0, 5, new LElephant(color2));
	this->setFigure(0, 1, new LHorse(color2));
	this->setFigure(0, 6, new LHorse(color2));
	this->setFigure(0, 0, new LRook(color2));
	this->setFigure(0, 7, new LRook(color2));
	this->setFigure(1, 0, new LPawn(color2));
	this->setFigure(1, 1, new LPawn(color2));
	this->setFigure(1, 2, new LPawn(color2));
	this->setFigure(1, 3, new LPawn(color2));
	this->setFigure(1, 4, new LPawn(color2));
	this->setFigure(1, 5, new LPawn(color2));
	this->setFigure(1, 6, new LPawn(color2));
	this->setFigure(1, 7, new LPawn(color2));

	this->setFigure(7, xKing, new LKing(color1));
	this->setFigure(7, xQueen, new LQueen(color1));
	this->setFigure(7, 2, new LElephant(color1));
	this->setFigure(7, 5, new LElephant(color1));
	this->setFigure(7, 1, new LHorse(color1));
	this->setFigure(7, 6, new LHorse(color1));
	this->setFigure(7, 0, new LRook(color1));
	this->setFigure(7, 7, new LRook(color1));
	this->setFigure(6, 0, new LPawn(color1));
	this->setFigure(6, 1, new LPawn(color1));
	this->setFigure(6, 2, new LPawn(color1));
	this->setFigure(6, 3, new LPawn(color1));
	this->setFigure(6, 4, new LPawn(color1));
	this->setFigure(6, 5, new LPawn(color1));
	this->setFigure(6, 6, new LPawn(color1));
	this->setFigure(6, 7, new LPawn(color1));
}

LFigure* LBiGame::getFigure(int v, int h)
{
	return this->figures[v][h];
}

void LBiGame::draw()
{
	LDesk* desk = LDesk::getInstance();

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j]->draw(!this->isActive1);
		}
	}

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (this->figures[i][j])
			{
				this->figures[i][j]->draw(this->squares[i][j], !this->isActive1);
			}
		}
	}
}

void LBiGame::mousePress(int v, int h)
{
	this->activeSquare = this->squares[v][h];
	this->activeFigure = this->figures[v][h];
	this->focusedSquare = this->squares[v][h];
}

void LBiGame::mouseRelease(int v, int h)
{
	if (this->activeFigure && this->activeFigure->isPossiblePosition(activeSquare, this->squares[v][h]))
	{
		QString name = (this->isActive1) ? (this->name1) : (this->name2);
		QString actFig = this->activeFigure->getName();
		QString pasFig = (this->figures[v][h]) ? (" (" + this->figures[v][h]->getName() + ")") : ("");
		this->figures[v][h] = this->activeFigure;
		this->figures[this->activeSquare->getVertical()][this->activeSquare->getHorizontal()] = nullptr;
		QString node = name + ": " + actFig + " " +
			('A' + activeSquare->getHorizontal()) + ('1' + activeSquare->getVertical()) + " - " +
			('A' + this->squares[v][h]->getHorizontal()) + ('1' + this->squares[v][h]->getVertical()) + pasFig;
		LMainWidget::getInstance()->pathListAppend(node);
		this->isActive1 = !this->isActive1;
	}
	this->activeSquare = nullptr;
	this->activeFigure = nullptr;
}

void LBiGame::mouseMotionMove(int v, int h)
{
	//this->focusedSquare = this->squares[v][h];
}

void LBiGame::mouseMove(int v, int h)
{
	this->focusedSquare = this->squares[v][h];
}

void LBiGame::setFigure(int v, int h, LFigure* figure)
{
	this->figures[v][h] = figure;
}

void LBiGame::checked()
{

}

void LBiGame::unchecked()
{

}

void LBiGame::clear()
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			delete this->squares[i][j];
			if (this->figures[i][j])
				delete this->figures[i][j];
		}
		delete[] this->squares[i];
		delete[] this->figures[i];
	}
	delete[] this->squares;
	delete[] this->figures;
}
