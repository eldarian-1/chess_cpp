#pragma once

#include "LClient.h"

struct LTcpServerPrivate;

class LTcpServer : public LClient
{
	Q_OBJECT

private:
	friend class LClient;
	LTcpServerPrivate* m;

protected:
	LTcpServer(int port);

public:
	~LTcpServer();

	virtual void sendPath(LPath* path) override;

public slots:
	virtual void slotNewGame(QString name) override;
	virtual void slotGetPath() override;

private:
	void sendToClient(const QString& string);

private slots:
	void slotNewConnection();
	void slotDeleteSocket();
	void slotReadClient();

};
