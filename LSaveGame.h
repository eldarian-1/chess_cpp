#pragma once

#include <QDialog>

class LGame;

class QListWidget;
class QListWidgetItem;
class QLineEdit;

class LSaveGame :
	public QDialog
{
	Q_OBJECT

private:
	LGame* game;
	QListWidgetItem* selectedSave;
	QListWidget* saves;
	QLineEdit* lineEdit;

public:
	LSaveGame(LGame* game);
	~LSaveGame();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotTextChanged(const QString& text);
	void slotSave();
	void slotDeleteSave();

};
