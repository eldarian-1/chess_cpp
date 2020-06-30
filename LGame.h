#pragma once

class LNewGame;

class LGame
{
private:
	static LGame* instance;

public:
	static LGame* getInstance();

	static void newGame(LNewGame* dialog);

	virtual void draw() = 0;

	virtual void mousePress(int x, int y) = 0;
	virtual void mouseRelease(int x, int y) = 0;
	virtual void mouseMotionMove(int x, int y) = 0;
	virtual void mouseMove(int x, int y) = 0;

	virtual void clear() = 0;

};
