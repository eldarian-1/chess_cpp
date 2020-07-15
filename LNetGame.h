#pragma once

#include "LGame.h"

#include <QObject>

class LFigure;
class LClient;

class LNetGame :
	public QObject,
	public LGame
{
	Q_OBJECT

private:
	LClient* client;

	LPlayer* me;
	LPlayer* rival;

	int myColor;

public:
	LNetGame(int color, QObject* object = nullptr);

	void actionAfterPath(LPath* path) override;

private slots:
	void slotConnecting(bool isConnect);
	void slotNewGame(LPlayer* player);
	void slotGetPath(LPath* path);

};
