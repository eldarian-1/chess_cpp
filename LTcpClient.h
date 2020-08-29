#pragma once

#include "LClient.h"

#include <QAbstractSocket>

struct LTcpClientPrivate;

class LTcpClient : public LClient
{
	Q_OBJECT

private:
	friend class LClient;
	LTcpClientPrivate* m;

protected:
	LTcpClient(QString ip, int port);

public:
	~LTcpClient();

	virtual void newGame(QString name) override;
	virtual void sendPath(LPath* path) override;
	virtual void getPath() override;

private:
	void sendToServer(QString text);

private slots:
	void slotReadyRead();
	void slotError(QAbstractSocket::SocketError error);
	void slotConnected();

};
