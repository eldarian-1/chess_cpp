#pragma once

#include "LClient.h"

class LTcpServer :
	public LClient
{
private:
	friend class LClient;

protected:
	LTcpServer(int port);

public:
	~LTcpServer();

	virtual void newGame(QString name) override;
	virtual void sendPath(LPath* path) override;
	virtual void getPath() override;

};
