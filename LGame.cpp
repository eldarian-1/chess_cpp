#include "LGame.h"

#include "LConst.h"
#include "LNewGame.h"

#include "LBiGame.h"
#include "LBotGame.h"
#include "LNetGame.h"

#include "LBeginBot.h"
#include "LWeakBot.h"
#include "LAverageBot.h"
#include "LStrongBot.h"

#include "LConst.h"
#include "LMainWidget.h"
#include "LTransformation.h"
#include "LDesk.h"
#include "LPath.h"
#include "LBoard.h"
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
	board(nullptr),
	activeSquare(nullptr),
	activeFigure(nullptr),
	focusedSquare(nullptr),
	playerWhite(nullptr),
	playerBlack(nullptr)
{
	
}

LGame::~LGame()
{
	this->clear();
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
	int botPower = dialog->getBotPower();

	QString name1 = dialog->getName1();
	QString name2 = dialog->getName2();

	int color = dialog->getColor();

	color = (color == L_COLOR_ANY) ? (rand() % 2 + L_COLOR_WHITE) : color;

	if (instance)
	{
		instance->clear();
		instance = nullptr;
	}

	switch (gameType)
	{
	case L_TYPE_BI:
	{
		instance = new LBiGame(name1, name2, color);
		break;
	}
	case L_TYPE_BOT:
	{
		switch (botPower)
		{
		case L_BOT_BEGIN:
		{
			instance = new LBeginBot(color);
			break;
		}
		case L_BOT_WEAK:
		{
			instance = new LWeakBot(color);
			break;
		}
		case L_BOT_AVERAGE:
		{
			instance = new LAverageBot(color);
			break;
		}
		case L_BOT_STRONG:
		{
			instance = new LStrongBot(color);
			break;
		}
		}
		break;
	}
	case L_TYPE_NET:
	{
		instance = new LNetGame;
		break;
	}
	}

	instance->board = new LBoard;
	instance->board->setFigures();

	if (gameType == L_TYPE_BOT && color == L_COLOR_BLACK)
	{
		instance->actionAfterPath(nullptr);
	}
}

void LGame::setGame(LGame* game)
{
	instance = game;

	LMainWidget::getInstance()
		->setPathList(
			instance->playerWhite->getName() + " vs " + instance->playerBlack->getName()
		);
}

void LGame::loadGame(int typeOfGame, int typeOfBot)
{
	if (instance)
	{
		delete instance;
	}

	switch (typeOfGame)
	{

	case L_TYPE_BI:
		instance = new LBiGame;
		break;

	case L_TYPE_BOT:
		switch (typeOfBot)
		{

		case L_BOT_BEGIN:
			instance = new LBeginBot;
			break;

		case L_BOT_WEAK:
			instance = new LWeakBot;
			break;

		case L_BOT_AVERAGE:
			instance = new LAverageBot;
			break;

		case L_BOT_STRONG:
			instance = new LStrongBot;
			break;

		}
		break;

	}

	instance->board = new LBoard;
	instance->playerWhite = new LPlayer(L_COLOR_WHITE);
	instance->playerBlack = new LPlayer(L_COLOR_BLACK);
}

LFigure* LGame::getFigure(int v, int h)
{
	if (v < 0 || v >= L_CHESS_BOARD_SIZE || h < 0 || h >= L_CHESS_BOARD_SIZE)
		return nullptr;

	return this->board->getFigure(v, h);
}

LSquare*& LGame::getSquare(int v, int h)
{
	return this->board->getSquare(v, h);
}

void LGame::draw()
{
	LDesk* desk = LDesk::getInstance();

	if (this->playerWhite && this->playerBlack)
	{
		desk->drawTablePlayer(this->playerWhite, this->areWhiteActive);
		desk->drawTablePlayer(this->playerBlack, this->areWhiteActive);
	}

	desk->drawMarkup(areWhiteActive);

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			this->board->getSquare(i, j)->draw(areWhiteActive);
		}
	}

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (this->board->getFigure(i, j))
			{
				this->board->getFigure(i, j)->draw(this->board->getSquare(i, j), areWhiteActive);
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
		flag = this->board->getFigure(v, h) &&
			(this->board->getFigure(v, h)->getType() == L_FIGURE_KING) &&
			(this->board->getFigure(v, h)->getColor() == color);
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
			LPath* path = new LPath(this->board->getSquare(y, x), this->board->getSquare(v, h));

			if (!(y == v && x == h) &&
				this->board->getFigure(y, x) &&
				this->board->getFigure(y, x)->getColor() != color &&
				this->board->getFigure(y, x)->isPossiblePath(path) & L_PATH_TRUE)
			{

				return color | L_PATH_CHECK;
			}

			delete path;
		}
	}

	return L_PATH_FALSE;
}

