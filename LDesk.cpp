#include "LDesk.h"

#include "LConst.h"
#include "LMainWidget.h"
#include "LGame.h"
#include "LPlayer.h"
#include "LSquare.h"
#include "LFigure.h"

#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QFontMetrics>

LDesk* LDesk::instance = nullptr;

int LDesk::edgeBoard;
int LDesk::edgeSquare;
int LDesk::leftMargin;
int LDesk::topMargin;

void LDesk::makeCalculations(int width, int height)
{
    edgeBoard = (width < height) ? (width) : (height);
    edgeSquare = edgeBoard / (L_CHESS_BOARD_SIZE + 2);
    leftMargin = (width - edgeBoard) / 2 + edgeSquare;
    topMargin = (height - edgeBoard) / 2 + edgeSquare;
    edgeBoard -= 2 * edgeSquare;
}

LDesk::LDesk(QWidget* widget)
	:
	QWidget(widget),
    mouseIsPressed(false)
{
	//this->setMouseTracking(true);
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
        QString file = ":/PreView.png";
        QImage image = QImage(file).scaled(this->width() * 0.9, this->height() * 0.9);
        QPainter painter;

        int x = (this->width() - image.width()) / 2;
        int y = (this->height() - image.height()) / 2;

        painter.begin(this);
        painter.drawImage(x, y, image);
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
    int x = pe->x();
    int y = pe->y();
    LGame* game = LGame::getInstance();
    if (game && x >= leftMargin && y >= topMargin && x <= leftMargin + edgeBoard && y <= topMargin + edgeBoard)
    {
        int vertical = (y - topMargin) / edgeSquare;
        int horizontal = (x - leftMargin) / edgeSquare;

        this->mouseIsPressed = true;
        game->mousePress(vertical, horizontal);
        this->repaint();
    }
}

void LDesk::mouseReleaseEvent(QMouseEvent* pe)
{
    this->mouseIsPressed = false;
    int x = pe->x();
    int y = pe->y();
    LGame* game = LGame::getInstance();
    if (game && x >= leftMargin && y >= topMargin && x <= leftMargin + edgeBoard && y <= topMargin + edgeBoard)
    {
        int vertical = (y - topMargin) / edgeSquare;
        int horizontal = (x - leftMargin) / edgeSquare;

        game->mouseRelease(vertical, horizontal);
        this->repaint();
    }
}

/*void LDesk::mouseMoveEvent(QMouseEvent* pe)
{
    int x = pe->x();
    int y = pe->y();
    LGame* game = LGame::getInstance();
    if (game && x >= leftMargin && y >= topMargin && x <= leftMargin + edgeBoard && y <= topMargin + edgeBoard)
    {
        int vertical = (y - topMargin) / edgeSquare;
        int horizontal = (x - leftMargin) / edgeSquare;

        if (this->mouseIsPressed)
        {
            game->mouseMotionMove(vertical, horizontal);
        }
        else
        {
            game->mouseMove(vertical, horizontal);
        }
        this->repaint();
    }
}*/

void LDesk::drawTablePlayer(LPlayer* player, bool areWhiteActive)
{
    QString name = player->getName();
    QFont font;
    font.setFamily("Helvetica");
    font.setPointSize(14);

    QFontMetrics metric(font, this);

    int x, y;
    int color = (player->getColor() == L_COLOR_WHITE) ? L_COLOR_BLACK : L_COLOR_WHITE;

    int count = player->getFigureCount();
    int H = (leftMargin - L_PADDING_BOARD) / edgeSquare;
    int V = ceil(double(count) / H);
    int marginLeft = (leftMargin - L_PADDING_BOARD - H * edgeSquare) / 2;

    if ((areWhiteActive && player->getColor() == L_COLOR_WHITE) || (!areWhiteActive && player->getColor() == L_COLOR_BLACK))
    {
        x = leftMargin + L_PADDING_BOARD + edgeBoard + (leftMargin - L_PADDING_BOARD - metric.width(name)) / 2;
        y = topMargin + L_PADDING_BOARD + edgeBoard - V * edgeSquare - 15;
    }
    else
    {
        x = (leftMargin - L_PADDING_BOARD - metric.width(name)) / 2;
        y = topMargin;
    }

    QPainter painter;
    painter.begin(this);
    painter.setFont(font);
    painter.drawText(x, y, name);
    painter.end();

    if ((areWhiteActive && player->getColor() == L_COLOR_WHITE) || (!areWhiteActive && player->getColor() == L_COLOR_BLACK))
    {
        for (int i = 0, h = 0, v = 0; i < count; ++i, (i % H == 0) ? (++v, h = 0) : (++h))
        {
            x = leftMargin + L_PADDING_BOARD + edgeBoard + marginLeft + h * edgeSquare;
            y = topMargin + L_PADDING_BOARD + edgeBoard - (V - v) * edgeSquare;
            switch ((*player)[i]->getType())
            {
            case L_FIGURE_KING: this->drawKing(color, x, y); break;
            case L_FIGURE_QUEEN: this->drawQueen(color, x, y); break;
            case L_FIGURE_ELEPHANT: this->drawElephant(color, x, y); break;
            case L_FIGURE_HORSE: this->drawHorse(color, x, y); break;
            case L_FIGURE_ROOK: this->drawRook(color, x, y); break;
            case L_FIGURE_PAWN: this->drawPawn(color, x, y); break;
            }
        }
    }
    else
    {
        for (int i = 0, h = 0, v = 0; i < count; ++i, (i % H == 0) ? (++v, h = 0) : (++h))
        {
            x = marginLeft + h * edgeSquare;
            y = topMargin + v * edgeSquare + 15;
            switch ((*player)[i]->getType())
            {
            case L_FIGURE_KING: this->drawKing(color, x, y); break;
            case L_FIGURE_QUEEN: this->drawQueen(color, x, y); break;
            case L_FIGURE_ELEPHANT: this->drawElephant(color, x, y); break;
            case L_FIGURE_HORSE: this->drawHorse(color, x, y); break;
            case L_FIGURE_ROOK: this->drawRook(color, x, y); break;
            case L_FIGURE_PAWN: this->drawPawn(color, x, y); break;
            }
        }
    }
}

