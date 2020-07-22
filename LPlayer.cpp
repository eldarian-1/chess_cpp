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
		QString name = parent.at(1).toElement().text();
		int color = parent.at(2).toElement().text().toInt();

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

	return "&name=" + this->name + "&color=" + color;
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

QTextStream& operator >> (QTextStream& out, LPlayer& player)
{
	out >> player.name;

	int count;
	out >> count;

	for (int i = 0; i < count; ++i)
	{
		int type;
		int color;

		out >> type >> color;

		LFigure* figure = LFigure::create(type, color);
		player.figures.push_back(figure);
	}

	return out;
}

QTextStream& operator << (QTextStream& in, const LPlayer& player)
{
	in << player.name << '\n';

	int count = player.figures.size();
	in << count << '\n';

	for (int i = 0; i < count; ++i)
	{
		int type = player.figures[i]->getType();
		int color = player.figures[i]->getColor();

		in << type << '\n';
		in << color << '\n';
	}

	return in;
}