int LGame::isCheck(int color, int v, int h, int vK, int hK)
{
	LFigure* temp;

	if (vK != -1)
	{
		temp = this->board->getFigure(v, h);
		this->board->getFigure(v, h) = this->board->getFigure(vK, hK);
		this->board->getFigure(vK, hK) = nullptr;
	}
	else
	{
		temp = this->board->getFigure(v, h);
		this->board->getFigure(v, h) = nullptr;
	}

	int response = this->isCheck(color);

	if (vK != -1)
	{
		this->board->getFigure(vK, hK) = this->board->getFigure(v, h);
		this->board->getFigure(v, h) = temp;
	}
	else
	{
		this->board->getFigure(v, h) = temp;
	}

	return response;
}

int LGame::getIsCheck() const
{
	return this->_isCheck;
}

int LGame::isMat(int color)
{
	bool flag = false;

	for (int i = 0; i < L_CHESS_BOARD_SIZE && !flag; ++i)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE && !flag; ++j)
		{
			if (this->board->getFigure(i, j) && this->board->getFigure(i, j)->getColor() == color)
			{
				for (int k = 0; k < L_CHESS_BOARD_SIZE && !flag; ++k)
				{
					for (int l = 0; l < L_CHESS_BOARD_SIZE && !flag; ++l)
					{
						if (!this->board->getFigure(k, l) || this->board->getFigure(k, l)->getColor() != color)
						{
							LPath* path = new LPath(this->board->getSquare(i, j), this->board->getSquare(k, l));

							flag = !(i == k && j == l) && (this->board->getFigure(i, j)->isPossiblePath(path) & L_PATH_TRUE);

							delete path;
						}
					}
				}
			}
		}
	}

	return (!flag ? L_PATH_MAT : L_PATH_TRUE);
}

