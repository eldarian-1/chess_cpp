#include "LPlayer.h"

#include "LFigure.h"

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

LPlayer::LPlayer(int c, QString n)
	:
	original(this),
	color(c),
	name(n)
{

}

LPlayer::LPlayer(const LPlayer& player)
	:
	original(player.original),
	color(player.color),
	name(player.name),
	figures(player.figures)
{

}

LPlayer* LPlayer::playerFromXml(QDomDocument* document)
{
	QDomNodeList parent = document->documentElement().toElement().childNodes();

	LPlayer* player;

	if (parent.at(0).toElement().tagName() == "wait")
	{
		player = nullptr;
	}
	else
	{
		QString name = parent.at(0).toElement().text();
		int color = parent.at(1).toElement().text().toInt();

		player = new LPlayer(color, name);
	}

	return player;
}

LPlayer* LPlayer::getOriginal() const
{
	return this->original;
}

LPlayer* LPlayer::getClone() const
{
	return new LPlayer(*this);
}

int LPlayer::getColor() const
{
	return this->color;
}

QString LPlayer::getName() const
{
	return this->name;
}

QString LPlayer::getText() const
{
	QString color;
	color.setNum(this->color);

	return "?name=" + this->name + "&color=" + color;
}

int LPlayer::getFigureCount() const
{
	return this->figures.size();
}

LFigure* LPlayer::operator [] (int index) const
{
	return this->figures[index];
}

void LPlayer::setName(QString name)
{
	this->name = name;
}

void LPlayer::addFigure(LFigure* figure)
{
	this->figures.push_back(figure);
}
