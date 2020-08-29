#include "LTcpClient.h"

#include "LPath.h"

#include <QTcpSocket>
#include <QDataStream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

struct LTcpClientPrivate
{
	QTcpSocket* socket;
	QString ip;
	int port;
	quint16 size;
	bool isConnected;

	LTcpClientPrivate(LTcpClient* client, QString ip, int port);
	~LTcpClientPrivate();
};

LTcpClientPrivate::LTcpClientPrivate(LTcpClient* client, QString ip, int port)
	:
	socket(new QTcpSocket(client)),
	ip(ip),
	port(port),
	size(0),
	isConnected(false)
{

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

}

void LTcpClient::newGame(QString name)
{

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

	}
}

void LTcpClient::slotError(QAbstractSocket::SocketError error)
{

}

void LTcpClient::slotConnected()
{
	m->isConnected = true;
}