bool LGame::isPat(int color)
{
	bool flag = false;

	bool result[8];

	bool (*func)(LGame * game, int sV, int sH, int fV, int fH) = [](LGame* game, int sV, int sH, int fV, int fH)
	{
		LPath* path = new LPath(game->board->getSquare(sV, sH), game->board->getSquare(fV, fH));

		bool result = ((fV >= 0) &&
			(fV < L_CHESS_BOARD_SIZE) &&
			(fH >= 0) &&
			(fH < L_CHESS_BOARD_SIZE) &&
			(game->board->getFigure(sV, sH)->isPossiblePath(path) & L_PATH_TRUE));

		delete path;

		return result;
	};

	for (int i = 0; i < L_CHESS_BOARD_SIZE && !flag; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE && !flag; j++)
		{
			if (this->board->getFigure(i, j) && this->board->getFigure(i, j)->getColor() == color)
			{
				switch (this->board->getFigure(i, j)->getType())
				{
				case L_FIGURE_KING:
				case L_FIGURE_QUEEN:
				case L_FIGURE_ELEPHANT:
				{
					result[0] = func(this, i, j, i + 1, j + 1);
					result[1] = func(this, i, j, i + 1, j - 1);
					result[2] = func(this, i, j, i - 1, j - 1);
					result[3] = func(this, i, j, i - 1, j + 1);

					flag = result[0] || result[1] || result[2] || result[3];

					if (this->board->getFigure(i, j)->getType() == L_FIGURE_ELEPHANT)
					{
						break;
					}
				}
				case L_FIGURE_ROOK:
				{
					result[4] = func(this, i, j, i, j + 1);
					result[5] = func(this, i, j, i, j - 1);
					result[6] = func(this, i, j, i + 1, j);
					result[7] = func(this, i, j, i - 1, j);

					if (this->board->getFigure(i, j)->getType() == L_FIGURE_ROOK)
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
					result[0] = func(this, i, j, i + 1, j + 2);
					result[1] = func(this, i, j, i + 1, j - 2);
					result[2] = func(this, i, j, i - 1, j - 2);
					result[3] = func(this, i, j, i - 1, j + 2);
					result[4] = func(this, i, j, i + 2, j + 1);
					result[5] = func(this, i, j, i + 2, j - 1);
					result[6] = func(this, i, j, i - 2, j - 1);
					result[7] = func(this, i, j, i - 2, j + 1);

					flag = result[0] || result[1] || result[2] || result[3] || result[4] || result[5] || result[6] || result[7];

					break;
				}
				case L_FIGURE_PAWN:
				{
					result[0] = func(this, i, j, i + 1, j);
					result[1] = func(this, i, j, i - 1, j);
					result[2] = func(this, i, j, i + 1, j + 1);
					result[3] = func(this, i, j, i + 1, j - 1);
					result[4] = func(this, i, j, i - 1, j - 1);
					result[5] = func(this, i, j, i - 1, j + 1);

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
	if (!(this->getGameInstance() & L_GAME_PAUSE))
	{
		if (!this->areWhiteActive)
		{
			v = L_CHESS_BOARD_SIZE - 1 - v;
			h = L_CHESS_BOARD_SIZE - 1 - h;
		}

		this->activeSquare = this->board->getSquare(v, h);
		this->activeFigure = this->board->getFigure(v, h);

		this->activeSquare->setState(L_SQUARE_SELECTED);
	}
}

void LGame::mouseRelease(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_PAUSE))
	{
		if (!(
			(this->areWhiteActive && this->activeFigure && this->activeFigure->getColor() != L_COLOR_WHITE)
			||
			(!this->areWhiteActive && this->activeFigure && this->activeFigure->getColor() == L_COLOR_WHITE)
			))
		{

			if (!this->areWhiteActive)
			{
				v = L_CHESS_BOARD_SIZE - 1 - v;
				h = L_CHESS_BOARD_SIZE - 1 - h;
			}

			if (this->activeFigure)
			{
				LPlayer* act = this->areWhiteActive ? this->playerWhite : this->playerBlack;
				LPlayer* pass = this->areWhiteActive ? this->playerBlack : this->playerWhite;
				LSquare*& from = this->board->getSquare(this->activeSquare->getVertical(), this->activeSquare->getHorizontal());
				LSquare*& to = this->board->getSquare(v, h);
				LPath* path = new LPath(act->getClone(), pass->getClone(), from, to);

				int isPossible = this->activeFigure->isPossiblePath(path);

				if (isPossible & L_PATH_TRUE)
				{
					path->setPossible(isPossible);
					this->completeMove(path);
					this->actionAfterPath(path);
				}

				delete path;
			}

		}

		this->activeSquare->setState(L_SQUARE_NATIVE);

		this->activeSquare = nullptr;
		this->activeFigure = nullptr;
	}
}

void LGame::mouseMotionMove(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_PAUSE))
	{
		/*this->focusedSquare->setState(L_SQUARE_NATIVE);
		this->focusedSquare = this->squares[v][h];
		this->focusedSquare->setState(L_SQUARE_FOCUSED);*/
	}
}

void LGame::mouseMove(int v, int h)
{
	if (!(this->getGameInstance() & L_GAME_PAUSE))
	{
		/**this->focusedSquare->setState(L_SQUARE_NATIVE);
		this->focusedSquare = this->squares[v][h];
		this->focusedSquare->setState(L_SQUARE_FOCUSED);*/
	}
}

