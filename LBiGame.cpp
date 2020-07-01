#include "LBiGame.h"

#include <QString>

#include "LConst.h"
#include "LMainWidget.h"
#include "LTransformation.h"
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
	nameWhite((c == L_COLOR_ANY) ? ((rand() % 2) ? n1 : n2) : ((c == L_COLOR_WHITE) ? n1 : n2)),
	nameBlack((nameWhite == n1) ? n2 : n1),
	areWhiteActive(true),
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
			int color = (i + j + c % 2) % 2 + L_COLOR_WHITE;
			this->squares[i][j] = new LSquare(i, j, color);
			this->figures[i][j] = nullptr;
		}
	}

	int color1 = L_COLOR_WHITE;
	int color2 = L_COLOR_BLACK;

	this->setFigure(0, 4, new LKing(color2));
	this->setFigure(0, 3, new LQueen(color2));
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

	this->setFigure(7, 4, new LKing(color1));
	this->setFigure(7, 3, new LQueen(color1));
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
	if (v < 0 || v >= L_CHESS_BOARD_SIZE || h < 0 || h >= L_CHESS_BOARD_SIZE)
		return nullptr;

	return this->figures[v][h];
}

void LBiGame::draw()
{
	LDesk* desk = LDesk::getInstance();

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j]->draw(areWhiteActive);
		}
	}

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (this->figures[i][j])
			{
				this->figures[i][j]->draw(this->squares[i][j], areWhiteActive);
			}
		}
	}
}

void LBiGame::mousePress(int v, int h)
{
	if (!this->areWhiteActive)
	{
		v = L_CHESS_BOARD_SIZE - 1 - v;
		h = L_CHESS_BOARD_SIZE - 1 - h;
	}

	this->activeSquare = this->squares[v][h];
	this->activeFigure = this->figures[v][h];
	this->focusedSquare = this->squares[v][h];
}

void LBiGame::mouseRelease(int v, int h)
{
	if (
		(this->areWhiteActive && this->activeFigure->getColor() != L_COLOR_WHITE)
		||
		(!this->areWhiteActive && this->activeFigure->getColor() == L_COLOR_WHITE)
		)
	{
		this->activeSquare = nullptr;
		this->activeFigure = nullptr;
		return;
	}

	if (!this->areWhiteActive)
	{
		v = L_CHESS_BOARD_SIZE - 1 - v;
		h = L_CHESS_BOARD_SIZE - 1 - h;
	}

	if (this->activeFigure)
	{
		int response = this->activeFigure->isPossiblePosition(activeSquare, this->squares[v][h]);

		if (response & L_PATH_TRUE)
		{
			QString name = (this->areWhiteActive) ? (this->nameWhite) : (this->nameBlack);
			QString actFig = this->activeFigure->getName();
			QString pasFig = (this->figures[v][h]) ? (" (" + this->figures[v][h]->getName() + ")") : ("");

			this->figures[v][h] = this->activeFigure;
			this->figures[this->activeSquare->getVertical()][this->activeSquare->getHorizontal()] = nullptr;

			QString node = name + ": " + actFig + " " +
				('A' + activeSquare->getHorizontal()) + ('1' + activeSquare->getVertical()) + " - " +
				('A' + this->squares[v][h]->getHorizontal()) + ('1' + this->squares[v][h]->getVertical()) + pasFig;
			LMainWidget::getInstance()->pathListAppend(node);
		}

		if (response & L_PATH_CASTLING)
		{
			QString name = (this->areWhiteActive) ? (this->nameWhite) : (this->nameBlack);
			LGame* game = LGame::getInstance();
			int _h = this->activeSquare->getHorizontal();

			if (h - _h == 2)
			{
				LRook* rook = (LRook*)this->figures[v][h + 1];

				if (!rook)
				{
					rook = (LRook*)this->figures[v][h + 2];
					this->figures[v][h + 2] = nullptr;
				}
				else
				{
					this->figures[v][h + 1] = nullptr;
				}

				this->figures[v][h - 1] = rook;
			}
			else
			{
				LRook* rook = (LRook*)this->figures[v][h - 1];

				if (!rook)
				{
					rook = (LRook*)this->figures[v][h - 2];
					this->figures[v][h - 2] = nullptr;
				}
				else
				{
					this->figures[v][h - 1] = nullptr;
				}

				this->figures[v][h + 1] = rook;
			}

			LMainWidget::getInstance()->pathListAppend(name + ": Castling");
		}

		if (response & L_PATH_TRANSFORMATION)
		{
			LTransformation* dialog = new LTransformation;

			if (dialog->exec() == QDialog::Accepted)
			{
				QString name = (this->areWhiteActive) ? (this->nameWhite) : (this->nameBlack);
				QString newFigure;

				LFigure* temp = this->figures[v][h];

				switch (dialog->getFigure())
				{
				case L_FIGURE_QUEEN:
					newFigure = "Queen";
					this->figures[v][h] = new LQueen(this->figures[v][h]->getColor());
					break;
				case L_FIGURE_ELEPHANT:
					newFigure = "Elephant";
					this->figures[v][h] = new LElephant(this->figures[v][h]->getColor());
					break;
				case L_FIGURE_HORSE:
					newFigure = "Horse";
					this->figures[v][h] = new LHorse(this->figures[v][h]->getColor());
					break;
				case L_FIGURE_ROOK:
					newFigure = "Rook";
					this->figures[v][h] = new LRook(this->figures[v][h]->getColor());
					break;
				}

				QString node = name + ": Pawn to " + newFigure;
				LMainWidget::getInstance()->pathListAppend(node);

				delete temp;
			}

			delete dialog;
		}

		if (response & L_PATH_TRUE)
		{
			this->areWhiteActive = !this->areWhiteActive;
		}
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
