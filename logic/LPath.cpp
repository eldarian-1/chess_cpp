#include "LPath.h"

#include "LGame.h"
#include "LPlayer.h"
#include "LSquare.h"

#include <QJsonObject>
#include <QJsonValue>

LSquare* LPath::nullSquare = nullptr;

LPath::LPath(LSquare*& from, LSquare*& to)
	:
	LPath(nullptr, nullptr, from, to)
{

}

LPath::LPath(LPlayer* act, LPlayer* pass, LSquare*& from, LSquare*& to)
	:
	playerActive(act),
	playerPassive(pass),
	from(from),
	to(to),
	_isPossible(0)
{

}

LPath::LPath(const LPath& path)
	:
	playerActive(path.playerActive->getClone()),
	playerPassive(path.playerPassive->getClone()),
	from(path.from),
	to(path.to),
	_isPossible(path._isPossible)
{

}

LPath::~LPath()
{
	delete this->playerActive;
	delete this->playerPassive;
}

LPath* LPath::pathFromJson(QJsonObject* document)
{
	LPath* path;
	QJsonObject oPath = (*document)["path"].toObject();

	if (oPath.isEmpty())
	{
		path = nullptr;
	}
	else
	{
		LGame* game = LGame::getInstance();
		path = new LPath(
			game->getSquare(oPath["v0"].toInt(), oPath["h0"].toInt()),
			game->getSquare(oPath["v1"].toInt(), oPath["h1"].toInt())
		);
		path->setPossible(oPath["isPossible"].toInt());
	}

	return path;
}

LPath* LPath::getClone() const
{
	return new LPath(*this);
}

QString LPath::toUriString() const
{
	return "&v0=" + QString::number(this->from->getVertical())
		+ "&h0=" + QString::number(this->from->getHorizontal())
		+ "&v1=" + QString::number(this->to->getVertical())
		+ "&h1=" + QString::number(this->to->getHorizontal())
		+ "&isPossible=" + QString::number(this->_isPossible);
}

QString LPath::toJsonString() const
{
	return "{\"path\":{\"v0\":" + QString::number(this->from->getVertical())
		+ ",\"h0\":" + QString::number(this->from->getHorizontal())
		+ ",\"v1\":" + QString::number(this->to->getVertical())
		+ ",\"h1\":" + QString::number(this->to->getHorizontal())
		+ ",\"isPossible\":" + QString::number(this->_isPossible)
		+ "}}";
}

LPlayer* LPath::getActive() const
{
	return this->playerActive;
}

LPlayer* LPath::getPassive() const
{
	return this->playerPassive;
}

LSquare*& LPath::getFrom() const
{
	return this->from;
}

LSquare*& LPath::getTo() const
{
	return this->to;
}

int LPath::isPossible() const
{
	return this->_isPossible;
}

void LPath::setActive(LPlayer* active)
{
	this->playerActive = active;
}

void LPath::setPassive(LPlayer* passive)
{
	this->playerPassive = passive;
}

void LPath::setPossible(int isPossible)
{
	this->_isPossible = isPossible;
}

void LPath::clear()
{
	delete this->from;
	delete this->to;
}
