#include "LGame.h"

#include "LConst.h"
#include "LNewGame.h"

#include "LBiGame.h"
#include "LBotGame.h"
#include "LNetGame.h"

#include "LConst.h"
#include "LMainWidget.h"
#include "LTransformation.h"
#include "LDesk.h"
#include "LSquare.h"

#include "LPlayer.h"

#include "LFigure.h"
#include "LKing.h"
#include "LQueen.h"
#include "LElephant.h"
#include "LHorse.h"
#include "LRook.h"
#include "LPawn.h"

LGame* LGame::instance = nullptr;

LGame::LGame()
	:
	gameInstance(L_GAME_RUNNING),
	areWhiteActive(true),
	_isCheck(0),
	squares(new LSquare** [L_CHESS_BOARD_SIZE]),
	figures(new LFigure** [L_CHESS_BOARD_SIZE]),
	activeSquare(nullptr),
	activeFigure(nullptr),
	focusedSquare(nullptr)
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		this->squares[i] = new LSquare * [L_CHESS_BOARD_SIZE];
		this->figures[i] = new LFigure * [L_CHESS_BOARD_SIZE];
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			int color = (i + j) % 2 + L_COLOR_WHITE;
			this->squares[i][j] = new LSquare(i, j, color);
			this->figures[i][j] = nullptr;
		}
	}

	this->setFigure(0, 4, new LKing(L_COLOR_BLACK));
	this->setFigure(0, 3, new LQueen(L_COLOR_BLACK));
	this->setFigure(0, 2, new LElephant(L_COLOR_BLACK));
	this->setFigure(0, 5, new LElephant(L_COLOR_BLACK));
	this->setFigure(0, 1, new LHorse(L_COLOR_BLACK));
	this->setFigure(0, 6, new LHorse(L_COLOR_BLACK));
	this->setFigure(0, 0, new LRook(L_COLOR_BLACK));
	this->setFigure(0, 7, new LRook(L_COLOR_BLACK));
	this->setFigure(1, 0, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 1, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 2, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 3, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 4, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 5, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 6, new LPawn(L_COLOR_BLACK));
	this->setFigure(1, 7, new LPawn(L_COLOR_BLACK));

	this->setFigure(7, 4, new LKing(L_COLOR_WHITE));
	this->setFigure(7, 3, new LQueen(L_COLOR_WHITE));
	this->setFigure(7, 2, new LElephant(L_COLOR_WHITE));
	this->setFigure(7, 5, new LElephant(L_COLOR_WHITE));
	this->setFigure(7, 1, new LHorse(L_COLOR_WHITE));
	this->setFigure(7, 6, new LHorse(L_COLOR_WHITE));
	this->setFigure(7, 0, new LRook(L_COLOR_WHITE));
	this->setFigure(7, 7, new LRook(L_COLOR_WHITE));
	this->setFigure(6, 0, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 1, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 2, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 3, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 4, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 5, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 6, new LPawn(L_COLOR_WHITE));
	this->setFigure(6, 7, new LPawn(L_COLOR_WHITE));
}

LGame* LGame::getInstance()
{
	return instance;
}

int LGame::getGameInstance() const
{
	return this->gameInstance;
}

void LGame::changeGameInstance(int gameInstance)
{
	this->gameInstance = gameInstance;
}

void LGame::newGame(LNewGame* dialog)
{
	int gameType = dialog->getGameType();
	int color = dialog->getColor();
	QString name1 = dialog->getName1();
	QString name2 = dialog->getName2();

	if (instance)
	{
		instance->clear();
		instance = nullptr;
	}

	switch (gameType)
	{
	case L_TYPE_BI:
		instance = new LBiGame(name1, name2, color);
		break;
	case L_TYPE_BOT:
		instance = new LBotGame(color);
		break;
	case L_TYPE_NET:
		instance = new LNetGame(color);
		break;
	}
}

LFigure* LGame::getFigure(int v, int h)
{
	if (v < 0 || v >= L_CHESS_BOARD_SIZE || h < 0 || h >= L_CHESS_BOARD_SIZE)
		return nullptr;

	return this->figures[v][h];
}

void LGame::draw()
{
	LDesk* desk = LDesk::getInstance();

	desk->drawTablePlayer(this->playerWhite, this->areWhiteActive);
	desk->drawTablePlayer(this->playerBlack, this->areWhiteActive);

	desk->drawMarkup(areWhiteActive);

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->squares[i][j]->draw(areWhiteActive);
		}
	}

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (this->figures[i][j])
			{
				this->figures[i][j]->draw(this->squares[i][j], areWhiteActive);
			}
		}
	}
}

