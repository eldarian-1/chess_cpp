#pragma once

#include <QDialog>

class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;

class LNewGame :
	public QDialog
{
	Q_OBJECT

private:
	QRadioButton* biRadio;
	QRadioButton* botRadio;
	QRadioButton* netRadio;

	QGroupBox* botPower;

	QRadioButton* beginRadio;
	QRadioButton* weakRadio;
	QRadioButton* averageRadio;
	QRadioButton* strongRadio;

	QLabel* name1;
	QLabel* name2;

	QLineEdit* name1Edit;
	QLineEdit* name2Edit;

	QRadioButton* whiteRadio;
	QRadioButton* blackRadio;
	QRadioButton* anyRadio;

public:
	LNewGame(QWidget* widget = nullptr);

private slots:
	void slotCheckBi();
	void slotCheckBot();
	void slotCheckBiNet();
	void slotCheckBotNet();

public:
	int getGameType() const;
	int getColor() const;
	int getBotPower() const;
	QString getName1() const;
	QString getName2() const;

};

