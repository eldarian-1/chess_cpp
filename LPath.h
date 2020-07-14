#pragma once

class LPlayer;
class LSquare;

class LPath
{
private:
	static LSquare* nullSquare;

	LPlayer* playerActive;
	LPlayer* playerPassive;
	LSquare*& from;
	LSquare*& to;
	int _isPossible;

public:
	LPath(
		LSquare*& from = nullSquare,
		LSquare*& to = nullSquare
	);

	LPath(
		LPlayer* act = nullptr,
		LPlayer* pass = nullptr,
		LSquare*& from = nullSquare,
		LSquare*& to = nullSquare
	);

	LPath(const LPath& path);

	~LPath();

	LPath* getClone();
	LPlayer* getActive();
	LPlayer* getPassive();
	LSquare*& getFrom();
	LSquare*& getTo();
	int isPossible();

	void setPossible(int isPossible);

};
