#pragma once

#include <QWidget>

class LOptions;
class LGame;
class LDesk;
class QPushButton;
class QTextEdit;

class LMainWidget :
	public QWidget
{
	Q_OBJECT

private:
	static LMainWidget* instance;

	LOptions* optionsDialog;
	LGame* game;
	LDesk* desk;

	QPushButton* newGame;
	QPushButton* saveGame;
	QPushButton* loadGame;
	QPushButton* options;
	QPushButton* quit;
	QTextEdit* pathList;

public:
	static LMainWidget* getInstance(QWidget* widget = nullptr);

	LMainWidget(QWidget* widget);

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

	void setPathList(QString string);
	void pathListAppend(QString string);
	void messageAlert(QString string);

};
