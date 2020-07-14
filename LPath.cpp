#include "LPath.h"

#include "LPlayer.h"

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

LPath* LPath::getClone()
{
	return new LPath(*this);
}

LPlayer* LPath::getActive()
{
	return this->playerActive;
}

LPlayer* LPath::getPassive()
{
	return this->playerPassive;
}

LSquare*& LPath::getFrom()
{
	return this->from;
}

LSquare*& LPath::getTo()
{
	return this->to;
}

int LPath::isPossible()
{
	return this->_isPossible;
}

void LPath::setPossible(int isPossible)
{
	this->_isPossible = isPossible;
}
