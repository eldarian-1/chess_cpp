#pragma once

#include <QDialog>

class QRadioButton;

class LTransformation :
	public QDialog
{
private:
	QRadioButton* queenRadio;
	QRadioButton* elephantRadio;
	QRadioButton* horseRadio;
	QRadioButton* rookRadio;

public:
	LTransformation(QWidget* widget = nullptr);

	int getFigure();

};
