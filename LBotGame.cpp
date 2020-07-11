#include "LBotGame.h"

#include "LMainWidget.h"
#include "LTransformation.h"

#include "LFigure.h"
#include "LPlayer.h"
#include "LOptions.h"

#include <QVector>

#include "LKing.h"
#include "LQueen.h"
#include "LElephant.h"
#include "LHorse.h"
#include "LRook.h"

LBotGame::LBotGame(int c)
	:
	LGame(),
	myColor((c == L_COLOR_ANY) ? ((rand() % 2) ? L_COLOR_WHITE : L_COLOR_BLACK) : (c))
{
	QString n1 = LOptions::getInstance()->getName();
	QString n2 = "Computer";

	this->playerWhite = new LPlayer(
		L_COLOR_WHITE,
		(this->myColor == L_COLOR_WHITE ? n1 : n2)
	);

	this->playerBlack = new LPlayer(
		L_COLOR_BLACK,
		(this->myColor == L_COLOR_WHITE ? n2 : n1)
	);

	this->areWhiteActive = this->myColor == L_COLOR_WHITE;
	this->isBlocked = !this->areWhiteActive;

	if (this->isBlocked)
	{
		this->actionAfterPath();
	}
}

void LBotGame::draw()
{
	LGame::draw();
}

void LBotGame::mousePress(int vertical, int horizontal)
{
	LGame::mousePress(vertical, horizontal);
}

void LBotGame::mouseRelease(int vertical, int horizontal)
{
	if (!this->isBlocked)
	{
		LGame::mouseRelease(vertical, horizontal);
	}

	if (this->activeSquare)
	{
		this->activeSquare->setState(L_SQUARE_NATIVE);
		this->activeSquare = nullptr;
		this->activeFigure = nullptr;
	}
}

void LBotGame::mouseMotionMove(int vertical, int horizontal)
{
	LGame::mouseMotionMove(vertical, horizontal);
}

void LBotGame::mouseMove(int vertical, int horizontal)
{
	LGame::mouseMove(vertical, horizontal);
}

void LBotGame::actionAfterPath()
{
	this->setBlocked(true);
	this->waitBot();
	this->setBlocked(false);
}

void LBotGame::setBlocked(bool block)
{
	this->isBlocked = block;
}

void LBotGame::waitBot()
{
	this->completeMove();
}

QVector<LPath> LBotGame::uglyMoves()
{
	QVector<LPath> paths;

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (this->figures[i][j] && this->figures[i][j]->getColor() != this->myColor)
			{
				for (int k = 0; k < L_CHESS_BOARD_SIZE; k++)
				{
					for (int l = 0; l < L_CHESS_BOARD_SIZE; l++)
					{
						int result = this->figures[i][j]->isPossiblePosition(this->squares[i][j], this->squares[k][l]);

						if (result & L_PATH_TRUE)
						{
							paths.push_back(LPath{ this->squares[i][j], this->squares[k][l], result });
						}
					}
				}
			}
		}
	}

	return paths;
}

LPath LBotGame::calculateBestMove()
{
	QVector<LPath> paths = this->uglyMoves();
	return paths[rand() % paths.size()];
}

void LBotGame::completeMove()
{
	LMainWidget* mainWidget = LMainWidget::getInstance();

	LPath path = this->calculateBestMove();

	int fv = path.from->getVertical();
	int fh = path.from->getVertical();
	int v = path.to->getVertical();
	int h = path.to->getVertical();

	/*fv = L_CHESS_BOARD_SIZE - 1 - fv;
	fh = L_CHESS_BOARD_SIZE - 1 - fh;
	v = L_CHESS_BOARD_SIZE - 1 - v;
	h = L_CHESS_BOARD_SIZE - 1 - h;*/

	int color = (this->playerWhite->getName() == LOptions::getInstance()->getName()) ? L_COLOR_WHITE : L_COLOR_BLACK;

	QString name = (color == L_COLOR_WHITE) ? this->playerWhite->getName() : this->playerBlack->getName();

	if (this->figures[v][h])
	{
		if (color == L_COLOR_WHITE)
		{
			this->playerBlack->addFigure(this->figures[v][h]);
		}
		else
		{
			this->playerWhite->addFigure(this->figures[v][h]);
		}
	}

	this->figures[v][h] = this->figures[fv][fh];
	this->figures[fv][fh] = nullptr;

	if (path.result & L_PATH_CASTLING)
	{
		LGame* game = LGame::getInstance();

		if (h - fh == 2)
		{
			LRook* rook = (LRook*)this->figures[v][h + 1];

			if (!rook)
			{
				rook = (LRook*)this->figures[v][h + 2];
				this->figures[v][h + 2] = nullptr;
			}
			else
			{
				this->figures[v][h + 1] = nullptr;
			}

			this->figures[v][h - 1] = rook;
		}
		else
		{
			LRook* rook = (LRook*)this->figures[v][h - 1];

			if (!rook)
			{
				rook = (LRook*)this->figures[v][h - 2];
				this->figures[v][h - 2] = nullptr;
			}
			else
			{
				this->figures[v][h - 1] = nullptr;
			}

			this->figures[v][h + 1] = rook;
		}

		mainWidget->pathListAppend(name + ": Castling");
	}

	if (path.result & L_PATH_TRANSFORMATION)
	{
		delete this->figures[v][h];
		this->figures[v][h] = new LQueen(color);
	}
}

