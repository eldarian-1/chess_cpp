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

	virtual void sendPath(LPath* path) = 0;

public slots:
	virtual void slotNewGame(QString name) = 0;
	virtual void slotGetPath() = 0;

signals:
	void signalFindNewGame(QString name);
	void signalGetNextPath();

	void signalNewGame(LPlayer* player);
	void signalGetPath(LPath* path);
	void signalStatusChange(int status);

};
