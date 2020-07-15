#pragma once

#include <QString>
#include <QVector>

class QDomDocument;

class LFigure;

class LPlayer
{
private:
	LPlayer* original;

	int color;
	QString name;
	QVector<LFigure*> figures;

public:
	LPlayer(int color, QString name = "");
	LPlayer(const LPlayer& player);

	static LPlayer* playerFromXml(QDomDocument* document);

	LPlayer* getOriginal() const;
	LPlayer* getClone() const;
	int getColor() const;
	QString getName() const;
	QString getText() const;

	int getFigureCount() const;
	LFigure* operator [] (int index) const;

	void setName(QString name);

	void addFigure(LFigure* figure);

};