int LGame::isCheck(int color)
{
	int v, h;
	bool flag;

	for (v = 0, h = 0, flag = false; !flag && v != 8; (h == 7) ? (h = 0, ++v) : (++h))
	{
		flag = this->figures[v][h] && (this->figures[v][h]->getType() == L_FIGURE_KING) && (this->figures[v][h]->getColor() == color);
	}

	(h == 0) ? ((v > 0) ? (h = 7, --v) : (--h)) : (--h);

	if (v == 8)
	{
		return L_PATH_FALSE;
	}

	for (int y = 0; y < L_CHESS_BOARD_SIZE; y++)
	{
		for (int x = 0; x < L_CHESS_BOARD_SIZE; x++)
		{
			if (!(y == v && x == h) &&
				this->figures[y][x] &&
				this->figures[y][x]->getColor() != color &&
				(this->figures[y][x]->isPossiblePosition(this->squares[y][x], this->squares[v][h]) & L_PATH_TRUE))
			{
				return color | L_PATH_CHECK;
			}
		}
	}

	return L_PATH_FALSE;
}

int LGame::isCheck(int color, int v, int h, int vK, int hK)
{
	LFigure* temp;

	if (vK != -1)
	{
		temp = this->figures[v][h];
		this->figures[v][h] = this->figures[vK][hK];
		this->figures[vK][hK] = nullptr;
	}
	else
	{
		temp = this->figures[v][h];
		this->figures[v][h] = nullptr;
	}

	int response = this->isCheck(color);

	if (vK != -1)
	{
		this->figures[vK][hK] = this->figures[v][h];
		this->figures[v][h] = temp;
	}
	else
	{
		this->figures[v][h] = temp;
	}

	return response;
}

int LGame::getIsCheck() const
{
	return this->_isCheck;
}

int LGame::isMat(int color)
{
	int v, h;
	bool flag;

	for (v = 0, h = 0, flag = false; !flag && v != 8; (h == 7) ? (h = 0, ++v) : (++h))
	{
		flag = this->figures[v][h] && (this->figures[v][h]->getType() == L_FIGURE_KING) && (this->figures[v][h]->getColor() == color);
	}

	(h == 0) ? ((v > 0) ? (h = 7, --v) : (--h)) : (--h);

	bool (*func)(LGame * game, int sV, int sH, int fV, int fH) = [](LGame* game, int sV, int sH, int fV, int fH)
	{
		return ((fV >= 0) &&
			(fV < L_CHESS_BOARD_SIZE) &&
			(fH >= 0) &&
			(fH < L_CHESS_BOARD_SIZE) &&
			(game->figures[sV][sH]->isPossiblePosition(game->squares[sV][sH], game->squares[fV][fH]) & L_PATH_TRUE));
	};

	bool result[8];

	result[0] = func(this, v, h, v, h + 1);
	result[1] = func(this, v, h, v + 1, h + 1);
	result[2] = func(this, v, h, v + 1, h);
	result[3] = func(this, v, h, v + 1, h - 1);
	result[4] = func(this, v, h, v, h - 1);
	result[5] = func(this, v, h, v - 1, h - 1);
	result[6] = func(this, v, h, v - 1, h);
	result[7] = func(this, v, h, v - 1, h + 1);

	if (!(result[0] || result[1] || result[2] || result[3] || result[4] || result[5] || result[6] || result[7]))
	{
		return L_PATH_MAT;
	}
	else
	{
		return L_PATH_TRUE;
	}
}

