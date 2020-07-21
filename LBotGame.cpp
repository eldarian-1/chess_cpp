#include "LBotGame.h"

#include "LMainWidget.h"

#include "LConst.h"
#include "LBoard.h"
#include "LPath.h"
#include "LFigure.h"
#include "LSquare.h"
#include "LPlayer.h"
#include "LOptions.h"

#include <QVector>

#include "LKing.h"
#include "LQueen.h"
#include "LElephant.h"
#include "LHorse.h"
#include "LRook.h"

LBotGame::LBotGame(int color)
	:
	LGame()
{
	QString n1 = LOptions::getInstance()->getName();
	QString n2 = "Computer";

	this->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		(color == L_COLOR_WHITE ? n1 : n2)
	);

	this->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(color == L_COLOR_WHITE ? n2 : n1)
	);

	this->me = (color == L_COLOR_WHITE) ? (this->playerWhite) : (this->playerBlack);
	this->bot = (color == L_COLOR_WHITE) ? (this->playerBlack) : (this->playerWhite);

	this->me = this->me->getClone();
	this->bot = this->bot->getClone();

	this->areWhiteActive = color == L_COLOR_WHITE;
	this->isBlocked = !this->areWhiteActive;
}

LBotGame::~LBotGame()
{
	this->clear();
}

void LBotGame::actionAfterPath(LPath* path)
{
	this->setBlocked(true);
	this->waitBot();
	this->setBlocked(false);
}

void LBotGame::setBlocked(bool block)
{
	this->isBlocked = block;
}

void LBotGame::waitBot()
{
	LPath* path = this->calculateBestMove();

	if (path)
	{
		this->completeMove(path);
		delete path;
	}
	else
	{

		LMainWidget* mainWidget = LMainWidget::getInstance();
		QString node = "";

		if (this->isMat(this->bot->getColor()))
		{
			this->changeGameInstance(L_GAME_PAUSE | L_PATH_MAT | this->bot->getColor());

			node = this->me->getName() + " win!\n";
			node += this->me->getName() + " mat " + this->bot->getName();
		}
		else if (this->isPat(this->bot->getColor()))
		{
			this->changeGameInstance(L_GAME_PAUSE | L_PATH_PAT);

			node = "Dead Heat!\nStalemate situation.";
		}

		mainWidget->pathListAppend(node);
		mainWidget->messageAlert(node);
	}
}

QVector<LPath*> LBotGame::uglyMoves(bool itsMe, LBoard* board)
{
	QVector<LPath*> paths;

	if (!board)
	{
		board = this->board;
	}

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (board->getFigure(i, j) && board->getFigure(i, j)->getColor() == this->bot->getColor())
			{
				for (int k = 0; k < L_CHESS_BOARD_SIZE; k++)
				{
					for (int l = 0; l < L_CHESS_BOARD_SIZE; l++)
					{
						LPath* path = new LPath(this->bot->getClone(), this->me->getClone(), board->getSquare(i, j), board->getSquare(k, l));

						int result = board->getFigure(i, j)->isPossiblePath(path);

						if (result & L_PATH_TRUE)
						{
							path->setPossible(result);
							paths.push_back(path);
						}
						else
						{
							delete path;
						}
					}
				}
			}
		}
	}

	return paths;
}

int LBotGame::getFigureTransformation()
{
	int figure;

	if (!this->isBlocked)
	{
		figure = LGame::getFigureTransformation();
	}
	else
	{
		figure = L_FIGURE_QUEEN;
	}

	return figure;
}

int LBotGame::getTypeOfGame()
{
	return L_TYPE_BOT;
}

void LBotGame::clear()
{
	LGame::~LGame();
	delete this->me;
	delete this->bot;
}
