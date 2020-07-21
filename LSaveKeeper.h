#pragma once

#include <QVector>

class LSave;
class LGame;

class LSaveKeeper
{
private:
	static LSaveKeeper* instance;

	QVector<LSave*> games;

	LSaveKeeper();

	static LSaveKeeper* getInstance();

public:
	static QVector<QString> getNameSaves();

	static void save(QString name, LGame* game);
	static void rewriteSave(QString oldGame, LGame* newGame);
	static LGame* loadSave(QString name);
	static void deleteSave(QString name);

};
