#pragma once

#include <QDialog>

class LGame;

class QListWidget;
class QListWidgetItem;

class LLoadGame :
	public QDialog
{
	Q_OBJECT

private:
	QListWidgetItem* selectedSave;
	QListWidget* saves;

public:
	LLoadGame();
	~LLoadGame();

	LGame* getSelectedSave();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotDeleteSave();

};
