#pragma once

#include <QWidget>

class LGame;
class LDesk;
class QPushButton;
class QTextEdit;

class LMainWidget :
	public QWidget
{
	Q_OBJECT

private:
	LGame* game;
	LDesk* desk;

	QPushButton* newGame;
	QPushButton* saveGame;
	QPushButton* loadGame;
	QPushButton* options;
	QPushButton* quit;
	QTextEdit* pathList;

public:
	LMainWidget(QApplication* app, QWidget* widget = nullptr);

protected:
	virtual void paintEvent(QPaintEvent* event);

private slots:
	void slotNewGame();
	void slotSaveGame();
	void slotLoadGame();
	void slotOptions();

public:
	LGame* getGame() const;

	void pathListAppend(QString string);


};
