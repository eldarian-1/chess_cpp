#pragma once

class LNewGame;
class LFigure;

class LPlayer;
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

	LSquare*** squares;
	LFigure*** figures;
	int _isCheck;

	bool areWhiteActive;
	LSquare* activeSquare;
	LFigure* activeFigure;
	LSquare* focusedSquare;

	LGame();

	virtual int getGameInstance() const final;
	virtual void changeGameInstance(int gameInstance) final;

public:
	static LGame* getInstance();

	static void newGame(LNewGame* dialog);

	virtual LFigure* getFigure(int vertical, int horizontal) final;
	virtual void draw();

	virtual int isCheck(int color) final;
	virtual int isCheck(int color, int v, int h, int vK = -1, int hK = -1) final;
	virtual int getIsCheck() const final;

	virtual int isMat(int color) final;
	virtual bool isPat(int color) final;

	virtual void mousePress(int vertical, int horizontal);
	virtual void mouseRelease(int vertical, int horizontal);
	virtual void mouseMotionMove(int vertical, int horizontal);
	virtual void mouseMove(int vertical, int horizontal);
	
	virtual void setFigure(int vertical, int horizontal, LFigure* figure) final;

	virtual void actionAfterPath();

	virtual void clear();

};
