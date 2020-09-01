#include "LNetGame.h"
#define LCHILD
#include "LGame.cpp"
#undef LCHILD

#include <QThread>

#include "LMain.h"
#include "LConst.h"
#include "LDesk.h"
#include "LPath.h"
#include "LFigure.h"
#include "LSquare.h"
#include "LPlayer.h"
#include "LOptions.h"
#include "LClient.h"

struct LNetGamePrivate
{
	LClient* client;
	LPlayer*& me;
	LPlayer*& rival;
	bool& imWhite;

	LNetGamePrivate(int netType, QString ip, int port, bool& imWhite, LPlayer*& white, LPlayer*& black);
	~LNetGamePrivate();
};

LNetGamePrivate::LNetGamePrivate(int netType, QString ip, int port, bool& imWhite, LPlayer*& white, LPlayer*& black)
	:
	client(LClient::newClient(netType, ip, port)),
	me(white),
	rival(black),
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
	m(new LNetGamePrivate(netType, ip, port, LGame::m->areWhiteActive, LGame::m->playerWhite, LGame::m->playerWhite))
{
	setGameInstance(L_GAME_PAUSE);

	connect(m->client, SIGNAL(signalNewGame(LPlayer*)), SLOT(slotNewGame(LPlayer*)));
	connect(m->client, SIGNAL(signalGetPath(LPath*)), SLOT(slotGetPath(LPath*)));
	connect(m->client, SIGNAL(signalStatusChange(int)), SLOT(slotStatusChange(int)));

	QString name = LOptions::getInstance()->getName();

	m->client->slotNewGame(name);
}

LNetGame::~LNetGame()
{
	disconnect(m->client, SIGNAL(signalNewGame(LPlayer*)), this, SLOT(slotNewGame(LPlayer*)));
	disconnect(m->client, SIGNAL(signalGetPath(LPath*)), this, SLOT(slotGetPath(LPath*)));
	disconnect(m->client, SIGNAL(signalStatusChange(int)), this, SLOT(slotStatusChange(int)));

	delete m;
}

void LNetGame::actionAfterPath(LPath* path)
{
	if (path && path->getActive()->getOriginal() == m->me)
	{
		setGameInstance(L_GAME_PAUSE);
		m->client->sendPath(path);
		m->client->slotGetPath();
	}
	else if(!path)
		m->client->slotGetPath();
}

int LNetGame::getTypeOfGame()
{
	return L_TYPE_NET;
}

void LNetGame::slotNewGame(LPlayer* player)
{
	QString myName = LOptions::getInstance()->getName();
	int myColor = player->getColor() == L_COLOR_WHITE ? L_COLOR_BLACK : L_COLOR_WHITE;
	LPlayer* myPlayer = new LPlayer(myColor, myName);

	m->imWhite = myColor == L_COLOR_WHITE;
	LGame::m->playerWhite = (m->imWhite) ? myPlayer : player;
	LGame::m->playerBlack = (m->imWhite) ? player : myPlayer;

	if (m->imWhite)
		setGameInstance(L_GAME_RUNNING);

	LMain::getInstance()->appendGameDesc(m->me->getName() + " vs " + player->getName());
	LDesk::getInstance()->repaint();

	if (!m->imWhite)
		actionAfterPath(nullptr);
}

void LNetGame::slotGetPath(LPath* path)
{
	path->setActive(m->rival);
	path->setPassive(m->me);

	setGameInstance(L_GAME_RUNNING);
	completeMove(path);

	LDesk::getInstance()->repaint();
}

void  LNetGame::slotStatusChange(int status)
{
	LGame::m->gameInstance = status;
}
