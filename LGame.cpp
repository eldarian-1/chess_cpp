#include "LGame.h"

#include "LConst.h"
#include "LNewGame.h"

#include "LBiGame.h"
#include "LBotGame.h"
#include "LNetGame.h"

#include "LConst.h"
#include "LMain.h"
#include "LTransform.h"
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

struct LGamePrivate
{
	int gameInstance;

	LPlayer* playerWhite;
	LPlayer* playerBlack;

	LBoard* board;
	int _isCheck;

	bool areWhiteActive;
	LSquare* activeSquare;
	LFigure* activeFigure;
	LSquare* focusedSquare;

	LGamePrivate();
	~LGamePrivate();
};

#ifndef LCHILD

LGame* LGame::instance = nullptr;

LGamePrivate::LGamePrivate()
	:
	gameInstance(L_GAME_RUNNING),
	areWhiteActive(true),
	_isCheck(0),
	board(new LBoard),
	activeSquare(nullptr),
	activeFigure(nullptr),
	focusedSquare(nullptr),
	playerWhite(nullptr),
	playerBlack(nullptr)
{

}

LGamePrivate::~LGamePrivate()
{
	delete playerWhite;
	delete playerBlack;
	delete board;
}

LGame::LGame()
	: m(new LGamePrivate)
{
	
}

LGame::~LGame()
{
	clear();
}

LGame* LGame::getInstance()
{
	return instance;
}

int LGame::getGameInstance() const
{
	return m->gameInstance;
}

void LGame::setGameInstance(int gameInstance)
{
	m->gameInstance = gameInstance;
}

void LGame::newGame(LNewGame* dialog)
{
	int gameType = dialog->getGameType();
	int botPower = dialog->getBotPower();
	int netType = dialog->getNetType();

	QString name1 = dialog->getName1();
	QString name2 = dialog->getName2();

	int color = dialog->getColor();

	QString ip = dialog->getIp();
	int port = dialog->getPort();

	color = (color == L_COLOR_ANY) ? (rand() % 2 + L_COLOR_WHITE) : color;

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
		instance = LBotGame::newGame(botPower, color);
		break;
	case L_TYPE_NET:
		instance = new LNetGame(netType, ip, port);
		break;
	}

	instance->m->board->setFigures();

	if (gameType == L_TYPE_BOT && color == L_COLOR_BLACK)
	{
		instance->actionAfterPath(nullptr);
	}
}

void LGame::setGame(LGame* game)
{
	instance = game;

	LMain::getInstance()
		->setGameDesc(
			instance->m->playerWhite->getName() + " vs " + instance->m->playerBlack->getName()
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
		instance = LBotGame::newGame(typeOfBot);
		break;
	}

	instance->m->playerWhite = new LPlayer(L_COLOR_WHITE);
	instance->m->playerBlack = new LPlayer(L_COLOR_BLACK);
}

LFigure* LGame::getFigure(int v, int h)
{
	if (v < 0 || v >= L_CHESS_BOARD_SIZE || h < 0 || h >= L_CHESS_BOARD_SIZE)
		return nullptr;

	return m->board->getFigure(v, h);
}

LSquare*& LGame::getSquare(int v, int h)
{
	return m->board->getSquare(v, h);
}

void LGame::draw()
{
	LDesk* desk = LDesk::getInstance();

	if (m->playerWhite && m->playerBlack)
	{
		desk->drawTablePlayer(m->playerWhite, m->areWhiteActive);
		desk->drawTablePlayer(m->playerBlack, m->areWhiteActive);
	}

	desk->drawMarkup(m->areWhiteActive);

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			m->board->getSquare(i, j)->draw(m->areWhiteActive);
		}
	}

	for (int i = 0; i < L_CHESS_BOARD_SIZE; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE; j++)
		{
			if (m->board->getFigure(i, j))
			{
				m->board->getFigure(i, j)->draw(m->board->getSquare(i, j), m->areWhiteActive);
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
		flag = m->board->getFigure(v, h) &&
			(m->board->getFigure(v, h)->getType() == L_FIGURE_KING) &&
			(m->board->getFigure(v, h)->getColor() == color);
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
			LPath* path = new LPath(m->board->getSquare(y, x), m->board->getSquare(v, h));

			if (!(y == v && x == h) &&
				m->board->getFigure(y, x) &&
				m->board->getFigure(y, x)->getColor() != color &&
				m->board->getFigure(y, x)->isPossiblePath(path) & L_PATH_TRUE)
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
		temp = m->board->getFigure(v, h);
		m->board->getFigure(v, h) = m->board->getFigure(vK, hK);
		m->board->getFigure(vK, hK) = nullptr;
	}
	else
	{
		temp = m->board->getFigure(v, h);
		m->board->getFigure(v, h) = nullptr;
	}

	int response = isCheck(color);

	if (vK != -1)
	{
		m->board->getFigure(vK, hK) = m->board->getFigure(v, h);
		m->board->getFigure(v, h) = temp;
	}
	else
	{
		m->board->getFigure(v, h) = temp;
	}

	return response;
}

