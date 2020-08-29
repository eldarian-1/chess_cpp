#include "LSaveKeeper.h"

#include "LConst.h"
#include "LBiGame.h"
#include "LBotGame.h"
#include "LPlayer.h"
#include "LBoard.h"

#include <QDir>
#include <QTextStream>

#define LCHILD
#include "LGame.cpp"
#undef LCHILD

LSaveKeeper* LSaveKeeper::instance = nullptr;

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

		stream << game->m->gameInstance << '\n';
		stream << *game->m->playerWhite;
		stream << *game->m->playerBlack;
		stream << *game->m->board;
		stream << game->m->_isCheck << '\n';
		stream << (game->m->areWhiteActive ? 1 : 0) << '\n';

		if (typeOfGame == L_TYPE_BOT)
		{
			LBotGame* bgame = (LBotGame*)game;

			stream << ((bgame->me == game->m->playerWhite) ? 1 : 0) << '\n';
			stream << ((bgame->bot == game->m->playerBlack) ? 1 : 0) << '\n';
			stream << (bgame->isBlocked ? 1 : 0) << '\n';
		}

		file.close();
	}
}

void LSaveKeeper::rewriteSave(QString oldGame)
{
	this->deleteSave(oldGame);
	this->save(oldGame);
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

		stream >> game->m->gameInstance;
		stream >> *game->m->playerWhite;
		stream >> *game->m->playerBlack;
		stream >> *game->m->board;
		stream >> game->m->_isCheck;
		stream >> flag;

		game->m->areWhiteActive = flag != 0;

		if (typeOfGame == L_TYPE_BOT)
		{
			LBotGame* bgame = (LBotGame*)game;

			stream >> flag;
			bgame->me = flag ? game->m->playerWhite : game->m->playerBlack;

			stream >> flag;
			bgame->bot = flag ? game->m->playerBlack : game->m->playerWhite;

			stream >> flag;
			bgame->isBlocked = flag;
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
