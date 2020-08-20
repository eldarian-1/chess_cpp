#pragma once

#include <QDialog>

class LConfirmPrivate;

class LConfirm :
	public QDialog
{
	Q_OBJECT

private:
	LConfirmPrivate* m;

public:
	LConfirm(QString text, QWidget* widget = nullptr);
	~LConfirm();

};
