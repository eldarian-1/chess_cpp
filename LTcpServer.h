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

	virtual void newGame(QString name) override;
	virtual void sendPath(LPath* path) override;
	virtual void getPath() override;

private:
	void sendToClient(const QString& string);

private slots:
	void slotNewConnection();
	void slotDeleteSocket();
	void slotReadClient();

};
