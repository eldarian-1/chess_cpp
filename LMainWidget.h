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

	LOptions* optionsDIalog;
	LGame* game;
	LDesk* desk;

	QPushButton* newGame;
	QPushButton* saveGame;
	QPushButton* loadGame;
	QPushButton* options;
	QPushButton* quit;
	QTextEdit* pathList;

public:
	static LMainWidget* getInstance(QApplication* app = nullptr, QWidget* widget = nullptr);

	LMainWidget(QApplication* app, QWidget* widget);

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
	void messageAlert(QString string);

};
