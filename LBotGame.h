#pragma once

#include "LGame.h"

class LBotGame :
	public LGame
{
private:


public:
	LBotGame(int color);

	void draw() override;

	void clear() override;

};
