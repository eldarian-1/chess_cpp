#include "LChessBoard.h"

#include "LConst.h"
#include "LDesk.h"

LChessBoard* LChessBoard::instance = nullptr;

LChessBoard* LChessBoard::getInstance()
{
	if (!LChessBoard::instance)
	{
		LChessBoard::instance = new LChessBoard();
	}

	return LChessBoard::instance;
}

LChessBoard::LChessBoard()
	:
	activeSquare(nullptr),
	activeFigure(nullptr),
	focusedSquare(nullptr)
{
	this->squares = new LSquare * *[L_CHESS_BOARD_SIZE];
	this->figures = new LFigure * *[L_CHESS_BOARD_SIZE];
	this->figureCount = L_FIGURE_COUNT;

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		this->squares[i] = new LSquare * [L_CHESS_BOARD_SIZE];
		this->figures[i] = new LFigure * [L_CHESS_BOARD_SIZE];

		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j] = new LSquare(i, j);
			this->figures[i][j] = nullptr;
		}
	}
}

void LChessBoard::setReverseOf(LChessBoard* board)
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j] = new LSquare(i, j);
			this->figures[i][j] = board->figures[L_CHESS_BOARD_SIZE - 1 - i][L_CHESS_BOARD_SIZE - 1 - j];
		}
	}
}

void LChessBoard::swapFigurePlace(LSquare* oldPlace, LSquare* newPlace, int activePlayer, int passivePlayer)
{
	int oldX = oldPlace->getHorizontal();
	int oldY = oldPlace->getVertical();
	int newX = newPlace->getHorizontal();
	int newY = newPlace->getVertical();

	LChessBoard::getInstance(activePlayer)->figures[newY][newX] = LChessBoard::getInstance(activePlayer)->figures[oldY][oldX];
	LChessBoard::getInstance(activePlayer)->figures[oldY][oldX] = nullptr;

	LChessBoard::getInstance(passivePlayer)->figures[L_CHESS_BOARD_SIZE - 1 - newY][L_CHESS_BOARD_SIZE - 1 - newX] = LChessBoard::getInstance(passivePlayer)->figures[L_CHESS_BOARD_SIZE - 1 - oldY][L_CHESS_BOARD_SIZE - 1 - oldX];
	LChessBoard::getInstance(passivePlayer)->figures[L_CHESS_BOARD_SIZE - 1 - oldY][L_CHESS_BOARD_SIZE - 1 - oldX] = nullptr;
}

LChessBoard* LChessBoard::setFigure(int vertical, int horizontal, LFigure* figure)
{
	this->figures[vertical][horizontal] = figure;
	return this;
}

void LChessBoard::draw()
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j]->draw();

			if (this->figures[i][j])
				this->figures[i][j]->draw(this->squares[i][j]);
		}
}

LSquare* LChessBoard::getSquare(int vertical, int horizontal)
{
	if ((vertical >= 0) && (vertical < L_CHESS_BOARD_SIZE) && (horizontal >= 0) && (horizontal < L_CHESS_BOARD_SIZE))
	{
		return this->squares[vertical][horizontal];
	}
	else
	{
		return nullptr;
	}
}

LFigure* LChessBoard::getFigure(int vertical, int horizontal)
{
	if ((vertical >= 0) && (vertical < L_CHESS_BOARD_SIZE) && (horizontal >= 0) && (horizontal < L_CHESS_BOARD_SIZE))
	{
		return this->figures[vertical][horizontal];
	}
	else
	{
		return nullptr;
	}
}

void LChessBoard::getPlace(LSquare*& square, LFigure*& figure, int x, int y)
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE && !square; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE && !square; j++)
		{
			int xT = this->squares[i][j]->getHorizontal() * LOpenGL::edgeSquare + LOpenGL::leftMargin;
			int yT = this->squares[i][j]->getVertical() * LOpenGL::edgeSquare + LOpenGL::topMargin;

			if ((x >= xT) && (y >= yT) && (x <= xT + LOpenGL::edgeSquare) && (y <= yT + LOpenGL::edgeSquare))
			{
				square = this->squares[i][j];
				figure = this->figures[i][j];
			}
		}
	}
}

bool LChessBoard::isTakenPlace(int vertical, int horizontal)
{
	return ((vertical >= 0) && (vertical < L_CHESS_BOARD_SIZE) && (horizontal >= 0) && (horizontal < L_CHESS_BOARD_SIZE) && (this->figures[vertical][horizontal]));
}

void LChessBoard::mousePress(int x, int y, LPlayer* activePlayer)
{
	LSquare* square = nullptr;
	LFigure* figure = nullptr;

	this->getPlace(square, figure, x, y);

	if (square && figure && figure->getColor() == activePlayer->getColor())
	{
		square->setState(LAppConst::L_SQUARE_SELECTED);
		this->activeSquare = square;
		this->activeFigure = figure;
	}
}

bool LChessBoard::mouseRelease(int x, int y, LPlayer* activePlayer, LPlayer* passivePlayer)
{
	LSquare* square = nullptr;
	LFigure* figure = nullptr;

	bool flag = false;

	this->getPlace(square, figure, x, y);

	if (this->activeSquare)
	{
		this->activeSquare->setState(LAppConst::L_SQUARE_NATIVE);

		if ((activePlayer->getColor() == this->activeFigure->getColor()) && this->activeFigure->isPossiblePosition(this->activeSquare, square))
		{
			LChessBoard::swapFigurePlace(activeSquare, square, activePlayer->getColor(), passivePlayer->getColor());
			flag = true;
		}

		this->activeSquare = nullptr;
		this->activeFigure = nullptr;
	}

	return flag;
}

void LChessBoard::mouseMotionMove(int x, int y)
{
	
}

void LChessBoard::mouseMove(int x, int y)
{
	LSquare* square = nullptr;
	LFigure* figure = nullptr;

	this->getPlace(square, figure, x, y);

	if (square != this->activeSquare)
	{

		if (this->focusedSquare)
		{
			this->focusedSquare->setState(LAppConst::L_SQUARE_NATIVE);
		}

		if (square)
		{
			this->focusedSquare = square;
			this->focusedSquare->setState(LAppConst::L_SQUARE_FOCUSED);
		}

	}
}
