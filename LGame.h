#pragma once

class LNewGame;
class LFigure;

class LPlayer;
class LPath;
class LBoard;
class LSquare;
class LFigure;

struct LGamePrivate;

class LGame
{
private:
	friend class LSaveKeeper;
	static LGame* instance;

protected:
	LGamePrivate* m;

	LGame();
	~LGame();

	virtual int getGameInstance() const final;
	virtual void setGameInstance(int gameInstance) final;

public:
	static LGame* getInstance();

	static void newGame(LNewGame* dialog);
	static void setGame(LGame* game);
	static void loadGame(int typeOfGame, int typeOfBot = -1);

	virtual LFigure* getFigure(int vertical, int horizontal) final;
	virtual LSquare*& getSquare(int vertical, int horizontal) final;
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
	virtual void actionAfterPath(LPath* path);
	virtual int getTypeOfGame();

	virtual void clear();

};
