#include "LBiGame.h"

#include <QString>

#include "LConst.h"
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
	figures(new LFigure**[L_CHESS_BOARD_SIZE])
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

void LBiGame::draw()
{
	LDesk* desk = LDesk::getInstance();

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j]->draw(!this->isActive1);
			if (this->figures[i][j])
			{
				this->figures[i][j]->draw(this->squares[i][j], !this->isActive1);
			}
		}
	}
}

void LBiGame::setFigure(int v, int h, LFigure* figure)
{
	this->figures[v][h] = figure;
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
