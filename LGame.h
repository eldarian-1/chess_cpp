#pragma once

class LNewGame;
class LFigure;

class LPlayer;
class LPath;
class LBoard;
class LSquare;
class LFigure;

class LGame
{
private:
	static LGame* instance;

	int gameInstance;

protected:
	LPlayer* playerWhite;
	LPlayer* playerBlack;

	LBoard* board;
	int _isCheck;

	bool areWhiteActive;
	LSquare* activeSquare;
	LFigure* activeFigure;
	LSquare* focusedSquare;

	LGame();
	~LGame();

	virtual int getGameInstance() const final;
	virtual void changeGameInstance(int gameInstance) final;

public:
	static LGame* getInstance();

	static void newGame(LNewGame* dialog);

	virtual LFigure* getFigure(int vertical, int horizontal) final;
	virtual void draw() final;

	virtual int isCheck(int color) final;
	virtual int isCheck(int color, int v, int h, int vK = -1, int hK = -1) final;
	virtual int getIsCheck() const final;

	virtual int isMat(int color) final;
	virtual bool isPat(int color) final;

	virtual void mousePress(int vertical, int horizontal) final;
	virtual void mouseRelease(int vertical, int horizontal) final;
	virtual void mouseMotionMove(int vertical, int horizontal) final;
	virtual void mouseMove(int vertical, int horizontal) final;

	virtual void completeMove(LPath* path) final;
	virtual int getFigureTransformation();
	virtual void actionAfterPath();

	virtual void clear();

};
