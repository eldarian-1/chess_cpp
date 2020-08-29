#pragma once

#include "LGame.h"

#include <QObject>

class LFigure;
class LClient;

struct LNetGamePrivate;

class LNetGame :
	public QObject,
	public LGame
{
	Q_OBJECT

private:
	LNetGamePrivate* m;

public:
	LNetGame(int netType, QString ip, int port, QObject* object = nullptr);
	~LNetGame();

	void actionAfterPath(LPath* path) override;

	virtual int getTypeOfGame() override;

private slots:
	void slotNewGame(LPlayer* player);
	void slotGetPath(LPath* path);

};
