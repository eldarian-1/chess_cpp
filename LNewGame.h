#pragma once

#include <QDialog>

struct LNewGamePrivate;

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
	void slotCheckBiBot();
	void slotCheckBiNet();
	void slotCheckBot();
	void slotCheckBotNet();
	void slotCheckNet();

public:
	int getGameType() const;
	int getColor() const;
	int getBotPower() const;
	int getNetType() const;
	QString getName1() const;
	QString getName2() const;

};
