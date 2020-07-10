#pragma once

#include "LGame.h"

#include <QString>

class LBiGame :
	public LGame
{
private:

public:
	LBiGame(QString name1, QString name2, int color);

	void draw() override;

	virtual void mousePress(int vertical, int horizontal) override;
	virtual void mouseRelease(int vertical, int horizontal) override;
	virtual void mouseMotionMove(int vertical, int horizontal) override;
	virtual void mouseMove(int vertical, int horizontal) override;

	void actionAfterPath() override;

	void clear() override;

};
