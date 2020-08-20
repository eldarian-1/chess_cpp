#pragma once

#include <QDialog>

class LTransformationPrivate;

class LTransformation :
	public QDialog
{
private:
	LTransformationPrivate* m;

public:
	LTransformation(QWidget* widget = nullptr);
	~LTransformation();

	int getFigure();

};
