#pragma once

#include <QDialog>

class QWidget;
class QString;
class QLineEdit;
class QRadioButton;

class LOptions :
	public QDialog
{
	Q_OBJECT

private:
	static LOptions* instance;

	QWidget* mainWidget;

	QString playerName;
	int windowSize;
	int windowWidth;
	int windowHeight;

	QLineEdit* playerEdit;
	QRadioButton* winSizeNHD;
	QRadioButton* winSizeFWVGA;
	QRadioButton* winSizeHD;
	QRadioButton* winSizeHDP;
	QRadioButton* winSizeFHD;
	QRadioButton* winSizeFULL;

protected:
	LOptions(QWidget* mainWidget, QWidget* widget);

public:
	static LOptions* getInstance(QWidget* mainWidget = nullptr, QWidget* widget = nullptr);

	void showDialog();

	QString getName() const;
	int getWidth() const;
	int getHeight() const;

public slots:
	void slotAccepted();
	void slotFinished();

};
