#include "LPlayer.h"

#include "LFigure.h"
#include "LConst.h"

#include <QJsonObject>
#include <QJsonValue>

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

LPlayer* LPlayer::playerFromJson(QJsonObject* document)
{
	LPlayer* player;
	QJsonObject oPlayer = (*document)["player"].toObject();

	if (oPlayer.isEmpty())
	{
		player = nullptr;
	}
	else
	{
		player = new LPlayer(
			oPlayer["color"].toInt(),
			oPlayer["name"].toString()
		);
	}

	return player;
}

QString LPlayer::toJsonClientString(QString name)
{
	return "{\"player\":{\"name\":\"" + name + "\"}}";
}

QString LPlayer::toJsonServerString(QString name)
{
	return "{\"player\":{\"name\":\"" + name + "\", \"color\":"
		+ QString::number(rand() % 2 + L_COLOR_WHITE) + "}}";
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
