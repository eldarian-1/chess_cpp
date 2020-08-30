#include "LTcpClient.h"

#include "LConst.h"
#include "LPath.h"
#include "LPlayer.h"

#include <QTcpSocket>
#include <QDataStream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

struct LTcpClientPrivate
{
	bool isConnected;
	quint16 size;
	QTcpSocket* socket;

	LTcpClientPrivate(LTcpClient* client, QString ip, int port);
	~LTcpClientPrivate();
};

LTcpClientPrivate::LTcpClientPrivate(LTcpClient* client, QString ip, int port)
	:
	socket(new QTcpSocket(client)),
	size(0),
	isConnected(false)
{
	socket->connectToHost(ip, port);
}

LTcpClientPrivate::~LTcpClientPrivate()
{
	delete socket;
}

LTcpClient::LTcpClient(QString ip, int port)
	:
	LClient(),
	m(new LTcpClientPrivate(this, ip, port))
{
	connect(m->socket, SIGNAL(connected()), SLOT(slotConnected()));
	connect(m->socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
	connect(m->socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
}

LTcpClient::~LTcpClient()
{
	disconnect(m->socket, SIGNAL(connected()), this, SLOT(slotConnected()));
	disconnect(m->socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	disconnect(m->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

	delete m;
}

void LTcpClient::newGame(QString name)
{
	sendToServer(LPlayer::toJsonClientString(name));
}

void LTcpClient::sendPath(LPath* path)
{
	sendToServer(path->toJsonString());
}

void LTcpClient::getPath()
{

}

void LTcpClient::sendToServer(QString text)
{
	QByteArray arrBlock;
	QDataStream out(&arrBlock, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_14);
	out << quint16(0) << text;

	out.device()->seek(0);
	out << quint16(arrBlock.size() - sizeof(quint16));

	m->socket->write(arrBlock);
}

void LTcpClient::slotReadyRead()
{
	QDataStream in(m->socket);
	in.setVersion(QDataStream::Qt_5_14);

	while (true)
	{
		if (!m->size)
		{
			if (m->socket->bytesAvailable() < sizeof(quint16))
			{
				break;
			}
			in >> m->size;
		}

		if (m->socket->bytesAvailable() < m->size)
		{
			break;
		}

		QByteArray response;
		in >> response;
		m->size = 0;

		QJsonObject object = QJsonDocument::fromJson(response).object();
		if (m->isConnected)
		{
			LPath* path = LPath::pathFromJson(&object);
			emit signalGetPath(path);
		}
		else
		{
			LPlayer* player = LPlayer::playerFromJson(&object);
			m->isConnected = true;
			emit signalNewGame(player);
		}
	}
}

void LTcpClient::slotError(QAbstractSocket::SocketError error)
{
	emit signalStatusChange(L_GAME_PAUSE);
}

void LTcpClient::slotConnected()
{
	
}
