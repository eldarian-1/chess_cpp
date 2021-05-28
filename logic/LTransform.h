#pragma once

#include <QDialog>

struct LTransformPrivate;

class LTransform :
	public QDialog
{
private:
	LTransformPrivate* m;

public:
	LTransform(QWidget* widget = nullptr);
	~LTransform();

	int getFigure();

};
