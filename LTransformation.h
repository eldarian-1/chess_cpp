#pragma once

#include <QDialog>

struct LTransformationPrivate;

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
