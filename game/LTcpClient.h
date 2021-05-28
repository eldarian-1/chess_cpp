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

	virtual void sendPath(LPath* path) override;

public slots:
	virtual void slotNewGame(QString name) override;
	virtual void slotGetPath() override;

private:
	void sendToServer(QString text);

private slots:
	void slotReadyRead();
	void slotError(QAbstractSocket::SocketError error);
	void slotConnected();

};
