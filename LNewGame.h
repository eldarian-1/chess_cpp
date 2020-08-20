#pragma once

#include <QDialog>

class LNewGamePrivate;

class LNewGame :
	public QDialog
{
	Q_OBJECT

private:
	LNewGamePrivate* m;

public:
	LNewGame(QWidget* widget = nullptr);
	~LNewGame();

private slots:
	void slotCheckBi();
	void slotCheckBot();
	void slotCheckBiNet();
	void slotCheckBotNet();
	void slotCheckNet();

public:
	int getGameType() const;
	int getColor() const;
	int getBotPower() const;
	QString getName1() const;
	QString getName2() const;

};
