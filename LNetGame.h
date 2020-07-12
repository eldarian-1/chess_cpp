#pragma once

#include "LGame.h"

class LFigure;

class LNetGame :
	public LGame
{
private:
	bool isBlocked;

	void waitNet();

public:
	LNetGame(int color);

	void actionAfterPath() override;

	void setBlocked(bool block);

};
