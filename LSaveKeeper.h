#pragma once

#include <QStringList>

class LGame;

class LSaveKeeper
{
private:
	static LSaveKeeper* instance;

protected:
	LSaveKeeper() {}

public:
	static LSaveKeeper* getInstance();

	QStringList getNameSaves();

	void save(QString name);
	void rewriteSave(QString oldGame);
	LGame* loadSave(QString name);
	void deleteSave(QString name);

};
