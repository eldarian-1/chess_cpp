#pragma once

#include <QDialog>

class LSaveKeeper;

class QListWidget;
class QListWidgetItem;
class QLineEdit;
class QPushButton;

class LSaveGame :
	public QDialog
{
	Q_OBJECT

private:
	LSaveKeeper* saveKeeper;

	QListWidgetItem* selectedSave;
	QListWidget* saves;

	QLineEdit* lineEdit;
	QPushButton* delButton;
	QPushButton* saveButton;

public:
	LSaveGame();
	~LSaveGame();

public slots:
	void slotSelectSave(QListWidgetItem* item);
	void slotTextChanged(const QString& text);
	void slotSave();
	void slotDeleteSave();

};