void LGame::completeMove(LPath* path)
{
	LPlayer* actPlayer = path->getActive();
	LPlayer* passPlayer = path->getPassive();

	LSquare*& from = path->getFrom();
	LSquare*& to = path->getTo();

	int oldVer = from->getVertical();
	int oldHor = from->getHorizontal();

	int newVer = to->getVertical();
	int newHor = to->getHorizontal();

	QString actName = actPlayer->getName();

	int isPossible = path->isPossible();

	LMainWidget* mainWidget = LMainWidget::getInstance();

	if (isPossible & L_PATH_TRUE)
	{
		QString actFigure = this->board->getFigure(oldVer, oldHor)->getName();
		QString passFigure = "";

		if (this->board->getFigure(newVer, newHor))
		{
			QString passFigure = " (" + this->board->getFigure(newVer, newHor)->getName() + ")";

			actPlayer->getOriginal()->addFigure(this->board->getFigure(newVer, newHor));
		}

		this->board->getFigure(newVer, newHor) = this->board->getFigure(oldVer, oldHor);
		this->board->getFigure(oldVer, oldHor) = nullptr;

		QString node = actName + ": " + actFigure + " " +
			('A' + oldHor) + ('8' - oldVer) + " - " +
			('A' + newHor) + ('8' - newVer) + passFigure;

		mainWidget->pathListAppend(node);
	}

	if (isPossible & L_PATH_CASTLING)
	{
		LGame* game = LGame::getInstance();

		if (newHor - oldHor == 2)
		{
			LRook* rook = (LRook*)this->board->getFigure(newVer, newHor + 1);

			if (!rook)
			{
				rook = (LRook*)this->board->getFigure(newVer, newHor + 2);
				this->board->getFigure(newVer, newHor + 2) = nullptr;
			}
			else
			{
				this->board->getFigure(newVer, newHor + 1) = nullptr;
			}

			this->board->getFigure(newVer, newHor - 1) = rook;
		}
		else
		{
			LRook* rook = (LRook*)this->board->getFigure(newVer, newHor - 1);

			if (!rook)
			{
				rook = (LRook*)this->board->getFigure(newVer, newHor - 2);
				this->board->getFigure(newVer, newHor - 2) = nullptr;
			}
			else
			{
				this->board->getFigure(newVer, newHor - 1) = nullptr;
			}

			this->board->getFigure(newVer, newHor + 1) = rook;
		}

		mainWidget->pathListAppend(actName + ": Castling");
	}

	if (isPossible & L_PATH_TRANSFORMATION)
	{
		QString newFigure;

		LFigure* temp = this->board->getFigure(newVer, newHor);

		int figure = this->getFigureTransformation();
		int color = actPlayer->getColor();

		switch (figure)
		{
		case L_FIGURE_QUEEN:
			newFigure = "Queen";
			this->board->getFigure(newVer, newHor) = new LQueen(color);
			break;
		case L_FIGURE_ELEPHANT:
			newFigure = "Elephant";
			this->board->getFigure(newVer, newHor) = new LElephant(color);
			break;
		case L_FIGURE_HORSE:
			newFigure = "Horse";
			this->board->getFigure(newVer, newHor) = new LHorse(color);
			break;
		case L_FIGURE_ROOK:
			newFigure = "Rook";
			this->board->getFigure(newVer, newHor) = new LRook(color);
			break;
		}

		QString node = actName + ": Pawn to " + newFigure;
		mainWidget->pathListAppend(node);

		delete temp;
	}

	if (isPossible & L_PATH_TRUE)
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
					node = this->playerBlack->getName() + " win!\n";
					node += this->playerBlack->getName() + " mat " + this->playerWhite->getName();
					mainWidget->pathListAppend(node);
					mainWidget->messageAlert(node);
					this->changeGameInstance(L_GAME_PAUSE | L_PATH_MAT | L_COLOR_WHITE);
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
					this->changeGameInstance(L_GAME_PAUSE | L_PATH_MAT | L_COLOR_BLACK);
				}
				else
				{
					mainWidget->messageAlert(node);
				}
			}
		}

		else if (this->isPat(path->getPassive()->getColor()))
		{
			QString node = "Dead Heat!\nStalemate situation.";
			mainWidget->pathListAppend(node);
			mainWidget->messageAlert(node);
			this->changeGameInstance(L_GAME_PAUSE | L_PATH_PAT);
		}
	}
}

int LGame::getFigureTransformation()
{
	LTransformation* dialog = new LTransformation;

	int figure;

	if (dialog->exec() == QDialog::Accepted)
	{
		figure = dialog->getFigure();
	}

	delete dialog;

	return figure;
}

void LGame::actionAfterPath(LPath* path)
{
	
}

int LGame::getTypeOfGame()
{
	return 0;
}

void LGame::clear()
{
	delete this->playerWhite;
	delete this->playerBlack;
	delete this->board;
	delete this->activeSquare;
	delete this->activeFigure;
	delete this->focusedSquare;
}
