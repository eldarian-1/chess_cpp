#pragma once

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QLineEdit;

class LSaveGame :
	public QDialog
{
	Q_OBJECT

private:
	QListWidgetItem* selectedSave;
	QListWidget* saves;
	QLineEdit* lineEdit;

public:
	LSaveGame();
	~LSaveGame();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotTextChanged(const QString& text);
	void slotSave();
	void slotDeleteSave();

};
