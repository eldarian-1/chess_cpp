#pragma once

#include <QString>

class LGame;

class LSave
{
private:
	QString name;
	LGame* game;

public:
	QString getName();
	LGame* getGame();


};
