#include "LDesk.h"

#include "LConst.h"
#include "LMainWidget.h"
#include "LGame.h"
#include "LSquare.h"

#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>

LDesk* LDesk::instance = nullptr;

int LDesk::edgeBoard;
int LDesk::edgeSquare;
int LDesk::leftMargin;
int LDesk::topMargin;

void LDesk::makeCalculations(int width, int height)
{
    LDesk::edgeBoard = (width < height) ? (width) : (height);
    LDesk::edgeSquare = edgeBoard / (L_CHESS_BOARD_SIZE + 2);
    LDesk::leftMargin = (width - edgeBoard) / 2;
    LDesk::topMargin = (height - edgeBoard) / 2;
}

LDesk::LDesk(QWidget* widget)
	:
	QWidget(widget),
    mouseIsPressed(false)
{
	this->setMouseTracking(true);
}

LDesk* LDesk::getInstance(QWidget* widget)
{
	if (!instance)
		instance = new LDesk(widget);

	return instance;
}

void LDesk::paintEvent(QPaintEvent* event)
{
	LGame* game = LGame::getInstance();
	if (game)
	{
		game->draw();
	}
	else
	{
		QPainter painter;
		painter.begin(this);
		painter.drawEllipse(0, 0, this->width(), this->height());
		painter.end();
	}
}

void LDesk::resizeEvent(QResizeEvent* event)
{
    QSize size = event->size();
    LDesk::makeCalculations(size.width(), size.height());
}

void LDesk::mousePressEvent(QMouseEvent* pe)
{
    this->mouseIsPressed = true;
    LGame::getInstance()->mousePress(pe->x(), pe->y());
    this->repaint();
}

void LDesk::mouseReleaseEvent(QMouseEvent* pe)
{
    this->mouseIsPressed = false;
    LGame::getInstance()->mouseRelease(pe->x(), pe->y());
    this->repaint();
}

void LDesk::mouseMoveEvent(QMouseEvent* pe)
{
	if (this->mouseIsPressed)
    {
        LGame::getInstance()->mouseMotionMove(pe->x(), pe->y());
    }
    else
    {
        LGame::getInstance()->mouseMove(pe->x(), pe->y());
    }
    this->repaint();
}

void LDesk::drawSquare(LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;
    int state = position->getState();
    int color = position->getColor();

    QPainter painter;
    QBrush brush;
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    painter.begin(this);

    if (color == L_COLOR_BLACK)
    {
        brush.setColor(QColor(217, 222, 224));
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
    }

    QRect rect(x, y, edgeSquare, edgeSquare);
    painter.drawRect(rect);

    painter.setBrush(QBrush(QColor(217, 222, 224), Qt::NoBrush));

    switch (state)
    {
    case L_SQUARE_NATIVE:
        pen.setColor(QColor(76, 94, 102));
        pen.setWidth(1);
        painter.setPen(pen);
        break;
    case L_SQUARE_FOCUSED:
        pen.setColor(QColor(178, 191, 242));
        pen.setWidth(5);
        painter.setPen(pen);
        rect.setSize(QSize(edgeSquare - 2, edgeSquare - 2));
        rect.setTopLeft(QPoint(x + 2, y + 2));
        break;
    case L_SQUARE_SELECTED:
        pen.setColor(QColor(191, 242, 178));
        pen.setWidth(5);
        painter.setPen(pen);
        rect.setSize(QSize(edgeSquare - 2, edgeSquare - 2));
        rect.setTopLeft(QPoint(x + 2, y + 2));
        break;
    case L_SQUARE_VARIANT:
        pen.setColor(QColor(178, 242, 191));
        pen.setWidth(5);
        painter.setPen(pen);
        rect.setSize(QSize(edgeSquare - 2, edgeSquare - 2));
        rect.setTopLeft(QPoint(x + 2, y + 2));
        break;
    case L_SQUARE_VARIANT_FOCUSED:
        pen.setColor(QColor(191, 178, 242));
        pen.setWidth(5);
        painter.setPen(pen);
        rect.setSize(QSize(edgeSquare - 2, edgeSquare - 2));
        rect.setTopLeft(QPoint(x + 2, y + 2));
        break;
    }

    painter.drawRect(rect);
    painter.end();
}

void LDesk::drawKing(int color, LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;

    QString file = (color == L_COLOR_WHITE) ? ":/LWKing.png" : ":/LBKing.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawQueen(int color, LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;

    QString file = (color == L_COLOR_WHITE) ? ":/LWQueen.png" : ":/LBQueen.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawElephant(int color, LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;

    QString file = (color == L_COLOR_WHITE) ? ":/LWElephant.png" : ":/LBElephant.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawHorse(int color, LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;

    QString file = (color == L_COLOR_WHITE) ? ":/LWHorse.png" : ":/LBHorse.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawRook(int color, LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;

    QString file = (color == L_COLOR_WHITE) ? ":/LWRook.png" : ":/LBRook.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawPawn(int color, LSquare* position, bool reverse)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (reverse)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    ++h;
    ++v;

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;

    QString file = (color == L_COLOR_WHITE) ? ":/LWPawn.png" : ":/LBPawn.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}
