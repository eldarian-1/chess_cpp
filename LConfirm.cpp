#include "LConfirm.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class LConfirmPrivate
{
public:
	QVBoxLayout* lytMain;
	QLabel* lblText;
	QHBoxLayout* lytButton;
	QPushButton* btnYes;
	QPushButton* btnNo;

	LConfirmPrivate(QString text);
	~LConfirmPrivate();
};

LConfirmPrivate::LConfirmPrivate(QString text)
	:
	lytMain(new QVBoxLayout),
	lblText(new QLabel(text)),
	lytButton(new QHBoxLayout),
	btnYes(new QPushButton("Yes")),
	btnNo(new QPushButton("No"))
{
	lytMain->addWidget(lblText);
	lytMain->addLayout(lytButton);
	lytButton->addWidget(btnYes);
	lytButton->addWidget(btnNo);
}

LConfirmPrivate::~LConfirmPrivate()
{
	delete lblText;
	delete btnYes;
	delete btnNo;
	delete lytButton;
	delete lytMain;
}

LConfirm::LConfirm(QString text, QWidget* widget)
	:
	QDialog(widget),
	m(new LConfirmPrivate(text))
{
	connect(m->btnYes, SIGNAL(clicked()), SLOT(accept()));
	connect(m->btnNo, SIGNAL(clicked()), SLOT(reject()));

	setModal(true);
	setWindowTitle("Confirm");
	setLayout(m->lytMain);
	show();
}

LConfirm::~LConfirm()
{
	disconnect(m->btnYes, SIGNAL(clicked()), this, SLOT(accept()));
	disconnect(m->btnNo, SIGNAL(clicked()), this, SLOT(reject()));

	delete m;
}
