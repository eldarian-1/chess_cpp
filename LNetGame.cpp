#include "LNetGame.h"

#include <QThread>

#include "LMainWidget.h"

#include "LConst.h"
#include "LPath.h"
#include "LFigure.h"
#include "LSquare.h"
#include "LPlayer.h"
#include "LOptions.h"
#include "LClient.h"

LNetGame::LNetGame(int c, QObject* object)
	:
	QObject(object),
	LGame(),
	client(LClient::getInstance()),
	me(nullptr),
	rival(nullptr),
	myColor(c)
{
	this->areWhiteActive = !(c == L_COLOR_BLACK);
	this->changeGameInstance(L_GAME_PAUSE);

	connect(this->client, SIGNAL(signalConnecting(bool)), this, SLOT(slotConnectiong(bool)));
	connect(this->client, SIGNAL(signalNewGame(LPlayer*)), this, SLOT(slotNewGame(LPlayer*)));
	connect(this->client, SIGNAL(signalGetPath(LPath*)), this, SLOT(slotGetPath(LPath*)));

	QString name = LOptions::getInstance()->getName();
	LPlayer* tempPlayer = new LPlayer(c, name);

	client->newGame(tempPlayer);
	delete tempPlayer;
}

void LNetGame::actionAfterPath(LPath* path)
{
	this->changeGameInstance(L_GAME_PAUSE);
	this->client->sendPath(path);
	this->client->getPath();
}

void LNetGame::slotConnecting(bool isConnect)
{

}

void LNetGame::slotNewGame(LPlayer* player)
{
	if (player)
	{
		QString myName = LOptions::getInstance()->getName();
		this->myColor = (player->getColor() == L_COLOR_WHITE) ? L_COLOR_BLACK : L_COLOR_WHITE;

		this->me = new LPlayer(this->myColor, myName);
		this->rival = player;

		this->areWhiteActive = this->myColor == L_COLOR_WHITE;

		this->playerWhite = (this->areWhiteActive) ? this->me : this->rival;
		this->playerBlack = (this->areWhiteActive) ? this->rival : this->me;

		this->changeGameInstance(L_GAME_RUNNING);

		LMainWidget* mainWidget = LMainWidget::getInstance();
		mainWidget->pathListAppend(me->getName() + " vs " + player->getName());
	}
	else
	{
		this->thread()->usleep(500);

		QString name = LOptions::getInstance()->getName();
		LPlayer* tempPlayer = new LPlayer(this->myColor, name);

		client->newGame(tempPlayer);
		delete tempPlayer;
	}
}

void LNetGame::slotGetPath(LPath* path)
{
	if (path)
	{
		path->setActive(this->rival);
		path->setPassive(this->me);

		this->completeMove(path);

		this->changeGameInstance(L_GAME_RUNNING);
	}
	else
	{
		this->thread()->usleep(500);
		this->client->getPath();
	}
}
