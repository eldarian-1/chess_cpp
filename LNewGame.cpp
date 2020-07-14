#include "LNewGame.h"

#include "LConst.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>

LNewGame::LNewGame(QWidget* widget)
	:
	QDialog(widget, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),

	biRadio(new QRadioButton("Two players")),
	botRadio(new QRadioButton("Versus Bot")),
	netRadio(new QRadioButton("Versus Internet-players")),

	botPower(new QGroupBox("Bot Power")),
	beginRadio(new QRadioButton("Begin")),
	weakRadio(new QRadioButton("Weak")),
	averageRadio(new QRadioButton("Average")),
	strongRadio(new QRadioButton("Strong")),

	name1(new QLabel("Player 1:")),
	name2(new QLabel("Player 2:")),
	name1Edit(new QLineEdit),
	name2Edit(new QLineEdit),

	whiteRadio(new QRadioButton("White")),
	blackRadio(new QRadioButton("Black")),
	anyRadio(new QRadioButton("Any"))
{
	QVBoxLayout* mainLayout = new QVBoxLayout;

	QGroupBox* game = new QGroupBox("Game's Type");
	QVBoxLayout* hLayoutGameType = new QVBoxLayout;
	QVBoxLayout* hLayoutBotPower = new QVBoxLayout;

	QHBoxLayout* hLayoutName1 = new QHBoxLayout;
	QHBoxLayout* hLayoutName2 = new QHBoxLayout;

	QGroupBox* color = new QGroupBox("Color of Player 1");
	QHBoxLayout* hLayoutColor = new QHBoxLayout;

	QHBoxLayout* hLayoutButton = new QHBoxLayout;
	QPushButton* buttonOk = new QPushButton("Ok");
	QPushButton* buttonCancel = new QPushButton("Cancel");

	mainLayout->addWidget(game);
	game->setLayout(hLayoutGameType);
	hLayoutGameType->addWidget(this->biRadio);
	hLayoutGameType->addWidget(this->botRadio);
	hLayoutGameType->addWidget(this->netRadio);

	mainLayout->addWidget(this->botPower);
	this->botPower->setLayout(hLayoutBotPower);
	hLayoutBotPower->addWidget(this->beginRadio);
	hLayoutBotPower->addWidget(this->weakRadio);
	hLayoutBotPower->addWidget(this->averageRadio);
	hLayoutBotPower->addWidget(this->strongRadio);

	mainLayout->addLayout(hLayoutName1);
	hLayoutName1->addWidget(this->name1);
	hLayoutName1->addWidget(this->name1Edit);

	mainLayout->addLayout(hLayoutName2);
	hLayoutName2->addWidget(this->name2);
	hLayoutName2->addWidget(this->name2Edit);

	mainLayout->addWidget(color);
	color->setLayout(hLayoutColor);
	hLayoutColor->addWidget(this->whiteRadio);
	hLayoutColor->addWidget(this->blackRadio);
	hLayoutColor->addWidget(this->anyRadio);

	mainLayout->addLayout(hLayoutButton);
	hLayoutButton->addWidget(buttonOk);
	hLayoutButton->addWidget(buttonCancel);

	connect(this->biRadio, SIGNAL(clicked()), SLOT(slotCheckBi()));
	connect(this->biRadio, SIGNAL(clicked()), SLOT(slotCheckBiNet()));
	connect(this->botRadio, SIGNAL(clicked()), SLOT(slotCheckBot()));
	connect(this->botRadio, SIGNAL(clicked()), SLOT(slotCheckBotNet()));
	connect(this->netRadio, SIGNAL(clicked()), SLOT(slotCheckBiNet()));
	connect(this->netRadio, SIGNAL(clicked()), SLOT(slotCheckBotNet()));

	connect(buttonOk, SIGNAL(clicked()), SLOT(accept()));
	connect(buttonCancel, SIGNAL(clicked()), SLOT(reject()));

	this->biRadio->setChecked(true);
	this->beginRadio->setChecked(true);
	this->anyRadio->setChecked(true);

	this->setWindowTitle("New Game");
	this->resize(300, 270);

	this->slotCheckBi();
	this->slotCheckBiNet();

	this->setLayout(mainLayout);
	this->setModal(true);
	this->show();
}

void LNewGame::slotCheckBi()
{
	this->name1Edit->setVisible(true);
	this->name2Edit->setVisible(true);
	this->name1->setVisible(true);
	this->name2->setVisible(true);
}

void LNewGame::slotCheckBiNet()
{
	this->botPower->setVisible(false);
}

void LNewGame::slotCheckBot()
{
	this->botPower->setVisible(true);
}

void LNewGame::slotCheckBotNet()
{
	this->name1Edit->setVisible(false);
	this->name2Edit->setVisible(false);
	this->name1->setVisible(false);
	this->name2->setVisible(false);
}

int LNewGame::getGameType() const
{
	if (this->biRadio->isChecked())
	{
		return LConst::L_TYPE_BI;
	}
	else if (this->botRadio->isChecked())
	{
		return LConst::L_TYPE_BOT;
	}
	else
	{
		return LConst::L_TYPE_NET;
	}
}

int LNewGame::getColor() const
{
	if (this->whiteRadio->isChecked())
	{
		return LConst::L_COLOR_WHITE;
	}
	else if (this->blackRadio->isChecked())
	{
		return LConst::L_COLOR_BLACK;
	}
	else
	{
		return LConst::L_COLOR_ANY;
	}
}

int LNewGame::getBotPower() const
{
	if (this->beginRadio->isChecked())
	{
		return LConst::L_BOT_BEGIN;
	}
	else if (this->weakRadio->isChecked())
	{
		return LConst::L_BOT_WEAK;
	}
	else if (this->averageRadio->isChecked())
	{
		return LConst::L_BOT_AVERAGE;
	}
	else if (this->strongRadio->isChecked())
	{
		return LConst::L_BOT_STRONG;
	}

	return 0;
}

QString LNewGame::getName1() const
{
	return this->name1Edit->text();
}

QString LNewGame::getName2() const
{
	return this->name2Edit->text();
}