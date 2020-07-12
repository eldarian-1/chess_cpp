#pragma once

class LPlayer;
class LSquare;

class LPath
{
private:
	static LSquare* nullPtr;

	LPlayer* playerActive;
	LPlayer* playerPassive;
	LSquare*& from;
	LSquare*& to;
	int _isPossible;

public:
	LPath(
		LSquare*& from = nullPtr,
		LSquare*& to = nullPtr
	);

	LPath(
		LPlayer* act = nullptr,
		LPlayer* pass = nullptr,
		LSquare*& from = nullPtr,
		LSquare*& to = nullPtr
	);

	LPlayer* getActive();
	LPlayer* getPassive();
	LSquare*& getFrom();
	LSquare*& getTo();
	int isPossible();

	void setPossible(int isPossible);

};
