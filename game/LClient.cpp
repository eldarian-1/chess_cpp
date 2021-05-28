#include "LClient.h"

#include "LConst.h"

#include "LWebClient.h"
#include "LTcpClient.h"
#include "LTcpServer.h"

LClient::LClient(QObject* object)
	: QObject(object)
{
	
}

LClient::~LClient()
{

}

LClient* LClient::newClient(int type, QString ip, int port)
{
	switch (type)
	{
	case L_CLIENT_WEB:
		return new LWebClient;
	case L_CLIENT_TCP:
		return new LTcpClient(ip, port);
	case L_SERVER_TCP:
		return new LTcpServer(port);
	default:
		return nullptr;
	}
}
