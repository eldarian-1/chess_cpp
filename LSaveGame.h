#pragma once

#include <QDialog>

class LSaveKeeper;
class QListWidgetItem;

struct LSaveGamePrivate;

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
