#include "LSaveKeeper.h"

#include "LConst.h"
#include "LBiGame.h"
#include "LBotGame.h"
#include "LPlayer.h"
#include "LBoard.h"

#include <QDir>
#include <QTextStream>

LSaveKeeper* LSaveKeeper::instance = nullptr;

LSaveKeeper::LSaveKeeper()
{

}

LSaveKeeper* LSaveKeeper::getInstance()
{
	if (!instance)
	{
		instance = new LSaveKeeper;
	}

	return instance;
}

void LSaveKeeper::save(QString name)
{
	LGame * const & game = LGame::instance;

	QString path = QDir::currentPath() + "/save/" + name + ".save";
	QFile file(path);
	if (file.open(QIODevice::WriteOnly))
	{
		QTextStream stream(&file);

		int typeOfGame = game->getTypeOfGame();

		stream << typeOfGame << '\n';

		if (typeOfGame == L_TYPE_BOT)
		{
			LBotGame* bgame = (LBotGame*)game;

			stream << bgame->getTypeOfBot() << '\n';
		}

		stream << game->gameInstance << '\n';
		stream << *game->playerWhite;
		stream << *game->playerBlack;
		stream << *game->board;
		stream << game->_isCheck << '\n';
		stream << (int)game->areWhiteActive << '\n';

		if (typeOfGame == L_TYPE_BOT)
		{
			LBotGame* bgame = (LBotGame*)game;

			stream << (bgame->me == game->playerWhite) << '\n';
			stream << (bgame->bot == game->playerBlack) << '\n';
			stream << bgame->isBlocked << '\n';
		}

		file.close();
	}
}

void LSaveKeeper::rewriteSave(QString oldGame)
{
	deleteSave(oldGame);
	save(oldGame);
}

LGame* LSaveKeeper::loadSave(QString name)
{
	LGame*& game = LGame::instance;
	int flag = false;

	QString path = QDir::currentPath() + "/save/" + name + ".save";
	QFile file(path);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);

		int typeOfGame;
		stream >> typeOfGame;

		if (typeOfGame == L_TYPE_BI)
		{
			LGame::loadGame(typeOfGame);
		}
		else
		{
			int typeOfBot;
			stream >> typeOfBot;

			LGame::loadGame(typeOfGame, typeOfBot);
		}

		stream >> game->gameInstance;
		stream >> *game->playerWhite;
		stream >> *game->playerBlack;
		stream >> *game->board;
		stream >> game->_isCheck;
		stream >> flag;

		game->areWhiteActive = flag != 0;

		if (typeOfGame == L_TYPE_BOT)
		{
			LBotGame* bgame = (LBotGame*)game;

			stream >> flag;
			if (flag)
			{
				bgame->me = game->playerWhite;
			}
			else
			{
				bgame->me = game->playerBlack;
			}

			stream >> flag;
			if (flag)
			{
				bgame->bot = game->playerBlack;
			}
			else
			{
				bgame->bot = game->playerWhite;
			}

			stream >> flag;
			bgame->isBlocked = (flag == 0);
		}

		file.close();
	}

	return game;
}

void LSaveKeeper::deleteSave(QString name)
{
	QString path = QDir::currentPath() + "/save/" + name + ".save";
	QFile file(path);
	file.remove();
}

QStringList LSaveKeeper::getNameSaves()
{
	QString path = QDir::currentPath() + "/save";
	QDir dir(path);
	QStringList saves = dir.entryList();

	saves.removeFirst();
	saves.removeFirst();

	for (int i = 0; i < saves.size(); i++)
	{
		saves[i].remove(".save");
	}

	return saves;
}
