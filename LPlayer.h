#pragma once

#include <QString>
#include <QVector>

class LFigure;

class LPlayer
{
private:
	int color;
	QString name;
	QVector<LFigure*> figures;

public:
	LPlayer(int color, QString name);

	int getColor() const;
	QString getName() const;

	int getFigureCount();
	LFigure* operator [] (int index) const;

	void addFigure(LFigure* figure);

};
