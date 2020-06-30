#pragma once

#include "LGame.h"

class LNetGame :
	public LGame
{
private:


public:
	LNetGame(int color);

	void draw() override;

	void clear() override;

};
