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

				this->figures[i][j] = LFigure::create(type, color);
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

void LBoard::setFigures()
{
	this->figures[0][4] = LFigure::create(L_FIGURE_KING, L_COLOR_BLACK);
	this->figures[0][3] = LFigure::create(L_FIGURE_QUEEN, L_COLOR_BLACK);
	this->figures[0][2] = LFigure::create(L_FIGURE_ELEPHANT, L_COLOR_BLACK);
	this->figures[0][5] = LFigure::create(L_FIGURE_ELEPHANT, L_COLOR_BLACK);
	this->figures[0][1] = LFigure::create(L_FIGURE_HORSE, L_COLOR_BLACK);
	this->figures[0][6] = LFigure::create(L_FIGURE_HORSE, L_COLOR_BLACK);
	this->figures[0][0] = LFigure::create(L_FIGURE_ROOK, L_COLOR_BLACK);
	this->figures[0][7] = LFigure::create(L_FIGURE_ROOK, L_COLOR_BLACK);
	this->figures[1][0] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][1] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][2] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][3] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][4] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][5] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][6] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);
	this->figures[1][7] = LFigure::create(L_FIGURE_PAWN, L_COLOR_BLACK);

	this->figures[7][4] = LFigure::create(L_FIGURE_KING, L_COLOR_WHITE);
	this->figures[7][3] = LFigure::create(L_FIGURE_QUEEN, L_COLOR_WHITE);
	this->figures[7][2] = LFigure::create(L_FIGURE_ELEPHANT, L_COLOR_WHITE);
	this->figures[7][5] = LFigure::create(L_FIGURE_ELEPHANT, L_COLOR_WHITE);
	this->figures[7][1] = LFigure::create(L_FIGURE_HORSE, L_COLOR_WHITE);
	this->figures[7][6] = LFigure::create(L_FIGURE_HORSE, L_COLOR_WHITE);
	this->figures[7][0] = LFigure::create(L_FIGURE_ROOK, L_COLOR_WHITE);
	this->figures[7][7] = LFigure::create(L_FIGURE_ROOK, L_COLOR_WHITE);
	this->figures[6][0] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][1] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][2] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][3] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][4] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][5] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][6] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
	this->figures[6][7] = LFigure::create(L_FIGURE_PAWN, L_COLOR_WHITE);
}

void LBoard::setFigure(LFigure* figure, int v, int h)
{
	this->figures[v][h] = figure;
}

void LBoard::completePath(LPath* path)
{

}

QTextStream& operator >> (QTextStream& out, LBoard& board)
{
	int count;
	out >> count;

	for (int i = 0; i < count; ++i)
	{
		int v, h, type, color, temp;

		out >> v >> h >> type >> color;

		board.figures[v][h] = LFigure::create(type, color);

		if (type == L_FIGURE_KING)
		{
			out >> temp;
			((LKing*)board.figures[v][h])->setCastled(temp);
		}
		else if (type == L_FIGURE_ROOK)
		{
			out >> temp;
			((LRook*)board.figures[v][h])->setWalked(temp);
		}
	}

	return out;
}

QTextStream& operator << (QTextStream& in, const LBoard& board)
{
	int count = 0;

	for (int v = 0; v < L_CHESS_BOARD_SIZE; ++v)
	{
		for (int h = 0; h < L_CHESS_BOARD_SIZE; ++h)
		{
			if (board.figures[v][h])
			{
				++count;
			}
		}
	}

	in << count << '\n';

	for (int v = 0; v < L_CHESS_BOARD_SIZE; ++v)
	{
		for (int h = 0; h < L_CHESS_BOARD_SIZE; ++h)
		{
			if (board.figures[v][h])
			{
				int type, color;

				type = board.figures[v][h]->getType();
				color = board.figures[v][h]->getColor();

				in << v << '\n';
				in << h << '\n';
				in << type << '\n';
				in << color << '\n';

				if (type == L_FIGURE_KING)
				{
					in << (((LKing*)board.figures[v][h])->isCastled() ? 1 : 0) << '\n';
				}
				else if (type == L_FIGURE_ROOK)
				{
					in << (((LRook*)board.figures[v][h])->isWalked() ? 1 : 0) << '\n';
				}
			}
		}
	}

	return in;
}
