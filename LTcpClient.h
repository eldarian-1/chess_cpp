#pragma once

#include "LClient.h"

class LTcpClient :
	public LClient
{
private:
	friend class LClient;

protected:
	LTcpClient();

public:
	~LTcpClient();

	virtual void newGame(QString name) override;
	virtual void sendPath(LPath* path) override;
	virtual void getPath() override;

};
