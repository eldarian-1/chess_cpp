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

	bool& imWhite = LGame::areWhiteActive;

public:
	LNetGame(QObject* object = nullptr);

	void actionAfterPath(LPath* path) override;

	virtual int getTypeOfGame() override;

private slots:
	void slotConnecting(bool isConnect);
	void slotNewGame(LPlayer* player);
	void slotGetPath(LPath* path);

};
