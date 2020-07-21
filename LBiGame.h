#pragma once

#include "LGame.h"

#include <QString>

class LBiGame :
	public LGame
{
public:
	LBiGame(QString name1, QString name2, int color);

	void actionAfterPath(LPath* path) override;

	virtual int getTypeOfGame() override;

};