void LBotGame::completeMove(LPath path)
{
	if (!(this->getGameInstance() & L_GAME_FINISH))
	{
		int v = path.to->getVertical();
		int h = path.to->getHorizontal();

		int response = this->activeFigure->isPossiblePosition(path.from, path.to);
		QString name = (this->areWhiteActive) ? (this->playerWhite->getName()) : (this->playerBlack->getName());
		LMainWidget* mainWidget = LMainWidget::getInstance();

		if (response & L_PATH_TRUE)
		{
			QString actFig = this->activeFigure->getName();
			QString pasFig = (this->figures[v][h]) ? (" (" + this->figures[v][h]->getName() + ")") : ("");

			if (this->figures[v][h])
			{
				if (this->areWhiteActive)
				{
					this->playerWhite->addFigure(this->figures[v][h]);
				}
				else
				{
					this->playerBlack->addFigure(this->figures[v][h]);
				}
			}

			this->figures[v][h] = this->activeFigure;
			this->figures[this->activeSquare->getVertical()][this->activeSquare->getHorizontal()] = nullptr;

			QString node = name + ": " + actFig + " " +
				('A' + activeSquare->getHorizontal()) + ('1' + activeSquare->getVertical()) + " - " +
				('A' + this->squares[v][h]->getHorizontal()) + ('1' + this->squares[v][h]->getVertical()) + pasFig;

			mainWidget->pathListAppend(node);
		}

		if (response & L_PATH_CASTLING)
		{
			LGame* game = LGame::getInstance();
			int _h = this->activeSquare->getHorizontal();

			if (h - _h == 2)
			{
				LRook* rook = (LRook*)this->figures[v][h + 1];

				if (!rook)
				{
					rook = (LRook*)this->figures[v][h + 2];
					this->figures[v][h + 2] = nullptr;
				}
				else
				{
					this->figures[v][h + 1] = nullptr;
				}

				this->figures[v][h - 1] = rook;
			}
			else
			{
				LRook* rook = (LRook*)this->figures[v][h - 1];

				if (!rook)
				{
					rook = (LRook*)this->figures[v][h - 2];
					this->figures[v][h - 2] = nullptr;
				}
				else
				{
					this->figures[v][h - 1] = nullptr;
				}

				this->figures[v][h + 1] = rook;
			}

			mainWidget->pathListAppend(name + ": Castling");
		}

		if (response & L_PATH_TRANSFORMATION)
		{
			LTransformation* dialog = new LTransformation;

			if (dialog->exec() == QDialog::Accepted)
			{
				QString name = (this->areWhiteActive) ? (this->playerWhite->getName()) : (this->playerBlack->getName());
				QString newFigure;

				LFigure* temp = this->figures[v][h];

				switch (dialog->getFigure())
				{
				case L_FIGURE_QUEEN:
					newFigure = "Queen";
					this->figures[v][h] = new LQueen(this->figures[v][h]->getColor());
					break;
				case L_FIGURE_ELEPHANT:
					newFigure = "Elephant";
					this->figures[v][h] = new LElephant(this->figures[v][h]->getColor());
					break;
				case L_FIGURE_HORSE:
					newFigure = "Horse";
					this->figures[v][h] = new LHorse(this->figures[v][h]->getColor());
					break;
				case L_FIGURE_ROOK:
					newFigure = "Rook";
					this->figures[v][h] = new LRook(this->figures[v][h]->getColor());
					break;
				}

				QString node = name + ": Pawn to " + newFigure;
				mainWidget->pathListAppend(node);

				delete temp;
			}

			delete dialog;
		}

		if (response & L_PATH_TRUE)
		{
			if (this->_isCheck = this->isCheck(L_COLOR_WHITE) | this->isCheck(L_COLOR_BLACK))
			{
				QString node;

				if (this->_isCheck & L_COLOR_WHITE)
				{
					node = this->playerBlack->getName() + " check " + this->playerWhite->getName();
					mainWidget->pathListAppend(node);

					if (this->isMat(L_COLOR_WHITE) & L_PATH_MAT)
					{
						node = this->playerBlack->getName() + "win!\n";
						node += this->playerBlack->getName() + " mat " + this->playerWhite->getName();
						mainWidget->pathListAppend(node);
						mainWidget->messageAlert(node);
						this->changeGameInstance(L_GAME_FINISH | L_COLOR_WHITE);
					}
					else
					{
						mainWidget->messageAlert(node);
					}
				}

				if (this->_isCheck & L_COLOR_BLACK)
				{
					node = this->playerWhite->getName() + " check " + this->playerBlack->getName();
					mainWidget->pathListAppend(node);

					if (this->isMat(L_COLOR_BLACK) & L_PATH_MAT)
					{
						node = this->playerWhite->getName() + " win!\n";
						node += this->playerWhite->getName() + " mat " + this->playerBlack->getName();
						mainWidget->pathListAppend(node);
						mainWidget->messageAlert(node);
						this->changeGameInstance(L_GAME_FINISH | L_COLOR_BLACK);
					}
					else
					{
						mainWidget->messageAlert(node);
					}
				}
			}

			else if (this->isPat(L_COLOR_WHITE) || this->isPat(L_COLOR_BLACK))
			{
				QString node = "Dead Heat!\nStalemate situation.";
				mainWidget->pathListAppend(node);
				mainWidget->messageAlert(node);
				this->changeGameInstance(L_GAME_FINISH | L_PATH_PAT);
			}

			this->actionAfterPath();
		}
	}
}

void LBotGame::clear()
{
	LGame::clear();
}
