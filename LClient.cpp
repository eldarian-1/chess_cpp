#include "LClient.h"

#include "LWebClient.h"
#include "LTcpClient.h"
#include "LTcpServer.h"

#include "LPlayer.h"
#include "LConst.h"
#include "LPath.h"

struct LClientPrivate
{
	QString gameId;
	QString clientId;
	QString player;
	QString path;

	LClientPrivate();
	~LClientPrivate();
};

#ifndef LCHILD

LClientPrivate::LClientPrivate()
	:
	clientId("clientId=" + QString::number(rand())),
	gameId("")
{

}

LClientPrivate::~LClientPrivate()
{
	
}

LClient::LClient(QObject* object)
	:
	QObject(object),
	m(new LClientPrivate)
{
	
}

LClient* LClient::newClient(int type)
{
	switch (type)
	{
	case L_CLIENT_WEB:
		return new LWebClient;
	case L_CLIENT_TCP:
		return new LTcpClient;
	case L_SERVER_TCP:
		return new LTcpServer;
	}
}

LClient::~LClient()
{
	delete m;
}

#undef LCLIENT
#endif
