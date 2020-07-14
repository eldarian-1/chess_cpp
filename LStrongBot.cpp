#include "LStrongBot.h"

#include <QVector>

#include "LBotTree.h"
#include "LBoard.h"
#include "LPath.h"
#include "LSquare.h"
#include "LFigure.h"

LBotTree* LStrongBot::botTree = new LBotTree;

void LStrongBot::clearTree()
{
	botTree->clear();
}

LPath* LStrongBot::calculateBestMove()
{
	this->minimax();

	LPath* path;

	int size = botTree->getSize();

	int index = -1, value = 0;

	for (int i = 0; i < size; i++)
	{
		int tempValue = (*botTree)[i]->getValue();

		if (value < tempValue)
		{
			index = i;
			value = tempValue;
		}
	}

	if (index != -1)
	{
		path = (*botTree)[index]->getPath();
		path = path->getClone();
	}
	else if (!size)
	{
		path = nullptr;
	}
	else
	{
		path = (*botTree)[rand() % size]->getPath();
		path = path->getClone();
	}

	clearTree();

	return path;
}

void LStrongBot::minimax(LBotTree* botTree, int depth, bool itsMe)
{
	LBoard* board;

	if (!botTree)
	{
		botTree = LStrongBot::botTree;
		board = this->board;
	}
	else
	{
		board = botTree->getBoard();
	}

	QVector<LPath*> paths = this->uglyMoves(itsMe, botTree->getBoard());
	int size = paths.size();

	if (size)
	{
		for (int i = 0; i < size; i++)
		{
			LPath* tempPath = paths[i]->getClone();

			LSquare* from = tempPath->getFrom();
			LSquare* to = tempPath->getTo();

			int fromVer = from->getVertical();
			int fromHor = from->getHorizontal();

			int toVer = to->getVertical();
			int toHor = to->getHorizontal();

			LFigure* figure = board->getFigure(toVer, toHor);
			int value = 0;

			if (figure)
			{
				value = ((itsMe) ? (-1) : (1)) * figure->getValue();
				value = value + ((itsMe) ? (1) : (-1)) * board->getFigure(fromVer, fromHor)->getType();
			}

			LBotTree* tempTree = botTree->addChild(board, tempPath, value);

			if (depth > 1)
			{
				minimax(tempTree, depth + ((itsMe) ? (-1) : (0)), !itsMe);
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		delete paths[i];
	}
}
