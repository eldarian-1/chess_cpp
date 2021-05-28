#pragma once

#include <QWidget>

class LPlayer;
class LSquare;

class LDesk :
	public QWidget
{
private:
	static LDesk* instance;

	static int edgeBoard;
	static int edgeSquare;
	static int leftMargin;
	static int topMargin;

	static void makeCalculations(int width, int height);

	bool mouseIsPressed;

protected:
	LDesk(QWidget* widget);

public:
	static LDesk* getInstance(QWidget* widget = nullptr);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	//virtual void mouseMoveEvent(QMouseEvent* event);

public:
	void drawTablePlayer(LPlayer* player, bool areWhiteActive);
	void drawMarkup(bool areWhiteActive);
	void drawSquare(LSquare* position, bool areWhiteActive);

	void calculateForDrawFigure(int& x, int& y, LSquare* position, bool areWhiteActive);

	void drawKing(int color, LSquare* position, bool areWhiteActive);
	void drawQueen(int color, LSquare* position, bool areWhiteActive);
	void drawElephant(int color, LSquare* position, bool areWhiteActive);
	void drawHorse(int color, LSquare* position, bool areWhiteActive);
	void drawRook(int color, LSquare* position, bool areWhiteActive);
	void drawPawn(int color, LSquare* position, bool areWhiteActive);

	void drawKing(int color, int x, int y);
	void drawQueen(int color, int x, int y);
	void drawElephant(int color, int x, int y);
	void drawHorse(int color, int x, int y);
	void drawRook(int color, int x, int y);
	void drawPawn(int color, int x, int y);

};
