#include "LBotGame.h"

#include "LMainWidget.h"

#include "LConst.h"
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

LBotGame::LBotGame(int c)
	:
	LGame(),
	myColor(c)
{
	QString n1 = LOptions::getInstance()->getName();
	QString n2 = "Computer";

	this->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		(this->myColor == L_COLOR_WHITE ? n1 : n2)
	);

	this->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(this->myColor == L_COLOR_WHITE ? n2 : n1)
	);

	this->areWhiteActive = this->myColor == L_COLOR_WHITE;
	this->isBlocked = !this->areWhiteActive;
}

void LBotGame::actionAfterPath()
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
	this->completeMove();
}

QVector<LPath*> LBotGame::uglyMoves()
{
	QVector<LPath*> paths;

	LPlayer* bot = (this->areWhiteActive) ? this->playerBlack : this->playerWhite;
	LPlayer* me = (this->areWhiteActive) ? this->playerWhite : this->playerBlack;

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (this->figures[i][j] && this->figures[i][j]->getColor() != this->myColor)
			{
				for (int k = 0; k < L_CHESS_BOARD_SIZE; k++)
				{
					for (int l = 0; l < L_CHESS_BOARD_SIZE; l++)
					{
						LPath* path = new LPath(bot, me, this->squares[i][j], this->squares[k][l]);

						int result = this->figures[i][j]->isPossiblePath(path);

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

LPath* LBotGame::calculateBestMove()
{
	QVector<LPath*> paths = this->uglyMoves();
	return paths[rand() % paths.size()];
}

void LBotGame::completeMove()
{
	LMainWidget* mainWidget = LMainWidget::getInstance();

	LPath* path = this->calculateBestMove();

	LGame::completeMove(path);
}
