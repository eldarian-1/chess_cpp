#pragma once

#include <QObject>

class LPlayer;
class LPath;

struct LClientPrivate;

class LClient : public QObject
{
	Q_OBJECT

protected:
	LClientPrivate* m;

	LClient(QObject* object = nullptr);

public:
	static LClient* newClient(int type);
	~LClient();

	virtual void newGame(QString name) = 0;
	virtual void sendPath(LPath* path) = 0;
	virtual void getPath() = 0;

signals:
	void signalNewGame(LPlayer* player);
	void signalGetPath(LPath* path);

};
