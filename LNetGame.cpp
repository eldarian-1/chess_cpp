#include "LNetGame.h"

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

LNetGame::LNetGame(QObject* object)
	:
	QObject(object),
	LGame(),
	client(LClient::getInstance()),
	me(nullptr),
	rival(nullptr)
{
	this->changeGameInstance(L_GAME_PAUSE);

	connect(this->client, SIGNAL(signalConnecting(bool)), this, SLOT(slotConnectiong(bool)));
	connect(this->client, SIGNAL(signalNewGame(LPlayer*)), this, SLOT(slotNewGame(LPlayer*)));
	connect(this->client, SIGNAL(signalGetPath(LPath*)), this, SLOT(slotGetPath(LPath*)));

	QString name = LOptions::getInstance()->getName();

	client->newGame(name);
}

void LNetGame::actionAfterPath(LPath* path)
{
	if (path && (path->getActive()->getOriginal() == this->me))
	{
		this->changeGameInstance(L_GAME_PAUSE);
		this->client->sendPath(path);
		this->client->getPath();
	}
	else if(!path)
	{
		this->client->getPath();
	}
}

int LNetGame::getTypeOfGame()
{
	return L_TYPE_NET;
}

void LNetGame::slotConnecting(bool isConnect)
{

}

void LNetGame::slotNewGame(LPlayer* player)
{
	QString myName = LOptions::getInstance()->getName();

	if (player)
	{
		int myColor = (player->getColor() == L_COLOR_WHITE) ? L_COLOR_BLACK : L_COLOR_WHITE;

		this->me = new LPlayer(myColor, myName);
		this->rival = player;

		this->imWhite = myColor == L_COLOR_WHITE;

		this->playerWhite = (this->imWhite) ? this->me : this->rival;
		this->playerBlack = (this->imWhite) ? this->rival : this->me;

		if (this->imWhite)
		{
			this->changeGameInstance(L_GAME_RUNNING);
		}

		LMainWidget* mainWidget = LMainWidget::getInstance();
		mainWidget->pathListAppend(me->getName() + " vs " + player->getName());

		LDesk::getInstance()->repaint();

		if (!this->imWhite)
		{
			this->actionAfterPath(nullptr);
		}
	}
	else
	{
		this->thread()->usleep(500);
		client->newGame(myName);
	}
}

void LNetGame::slotGetPath(LPath* path)
{
	if (path)
	{
		path->setActive(this->rival);
		path->setPassive(this->me);

		this->changeGameInstance(L_GAME_RUNNING);

		this->completeMove(path);

		LDesk::getInstance()->repaint();
	}
	else
	{
		this->thread()->usleep(500);
		this->client->getPath();
	}
}
