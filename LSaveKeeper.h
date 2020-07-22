#pragma once

#include <QStringList>

class LSave;
class LGame;

class LSaveKeeper
{
public:
	static QStringList getNameSaves();

	static void save(QString name);
	static void rewriteSave(QString oldGame);
	static LGame* loadSave(QString name);
	static void deleteSave(QString name);

};
