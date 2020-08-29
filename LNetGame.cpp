#include "LNetGame.h"
#define LCHILD
#include "LGame.cpp"
#undef LCHILD

#include <QThread>

#include "LMainWidget.h"

#include "LConst.h"
#include "LDesk.h"
#include "LPath.h"
#include "LFigure.h"
#include "LSquare.h"
#include "LPlayer.h"
#include "LOptions.h"
#include "LClient.h"

struct LNetGamePrivate : public LGamePrivate
{
	LClient* client;
	LPlayer* me;
	LPlayer* rival;
	bool& imWhite;

	LNetGamePrivate(int netType, QString ip, int port, bool& imWhite);
	~LNetGamePrivate();
};

LNetGamePrivate::LNetGamePrivate(int netType, QString ip, int port, bool& imWhite)
	:
	client(LClient::newClient(netType, ip, port)),
	me(nullptr),
	rival(nullptr),
	imWhite(imWhite)
{

}

LNetGamePrivate::~LNetGamePrivate()
{
	delete client;
}

LNetGame::LNetGame(int netType, QString ip, int port, QObject* object)
	:
	QObject(object),
	LGame(),
	m(new LNetGamePrivate(netType, ip, port, LGame::m->areWhiteActive))
{
	setGameInstance(L_GAME_PAUSE);

	connect(m->client, SIGNAL(signalNewGame(LPlayer*)), SLOT(slotNewGame(LPlayer*)));
	connect(m->client, SIGNAL(signalGetPath(LPath*)), SLOT(slotGetPath(LPath*)));

	QString name = LOptions::getInstance()->getName();

	m->client->newGame(name);
}

LNetGame::~LNetGame()
{
	disconnect(m->client, SIGNAL(signalNewGame(LPlayer*)), this, SLOT(slotNewGame(LPlayer*)));
	disconnect(m->client, SIGNAL(signalGetPath(LPath*)), this, SLOT(slotGetPath(LPath*)));

	delete m;
}

void LNetGame::actionAfterPath(LPath* path)
{
	if (path && (path->getActive()->getOriginal() == m->me))
	{
		setGameInstance(L_GAME_PAUSE);
		m->client->sendPath(path);
		m->client->getPath();
	}
	else if(!path)
	{
		m->client->getPath();
	}
}

int LNetGame::getTypeOfGame()
{
	return L_TYPE_NET;
}

void LNetGame::slotNewGame(LPlayer* player)
{
	QString myName = LOptions::getInstance()->getName();

	if (player)
	{
		int myColor = (player->getColor() == L_COLOR_WHITE) ? L_COLOR_BLACK : L_COLOR_WHITE;

		m->me = new LPlayer(myColor, myName);
		m->rival = player;

		m->imWhite = myColor == L_COLOR_WHITE;

		m->playerWhite = (m->imWhite) ? m->me : m->rival;
		m->playerBlack = (m->imWhite) ? m->rival : m->me;

		if (m->imWhite)
		{
			setGameInstance(L_GAME_RUNNING);
		}

		LMainWidget* mainWidget = LMainWidget::getInstance();
		mainWidget->pathListAppend(m->me->getName() + " vs " + player->getName());

		LDesk::getInstance()->repaint();

		if (!m->imWhite)
		{
			actionAfterPath(nullptr);
		}
	}
	else
	{
		thread()->usleep(500);
		m->client->newGame(myName);
	}
}

void LNetGame::slotGetPath(LPath* path)
{
	if (path)
	{
		path->setActive(m->rival);
		path->setPassive(m->me);

		setGameInstance(L_GAME_RUNNING);
		completeMove(path);

		LDesk::getInstance()->repaint();
	}
	else
	{
		thread()->usleep(500);
		m->client->getPath();
	}
}
