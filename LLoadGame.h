#pragma once

#include <QDialog>

class LGame;
class LSaveKeeper;

class QListWidget;
class QListWidgetItem;
class QPushButton;

class LLoadGame :
	public QDialog
{
	Q_OBJECT

private:
	LSaveKeeper* saveKeeper;

	QListWidgetItem* selectedSave;
	QListWidget* saves;

	QPushButton* delButton;
	QPushButton* loadButton;

public:
	LLoadGame();
	~LLoadGame();

	QString getNameSelectedSave();
	LGame* getSelectedSave();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotDeleteSave();

};
