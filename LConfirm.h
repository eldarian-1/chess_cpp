#pragma once

#include <QDialog>

class LConfirm :
	public QDialog
{
	Q_OBJECT

public:
	LConfirm(QString text, QWidget* widget = nullptr);

};
