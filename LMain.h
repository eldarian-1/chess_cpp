#pragma once

#include <QWidget>

class LOptions;
class LGame;
class LDesk;
class QPushButton;
class QTextEdit;

struct LMainPrivate;

class LMain :
	public QWidget
{
	Q_OBJECT

private:
    static LMain *instance;

    LMainPrivate* m;

public:
    static LMain *getInstance();

    LMain(QWidget* widget = nullptr);
	~LMain();

protected:
	virtual void paintEvent(QPaintEvent* event);

private slots:
	void slotNewGame();
	void slotSaveGame();
	void slotLoadGame();
	void slotOptions();
	void slotQuit();

public:
	LGame* getGame() const;

	void setGameDesc(QString string);
	void appendGameDesc(QString string);
	void messageAlert(QString string);

};
