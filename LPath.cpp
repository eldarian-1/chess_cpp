#include "LPath.h"

#include "LGame.h"
#include "LPlayer.h"
#include "LSquare.h"

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

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

LPath* LPath::pathFromXml(QDomDocument* document)
{
	QDomNodeList parent = document->documentElement().toElement().childNodes();

	LPath* path;

	if (parent.at(0).toElement().tagName() == "wait")
	{
		path = nullptr;
	}
	else
	{
		int fromV = parent.at(0).toElement().text().toInt();
		int fromH = parent.at(1).toElement().text().toInt();
		int toV = parent.at(2).toElement().text().toInt();
		int toH = parent.at(3).toElement().text().toInt();
		int isPossible = parent.at(4).toElement().text().toInt();

		LGame* game = LGame::getInstance();

		path = new LPath(
			game->getSquare(fromV, fromH),
			game->getSquare(toV, toH)
		);

		path->setPossible(isPossible);
	}

	return path;
}

LPath* LPath::getClone() const
{
	return new LPath(*this);
}

QString LPath::getText() const
{
	return "&v0=" + QString::number(this->from->getVertical())
		+ "&h0=" + QString::number(this->from->getHorizontal())
		+ "&v1=" + QString::number(this->to->getVertical())
		+ "&h1=" + QString::number(this->to->getHorizontal())
		+ "&isPossible=" + QString::number(this->_isPossible);
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
