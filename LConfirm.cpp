#include "LConfirm.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

LConfirm::LConfirm(QString text, QWidget* widget)
	:
	QDialog(widget)
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	QLabel* label = new QLabel(text);
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	QPushButton* buttonYes = new QPushButton("Yes");
	QPushButton* buttonNo = new QPushButton("No");

	mainLayout->addWidget(label);
	mainLayout->addLayout(buttonLayout);
	buttonLayout->addWidget(buttonYes);
	buttonLayout->addWidget(buttonNo);

	connect(buttonYes, SIGNAL(clicked()), this, SLOT(accept()));
	connect(buttonNo, SIGNAL(clicked()), this, SLOT(reject()));

	this->setModal(true);
	this->setWindowTitle("Confirm");
	this->setLayout(mainLayout);
	this->show();
}
