#pragma once

#include "LGame.h"

#include <QString>

class LSquare;
class LFigure;

class LBiGame :
	public LGame
{
private:
	QString name1, name2;
	int color1, color2;
	bool isActive1;
	LSquare*** squares;
	LFigure*** figures;

public:
	LBiGame(QString name1, QString name2, int color);

	void draw() override;

	void setFigure(int vertical, int horizontal, LFigure* figure);

	void clear() override;

};
