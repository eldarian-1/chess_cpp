#include "LSaveKeeper.h"

#include "LConst.h"
#include "LBiGame.h"
#include "LBotGame.h"

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

void LSaveKeeper::save(QString name, LGame* game)
{

}

void LSaveKeeper::rewriteSave(QString oldGame, LGame* newGame)
{
	deleteSave(oldGame);
	save(oldGame, newGame);
}

LGame* LSaveKeeper::loadSave(QString name)
{
	return nullptr;
}

void LSaveKeeper::deleteSave(QString name)
{

}

QVector<QString> LSaveKeeper::getNameSaves()
{
	QVector<QString> saves;

	saves.push_back("1 Any text");
	saves.push_back("2 Any text");
	saves.push_back("3 Any text");
	saves.push_back("4 Any text");
	saves.push_back("5 Any text");

	return saves;
}