bool LGame::isPat(int color)
{
	bool flag = false;

	bool result[8];

	bool (*func)(LGame * game, int sV, int sH, int fV, int fH) = [](LGame* game, int sV, int sH, int fV, int fH)
	{
		return ((fV >= 0) &&
			(fV < L_CHESS_BOARD_SIZE) &&
			(fH >= 0) &&
			(fH < L_CHESS_BOARD_SIZE) &&
			(game->figures[sV][sH]->isPossiblePosition(game->squares[sV][sH], game->squares[fV][fH]) & L_PATH_TRUE));
	};

	for (int i = 0; i < L_CHESS_BOARD_SIZE && !flag; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE && !flag; j++)
		{
			if (this->figures[j][i] && this->figures[j][i]->getColor() == color)
			{
				switch (this->figures[j][i]->getType())
				{
				case L_FIGURE_KING:
				case L_FIGURE_QUEEN:
				case L_FIGURE_ELEPHANT:
				{
					result[0] = func(this, j, i, j + 1, i + 1);
					result[1] = func(this, j, i, j + 1, i - 1);
					result[2] = func(this, j, i, j - 1, i - 1);
					result[3] = func(this, j, i, j - 1, i + 1);

					flag = result[0] || result[1] || result[2] || result[3];

					if (this->figures[j][i]->getType() == L_FIGURE_ELEPHANT)
					{
						break;
					}
				}
				case L_FIGURE_ROOK:
				{
					result[4] = func(this, j, i, j, i + 1);
					result[5] = func(this, j, i, j, i - 1);
					result[6] = func(this, j, i, j + 1, i);
					result[7] = func(this, j, i, j - 1, i);

					if (this->figures[j][i]->getType() == L_FIGURE_ROOK)
					{
						flag = result[4] || result[5] || result[6] || result[7];
						break;
					}
					else
					{
						flag = flag || result[4] || result[5] || result[6] || result[7];
						break;
					}
				}
				case L_FIGURE_HORSE:
				{
					result[0] = func(this, j, i, j + 1, i + 2);
					result[1] = func(this, j, i, j + 1, i - 2);
					result[2] = func(this, j, i, j - 1, i - 2);
					result[3] = func(this, j, i, j - 1, i + 2);
					result[4] = func(this, j, i, j + 2, i + 1);
					result[5] = func(this, j, i, j + 2, i - 1);
					result[6] = func(this, j, i, j - 2, i - 1);
					result[7] = func(this, j, i, j - 2, i + 1);

					flag = result[0] || result[1] || result[2] || result[3] || result[4] || result[5] || result[6] || result[7];

					break;
				}
				case L_FIGURE_PAWN:
				{
					result[0] = func(this, j, i, j + 1, i);
					result[1] = func(this, j, i, j - 1, i);
					result[2] = func(this, j, i, j + 1, i + 1);
					result[3] = func(this, j, i, j + 1, i - 1);
					result[4] = func(this, j, i, j - 1, i - 1);
					result[5] = func(this, j, i, j - 1, i + 1);

					flag = result[0] || result[1] || result[2] || result[3] || result[4] || result[5];

					break;
				}
				}
			}
		}
	}

	return !flag;
}

void LGame::mousePress(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_FINISH))
	{
		if (!this->areWhiteActive)
		{
			v = L_CHESS_BOARD_SIZE - 1 - v;
			h = L_CHESS_BOARD_SIZE - 1 - h;
		}

		this->activeSquare = this->squares[v][h];
		this->activeFigure = this->figures[v][h];

		this->activeSquare->setState(L_SQUARE_SELECTED);
	}
}

void LGame::mouseRelease(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_FINISH))
	{
		if (
			(this->areWhiteActive && this->activeFigure && this->activeFigure->getColor() != L_COLOR_WHITE)
			||
			(!this->areWhiteActive && this->activeFigure && this->activeFigure->getColor() == L_COLOR_WHITE)
			)
		{
			this->activeSquare = nullptr;
			this->activeFigure = nullptr;
			return;
		}

		if (!this->areWhiteActive)
		{
			v = L_CHESS_BOARD_SIZE - 1 - v;
			h = L_CHESS_BOARD_SIZE - 1 - h;
		}

		if (this->activeFigure)
		{
			int response = this->activeFigure->isPossiblePosition(activeSquare, this->squares[v][h]);
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
}

void LGame::mouseMotionMove(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_FINISH))
	{
		/*this->focusedSquare->setState(L_SQUARE_NATIVE);
		this->focusedSquare = this->squares[v][h];
		this->focusedSquare->setState(L_SQUARE_FOCUSED);*/
	}
}

void LGame::mouseMove(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_FINISH))
	{
		/**this->focusedSquare->setState(L_SQUARE_NATIVE);
		this->focusedSquare = this->squares[v][h];
		this->focusedSquare->setState(L_SQUARE_FOCUSED);*/
	}
}

void LGame::setFigure(int v, int h, LFigure* figure)
{
	this->figures[v][h] = figure;
}

void LGame::actionAfterPath()
{
	
}

void LGame::clear()
{
	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			delete this->squares[i][j];
			if (this->figures[i][j])
				delete this->figures[i][j];
		}
		delete[] this->squares[i];
		delete[] this->figures[i];
	}
	delete[] this->squares;
	delete[] this->figures;
}
