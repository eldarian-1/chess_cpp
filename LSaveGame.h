#pragma once

#include <QDialog>

class LSaveGamePrivate;

class LSaveKeeper;

class QListWidgetItem;

class LSaveGame :
	public QDialog
{
	Q_OBJECT

private:
	LSaveGamePrivate* m;

public:
	LSaveGame();
	~LSaveGame();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotTextChanged(const QString& text);
	void slotSave();
	void slotDeleteSave();

};
