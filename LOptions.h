#pragma once

#include <QDialog>

class QWidget;
class QString;
class LOptionsPrivate;

class LOptions :
	public QDialog
{
	Q_OBJECT

private:
	static LOptions* instance;
	LOptionsPrivate* m;

public:
	static LOptions* getInstance(QWidget* mainWidget = nullptr, QWidget* widget = nullptr);

protected:
	LOptions(QWidget* mainWidget, QWidget* widget);

public:
	~LOptions();

	QString getName() const;
	int getWidth() const;
	int getHeight() const;

	void showDialog();

public slots:
	void slotAccepted();
	void slotFinished();

};
