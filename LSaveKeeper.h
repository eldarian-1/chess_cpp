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
	static QStringList getNameSaves();

	static void save(QString name);
	static void rewriteSave(QString oldGame);
	static LGame* loadSave(QString name);
	static void deleteSave(QString name);

};
