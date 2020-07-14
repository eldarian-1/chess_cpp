#include "LBoard.h"

#include "LConst.h"

#include "LPath.h"
#include "LSquare.h"
#include "LFigure.h"

#include "LKing.h"
#include "LQueen.h"
#include "LElephant.h"
#include "LHorse.h"
#include "LRook.h"
#include "LPawn.h"

LBoard::LBoard()
	:
	squares(new LSquare** [L_CHESS_BOARD_SIZE]),
	figures(new LFigure** [L_CHESS_BOARD_SIZE])
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		this->squares[i] = new LSquare * [L_CHESS_BOARD_SIZE];
		this->figures[i] = new LFigure * [L_CHESS_BOARD_SIZE];
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			int color = (i + j) % 2 + L_COLOR_WHITE;
			this->squares[i][j] = new LSquare(i, j, color);
			this->figures[i][j] = nullptr;
		}
	}

	this->figures[0][4] = new LKing(L_COLOR_BLACK);
	this->figures[0][3] = new LQueen(L_COLOR_BLACK);
	this->figures[0][2] = new LElephant(L_COLOR_BLACK);
	this->figures[0][5] = new LElephant(L_COLOR_BLACK);
	this->figures[0][1] = new LHorse(L_COLOR_BLACK);
	this->figures[0][6] = new LHorse(L_COLOR_BLACK);
	this->figures[0][0] = new LRook(L_COLOR_BLACK);
	this->figures[0][7] = new LRook(L_COLOR_BLACK);
	this->figures[1][0] = new LPawn(L_COLOR_BLACK);
	this->figures[1][1] = new LPawn(L_COLOR_BLACK);
	this->figures[1][2] = new LPawn(L_COLOR_BLACK);
	this->figures[1][3] = new LPawn(L_COLOR_BLACK);
	this->figures[1][4] = new LPawn(L_COLOR_BLACK);
	this->figures[1][5] = new LPawn(L_COLOR_BLACK);
	this->figures[1][6] = new LPawn(L_COLOR_BLACK);
	this->figures[1][7] = new LPawn(L_COLOR_BLACK);

	this->figures[7][4] = new LKing(L_COLOR_WHITE);
	this->figures[7][3] = new LQueen(L_COLOR_WHITE);
	this->figures[7][2] = new LElephant(L_COLOR_WHITE);
	this->figures[7][5] = new LElephant(L_COLOR_WHITE);
	this->figures[7][1] = new LHorse(L_COLOR_WHITE);
	this->figures[7][6] = new LHorse(L_COLOR_WHITE);
	this->figures[7][0] = new LRook(L_COLOR_WHITE);
	this->figures[7][7] = new LRook(L_COLOR_WHITE);
	this->figures[6][0] = new LPawn(L_COLOR_WHITE);
	this->figures[6][1] = new LPawn(L_COLOR_WHITE);
	this->figures[6][2] = new LPawn(L_COLOR_WHITE);
	this->figures[6][3] = new LPawn(L_COLOR_WHITE);
	this->figures[6][4] = new LPawn(L_COLOR_WHITE);
	this->figures[6][5] = new LPawn(L_COLOR_WHITE);
	this->figures[6][6] = new LPawn(L_COLOR_WHITE);
	this->figures[6][7] = new LPawn(L_COLOR_WHITE);
}

LBoard::LBoard(const LBoard& board)
	:
	squares(new LSquare** [L_CHESS_BOARD_SIZE]),
	figures(new LFigure** [L_CHESS_BOARD_SIZE])
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		this->squares[i] = new LSquare * [L_CHESS_BOARD_SIZE];
		this->figures[i] = new LFigure * [L_CHESS_BOARD_SIZE];
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			int color = (i + j) % 2 + L_COLOR_WHITE;
			this->squares[i][j] = new LSquare(i, j, color);
			this->figures[i][j] = nullptr;

			if (board.figures[i][j])
			{
				int color = board.figures[i][j]->getColor();
				int type = board.figures[i][j]->getType();

				switch (type)
				{
				case L_FIGURE_KING:
					this->figures[i][j] = new LKing(color);
					break;

				case L_FIGURE_QUEEN	:
					this->figures[i][j] = new LQueen(color);
					break;

				case L_FIGURE_ELEPHANT:
					this->figures[i][j] = new LElephant(color);
					break;

				case L_FIGURE_HORSE:
					this->figures[i][j] = new LHorse(color);
					break;

				case L_FIGURE_ROOK:
					this->figures[i][j] = new LRook(color);
					break;

				case L_FIGURE_PAWN:
					this->figures[i][j] = new LPawn(color);
					break;
				}
			}
		}
	}
}

LBoard::~LBoard()
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

LBoard* LBoard::getClone()
{
	return new LBoard(*this);
}

LSquare*& LBoard::getSquare(int v, int h) const
{
	return this->squares[v][h];
}

LFigure*& LBoard::getFigure(int v, int h) const
{
	return this->figures[v][h];
}

void LBoard::setFigure(LFigure* figure, int v, int h)
{
	this->figures[v][h] = figure;
}

void LBoard::completePath(LPath* path)
{
	
}