int LGame::getIsCheck() const
{
	return m->_isCheck;
}

int LGame::isMat(int color)
{
	bool flag = false;

	for (int i = 0; i < L_CHESS_BOARD_SIZE && !flag; ++i)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE && !flag; ++j)
		{
			if (m->board->getFigure(i, j) && m->board->getFigure(i, j)->getColor() == color)
			{
				for (int k = 0; k < L_CHESS_BOARD_SIZE && !flag; ++k)
				{
					for (int l = 0; l < L_CHESS_BOARD_SIZE && !flag; ++l)
					{
						if (!m->board->getFigure(k, l) || m->board->getFigure(k, l)->getColor() != color)
						{
							LPath* path = new LPath(m->board->getSquare(i, j), m->board->getSquare(k, l));

							flag = !(i == k && j == l) && (m->board->getFigure(i, j)->isPossiblePath(path) & L_PATH_TRUE);

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
		LPath* path = new LPath(game->m->board->getSquare(sV, sH), game->m->board->getSquare(fV, fH));

		bool result = ((fV >= 0) &&
			(fV < L_CHESS_BOARD_SIZE) &&
			(fH >= 0) &&
			(fH < L_CHESS_BOARD_SIZE) &&
			(game->m->board->getFigure(sV, sH)->isPossiblePath(path) & L_PATH_TRUE));

		delete path;

		return result;
	};

	for (int i = 0; i < L_CHESS_BOARD_SIZE && !flag; i++)
	{
		for (int j = 0; j < L_CHESS_BOARD_SIZE && !flag; j++)
		{
			if (m->board->getFigure(i, j) && m->board->getFigure(i, j)->getColor() == color)
			{
				switch (m->board->getFigure(i, j)->getType())
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

					if (m->board->getFigure(i, j)->getType() == L_FIGURE_ELEPHANT)
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

					if (m->board->getFigure(i, j)->getType() == L_FIGURE_ROOK)
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
	if (!(getGameInstance() & L_GAME_PAUSE))
	{
		if (!m->areWhiteActive)
		{
			v = L_CHESS_BOARD_SIZE - 1 - v;
			h = L_CHESS_BOARD_SIZE - 1 - h;
		}

		m->activeSquare = m->board->getSquare(v, h);
		m->activeFigure = m->board->getFigure(v, h);

		m->activeSquare->setState(L_SQUARE_SELECTED);
	}
}

void LGame::mouseRelease(int v, int h)
{
	if (!(getGameInstance() & L_GAME_PAUSE))
	{
		if (!(
			(m->areWhiteActive && m->activeFigure && m->activeFigure->getColor() != L_COLOR_WHITE)
			||
			(!m->areWhiteActive && m->activeFigure && m->activeFigure->getColor() == L_COLOR_WHITE)
			))
		{

			if (!m->areWhiteActive)
			{
				v = L_CHESS_BOARD_SIZE - 1 - v;
				h = L_CHESS_BOARD_SIZE - 1 - h;
			}

			if (m->activeFigure)
			{
				LPlayer* act = m->areWhiteActive ? m->playerWhite : m->playerBlack;
				LPlayer* pass = m->areWhiteActive ? m->playerBlack : m->playerWhite;
				LSquare*& from = m->board->getSquare(m->activeSquare->getVertical(), m->activeSquare->getHorizontal());
				LSquare*& to = m->board->getSquare(v, h);
				LPath* path = new LPath(act->getClone(), pass->getClone(), from, to);

				int isPossible = m->activeFigure->isPossiblePath(path);

				if (isPossible & L_PATH_TRUE)
				{
					path->setPossible(isPossible);
					completeMove(path);
					actionAfterPath(path);
				}

				delete path;
			}

		}

		m->activeSquare->setState(L_SQUARE_NATIVE);

		m->activeSquare = nullptr;
		m->activeFigure = nullptr;
	}
}

void LGame::mouseMotionMove(int v, int h)
{
	if (!(getGameInstance() & L_GAME_PAUSE))
	{
		/*m->focusedSquare->setState(L_SQUARE_NATIVE);
		m->focusedSquare = m->squares[v][h];
		m->focusedSquare->setState(L_SQUARE_FOCUSED);*/
	}
}

void LGame::mouseMove(int v, int h)
{
	if (!(getGameInstance() & L_GAME_PAUSE))
	{
		/**m->focusedSquare->setState(L_SQUARE_NATIVE);
		m->focusedSquare = m->squares[v][h];
		m->focusedSquare->setState(L_SQUARE_FOCUSED);*/
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

	LMain* wgtMain = LMain::getInstance();

	if (isPossible & L_PATH_TRUE)
	{
		QString actFigure = m->board->getFigure(oldVer, oldHor)->getName();
		QString passFigure = "";

		if (m->board->getFigure(newVer, newHor))
		{
			QString passFigure = " (" + m->board->getFigure(newVer, newHor)->getName() + ")";

			actPlayer->getOriginal()->addFigure(m->board->getFigure(newVer, newHor));
		}

		m->board->getFigure(newVer, newHor) = m->board->getFigure(oldVer, oldHor);
		m->board->getFigure(oldVer, oldHor) = nullptr;

		QString node = actName + ": " + actFigure + " " +
			('A' + oldHor) + ('8' - oldVer) + " - " +
			('A' + newHor) + ('8' - newVer) + passFigure;

		wgtMain->appendGameDesc(node);
	}

	if (isPossible & L_PATH_CASTLING)
	{
		LGame* game = LGame::getInstance();

		if (newHor - oldHor == 2)
		{
			LRook* rook = (LRook*)m->board->getFigure(newVer, newHor + 1);

			if (!rook)
			{
				rook = (LRook*)m->board->getFigure(newVer, newHor + 2);
				m->board->getFigure(newVer, newHor + 2) = nullptr;
			}
			else
			{
				m->board->getFigure(newVer, newHor + 1) = nullptr;
			}

			m->board->getFigure(newVer, newHor - 1) = rook;
		}
		else
		{
			LRook* rook = (LRook*)m->board->getFigure(newVer, newHor - 1);

			if (!rook)
			{
				rook = (LRook*)m->board->getFigure(newVer, newHor - 2);
				m->board->getFigure(newVer, newHor - 2) = nullptr;
			}
			else
			{
				m->board->getFigure(newVer, newHor - 1) = nullptr;
			}

			m->board->getFigure(newVer, newHor + 1) = rook;
		}

		wgtMain->appendGameDesc(actName + ": Castling");
	}

	if (isPossible & L_PATH_TRANSFORMATION)
	{
		QString newFigure;

		LFigure* temp = m->board->getFigure(newVer, newHor);

		int figure = getFigureTransformation();
		int color = actPlayer->getColor();

		switch (figure)
		{
		case L_FIGURE_QUEEN:
			newFigure = "Queen";
			m->board->getFigure(newVer, newHor) = new LQueen(color);
			break;
		case L_FIGURE_ELEPHANT:
			newFigure = "Elephant";
			m->board->getFigure(newVer, newHor) = new LElephant(color);
			break;
		case L_FIGURE_HORSE:
			newFigure = "Horse";
			m->board->getFigure(newVer, newHor) = new LHorse(color);
			break;
		case L_FIGURE_ROOK:
			newFigure = "Rook";
			m->board->getFigure(newVer, newHor) = new LRook(color);
			break;
		}

		QString node = actName + ": Pawn to " + newFigure;
		wgtMain->appendGameDesc(node);

		delete temp;
	}

	if (isPossible & L_PATH_TRUE)
	{
		if (m->_isCheck = isCheck(L_COLOR_WHITE) | isCheck(L_COLOR_BLACK))
		{
			QString node;

			if (m->_isCheck & L_COLOR_WHITE)
			{
				node = m->playerBlack->getName() + " check " + m->playerWhite->getName();
				wgtMain->appendGameDesc(node);

				if (isMat(L_COLOR_WHITE) & L_PATH_MAT)
				{
					node = m->playerBlack->getName() + " win!\n";
					node += m->playerBlack->getName() + " mat " + m->playerWhite->getName();
					wgtMain->appendGameDesc(node);
					wgtMain->messageAlert(node);
					setGameInstance(L_GAME_PAUSE | L_PATH_MAT | L_COLOR_WHITE);
				}
				else
				{
					wgtMain->messageAlert(node);
				}
			}

			if (m->_isCheck & L_COLOR_BLACK)
			{
				node = m->playerWhite->getName() + " check " + m->playerBlack->getName();
				wgtMain->appendGameDesc(node);

				if (isMat(L_COLOR_BLACK) & L_PATH_MAT)
				{
					node = m->playerWhite->getName() + " win!\n";
					node += m->playerWhite->getName() + " mat " + m->playerBlack->getName();
					wgtMain->appendGameDesc(node);
					wgtMain->messageAlert(node);
					setGameInstance(L_GAME_PAUSE | L_PATH_MAT | L_COLOR_BLACK);
				}
				else
				{
					wgtMain->messageAlert(node);
				}
			}
		}

		else if (isPat(path->getPassive()->getColor()))
		{
			QString node = "Dead Heat!\nStalemate situation.";
			wgtMain->appendGameDesc(node);
			wgtMain->messageAlert(node);
			setGameInstance(L_GAME_PAUSE | L_PATH_PAT);
		}
	}
}

int LGame::getFigureTransformation()
{
	LTransform* dialog = new LTransform;

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
	delete m;
	m = nullptr;
}

#endif
