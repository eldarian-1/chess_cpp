#include "LPath.h"

LSquare* LPath::nullPtr = nullptr;

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