void LDesk::drawMarkup(bool areWhiteActive)
{
    QPainter painter;
    painter.begin(this);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(13, 19, 23));

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(227, 227, 227));

    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawRect(
        leftMargin - L_PADDING_BOARD,
        topMargin - L_PADDING_BOARD,
        edgeBoard + 2 * L_PADDING_BOARD,
        edgeBoard + 2 * L_PADDING_BOARD
    );

    int x = leftMargin + edgeSquare * 0.5;
    int y = topMargin - 5;

    QString markup = " ";

    for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
    {
        markup[0] = (areWhiteActive) ? ('A' + i) : ('H' - i);
        painter.drawText(x + i * edgeSquare, y, markup);
    }

    y += edgeBoard + 20;

    for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
    {
        markup[0] = (areWhiteActive) ? ('A' + i) : ('H' - i);
        painter.drawText(x + i * edgeSquare, y, markup);
    }

    x = leftMargin - 15;
    y = topMargin + edgeSquare * 0.5;

    for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
    {
        markup[0] = (areWhiteActive) ? ('8' - i) : ('1' + i);
        painter.drawText(x, y + i * edgeSquare, markup);
    }

    x += edgeBoard + 25;

    for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
    {
        markup[0] = (areWhiteActive) ? ('8' - i) : ('1' + i);
        painter.drawText(x, y + i * edgeSquare, markup);
    }

    painter.end();
}

void LDesk::drawSquare(LSquare* position, bool areWhiteActive)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (!areWhiteActive)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    int x = h * edgeSquare + leftMargin;
    int y = v * edgeSquare + topMargin;
    int state = position->getState();
    int color = position->getColor();

    QPainter painter;
    QBrush brush;
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    painter.begin(this);

    if (color == L_COLOR_WHITE)
    {
        brush.setColor(QColor(255, 255, 255));
    }
    else
    {
        brush.setColor(QColor(217, 222, 224));
    }

    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

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

void LDesk::calculateForDrawFigure(int& x, int& y, LSquare* position, bool areWhiteActive)
{
    int h = position->getHorizontal();
    int v = position->getVertical();

    if (!areWhiteActive)
    {
        h = L_CHESS_BOARD_SIZE - 1 - h;
        v = L_CHESS_BOARD_SIZE - 1 - v;
    }

    x = h * edgeSquare + leftMargin;
    y = v * edgeSquare + topMargin;
}

void LDesk::drawKing(int color, LSquare* position, bool areWhiteActive)
{
    int x, y;
    this->calculateForDrawFigure(x, y, position, areWhiteActive);
    this->drawKing(color, x, y);
}

void LDesk::drawQueen(int color, LSquare* position, bool areWhiteActive)
{
    int x, y;
    this->calculateForDrawFigure(x, y, position, areWhiteActive);
    this->drawQueen(color, x, y);
}

void LDesk::drawElephant(int color, LSquare* position, bool areWhiteActive)
{
    int x, y;
    this->calculateForDrawFigure(x, y, position, areWhiteActive);
    this->drawElephant(color, x, y);
}

void LDesk::drawHorse(int color, LSquare* position, bool areWhiteActive)
{
    int x, y;
    this->calculateForDrawFigure(x, y, position, areWhiteActive);
    this->drawHorse(color, x, y);
}

void LDesk::drawRook(int color, LSquare* position, bool areWhiteActive)
{
    int x, y;
    this->calculateForDrawFigure(x, y, position, areWhiteActive);
    this->drawRook(color, x, y);
}

void LDesk::drawPawn(int color, LSquare* position, bool areWhiteActive)
{
    int x, y;
    this->calculateForDrawFigure(x, y, position, areWhiteActive);
    this->drawPawn(color, x, y);
}

void LDesk::drawKing(int color, int x, int y)
{
    QString file = (color == L_COLOR_WHITE) ? ":/LWKing.png" : ":/LBKing.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawQueen(int color, int x, int y)
{
    QString file = (color == L_COLOR_WHITE) ? ":/LWQueen.png" : ":/LBQueen.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawElephant(int color, int x, int y)
{
    QString file = (color == L_COLOR_WHITE) ? ":/LWElephant.png" : ":/LBElephant.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawHorse(int color, int x, int y)
{
    QString file = (color == L_COLOR_WHITE) ? ":/LWHorse.png" : ":/LBHorse.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawRook(int color, int x, int y)
{
    QString file = (color == L_COLOR_WHITE) ? ":/LWRook.png" : ":/LBRook.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}

void LDesk::drawPawn(int color, int x, int y)
{
    QString file = (color == L_COLOR_WHITE) ? ":/LWPawn.png" : ":/LBPawn.png";
    QImage image = QImage(file).scaled(edgeSquare, edgeSquare, Qt::IgnoreAspectRatio);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(x, y, image);
    painter.end();
}
