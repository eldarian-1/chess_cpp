#include "LTransformation.h"

#include "LConst.h"

#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>

LTransformation::LTransformation(QWidget* widget)
	:
	QDialog(widget, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
	queenRadio(new QRadioButton("Queen")),
	elephantRadio(new QRadioButton("Elephant")),
	horseRadio(new QRadioButton("Horse")),
	rookRadio(new QRadioButton("Rook"))
{
	QGroupBox* game = new QGroupBox("Select figure");
	QVBoxLayout* vLayout = new QVBoxLayout;
	QHBoxLayout* hLayout = new QHBoxLayout;
	QPushButton* buttonOk = new QPushButton("Ok");

	vLayout->addWidget(game);
	vLayout->addWidget(buttonOk);

	game->setLayout(hLayout);
	hLayout->addWidget(this->queenRadio);
	hLayout->addWidget(this->elephantRadio);
	hLayout->addWidget(this->horseRadio);
	hLayout->addWidget(this->rookRadio);

	connect(buttonOk, SIGNAL(clicked()), SLOT(accept()));

	this->queenRadio->setChecked(true);

	this->setWindowTitle("Transformation");
	this->setLayout(vLayout);
	this->setModal(true);
	this->show();
}

int LTransformation::getFigure()
{
	if (this->queenRadio->isChecked())
	{
		return L_FIGURE_QUEEN;
	}
	else if (this->elephantRadio->isChecked())
	{
		return L_FIGURE_ELEPHANT;
	}
	else if (this->horseRadio->isChecked())
	{
		return L_FIGURE_HORSE;
	}
	else
	{
		return L_FIGURE_ROOK;
	}
}
