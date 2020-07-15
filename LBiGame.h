#pragma once

#include "LGame.h"

#include <QString>

class LBiGame :
	public LGame
{
private:

public:
	LBiGame(QString name1, QString name2, int color);

	void actionAfterPath(LPath* path) override;

};
