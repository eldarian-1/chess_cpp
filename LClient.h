#pragma once

#include <QObject>

class LPlayer;
class LPath;

class LClient : public QObject
{
	Q_OBJECT

protected:
	LClient(QObject* object = nullptr);

public:
	~LClient();
	static LClient* newClient(int type, QString ip, int port);

	virtual void newGame(QString name) = 0;
	virtual void sendPath(LPath* path) = 0;
	virtual void getPath() = 0;

signals:
	void signalNewGame(LPlayer* player);
	void signalGetPath(LPath* path);

};
