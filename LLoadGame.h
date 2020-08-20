#pragma once

#include <QDialog>

class LGame;
class QListWidgetItem;
class LLoadGamePrivate;

class LLoadGame :
	public QDialog
{
	Q_OBJECT

private:
	LLoadGamePrivate* m;

public:
	LLoadGame();
	~LLoadGame();

	QString getNameSelectedSave();
	LGame* getSelectedSave();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotDeleteSave();

};
