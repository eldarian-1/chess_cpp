#pragma once

#include <QWidget>

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
	void drawSquare(LSquare* position, bool areWhiteActive);
	void drawKing(int color, LSquare* position, bool areWhiteActive);
	void drawQueen(int color, LSquare* position, bool areWhiteActive);
	void drawElephant(int color, LSquare* position, bool areWhiteActive);
	void drawHorse(int color, LSquare* position, bool areWhiteActive);
	void drawRook(int color, LSquare* position, bool areWhiteActive);
	void drawPawn(int color, LSquare* position, bool areWhiteActive);

};
