#include "LNewGame.h"

#include "LConst.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>

struct LNewGamePrivate
{
	QVBoxLayout* lytMain;

	QGroupBox* gbTypes;
	QVBoxLayout* lytTypes;
	QRadioButton* rdBi;
	QRadioButton* rdBot;
	QRadioButton* rdNet;

	QHBoxLayout* lytName1;
	QHBoxLayout* lytName2;
	QLabel* lblName1;
	QLabel* lblName2;
	QLineEdit* leName1;
	QLineEdit* leName2;

	QGroupBox* gbBotPower;
	QVBoxLayout* lytBotPower;
	QRadioButton* rdBegin;
	QRadioButton* rdWeak;
	QRadioButton* rdAverage;
	QRadioButton* rdStrong;

	QGroupBox* gbNetType;
	QVBoxLayout* lytNetType;
	QRadioButton* rdWebClient;
	QRadioButton* rdTcpClient;
	QRadioButton* rdTcpServer;

	QGroupBox* gbColor;
	QHBoxLayout* lytColor;
	QRadioButton* rdWhite;
	QRadioButton* rdBlack;
	QRadioButton* rdAny;

	QHBoxLayout* lytButton;
	QPushButton* btnOk;
	QPushButton* btnCancel;

	LNewGamePrivate();
	~LNewGamePrivate();
};

LNewGamePrivate::LNewGamePrivate()
	:
	lytMain(new QVBoxLayout),

	gbTypes(new QGroupBox("Game's Type")),
	lytTypes(new QVBoxLayout),
	rdBi(new QRadioButton("Two players")),
	rdBot(new QRadioButton("Versus Bot")),
	rdNet(new QRadioButton("Versus Internet-players")),

	lytName1(new QHBoxLayout),
	lytName2(new QHBoxLayout),
	lblName1(new QLabel("Player 1:")),
	lblName2(new QLabel("Player 2:")),
	leName1(new QLineEdit),
	leName2(new QLineEdit),

	gbBotPower(new QGroupBox("Bot Power")),
	lytBotPower(new QVBoxLayout),
	rdBegin(new QRadioButton("Begin")),
	rdWeak(new QRadioButton("Weak")),
	rdAverage(new QRadioButton("Average")),
	rdStrong(new QRadioButton("Strong")),

	gbNetType(new QGroupBox("Net Type")),
	lytNetType(new QVBoxLayout),
	rdWebClient(new QRadioButton("Web Client")),
	rdTcpClient(new QRadioButton("Tcp Client")),
	rdTcpServer(new QRadioButton("Tcp Server")),

	gbColor(new QGroupBox("Color of Player 1")),
	lytColor(new QHBoxLayout),
	rdWhite(new QRadioButton("White")),
	rdBlack(new QRadioButton("Black")),
	rdAny(new QRadioButton("Any")),

	lytButton(new QHBoxLayout),
	btnOk(new QPushButton("Ok")),
	btnCancel(new QPushButton("Cancel"))

{
	lytMain->addWidget(gbTypes);
	lytMain->addWidget(gbBotPower);
	lytMain->addWidget(gbNetType);
	lytMain->addLayout(lytName1);
	lytMain->addLayout(lytName2);
	lytMain->addWidget(gbColor);
	lytMain->addLayout(lytButton);

	gbTypes->setLayout(lytTypes);
	lytTypes->addWidget(rdBi);
	lytTypes->addWidget(rdBot);
	lytTypes->addWidget(rdNet);

	gbBotPower->setLayout(lytBotPower);
	lytBotPower->addWidget(rdBegin);
	lytBotPower->addWidget(rdWeak);
	lytBotPower->addWidget(rdAverage);
	lytBotPower->addWidget(rdStrong);

	gbNetType->setLayout(lytNetType);
	lytNetType->addWidget(rdWebClient);
	lytNetType->addWidget(rdTcpClient);
	lytNetType->addWidget(rdTcpServer);

	lytName1->addWidget(lblName1);
	lytName1->addWidget(leName1);
	lytName2->addWidget(lblName2);
	lytName2->addWidget(leName2);

	gbColor->setLayout(lytColor);
	lytColor->addWidget(rdWhite);
	lytColor->addWidget(rdBlack);
	lytColor->addWidget(rdAny);

	lytButton->addWidget(btnOk);
	lytButton->addWidget(btnCancel);

	rdBi->setChecked(true);
	rdBegin->setChecked(true);
	rdWebClient->setChecked(true);
	rdAny->setChecked(true);
}

LNewGamePrivate::~LNewGamePrivate()
{
	delete btnOk;
	delete btnCancel;

	delete rdBi;
	delete rdBot;
	delete rdNet;

	delete rdBegin;
	delete rdWeak;
	delete rdAverage;
	delete rdStrong;

	delete lblName1;
	delete lblName2;
	delete leName1;
	delete leName2;

	delete rdWhite;
	delete rdBlack;
	delete rdAny;

	delete lytTypes;
	delete gbTypes;

	delete lytBotPower;
	delete gbBotPower;

	delete lytName1;
	delete lytName2;
	delete lytButton;

	delete lytColor;
	delete gbColor;

	delete lytMain;
}

LNewGame::LNewGame(QWidget* widget)
	:
	QDialog(widget, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
	m(new LNewGamePrivate)

{
	connect(m->rdBi, SIGNAL(clicked()), SLOT(slotCheckBi()));
	connect(m->rdBi, SIGNAL(clicked()), SLOT(slotCheckBiBot()));
	connect(m->rdBi, SIGNAL(clicked()), SLOT(slotCheckBiNet()));

	connect(m->rdBot, SIGNAL(clicked()), SLOT(slotCheckBot()));
	connect(m->rdBot, SIGNAL(clicked()), SLOT(slotCheckBiBot()));
	connect(m->rdBot, SIGNAL(clicked()), SLOT(slotCheckBotNet()));

	connect(m->rdNet, SIGNAL(clicked()), SLOT(slotCheckBiNet()));
	connect(m->rdNet, SIGNAL(clicked()), SLOT(slotCheckBotNet()));
	connect(m->rdNet, SIGNAL(clicked()), SLOT(slotCheckNet()));

	connect(m->btnOk, SIGNAL(clicked()), SLOT(accept()));
	connect(m->btnCancel, SIGNAL(clicked()), SLOT(reject()));

	setWindowTitle("New Game");
	resize(300, 270);

	slotCheckBi();
	slotCheckBiBot();
	slotCheckBiNet();

	setLayout(m->lytMain);
	setModal(true);
	show();
}

LNewGame::~LNewGame()
{
	disconnect(m->rdBi, SIGNAL(clicked()), this, SLOT(slotCheckBi()));
	disconnect(m->rdBi, SIGNAL(clicked()), this, SLOT(slotCheckBiBot()));
	disconnect(m->rdBi, SIGNAL(clicked()), this, SLOT(slotCheckBiNet()));

	disconnect(m->rdBot, SIGNAL(clicked()), this, SLOT(slotCheckBot()));
	disconnect(m->rdBot, SIGNAL(clicked()), this, SLOT(slotCheckBiBot()));
	disconnect(m->rdBot, SIGNAL(clicked()), this, SLOT(slotCheckBotNet()));

	disconnect(m->rdNet, SIGNAL(clicked()), this, SLOT(slotCheckBiNet()));
	disconnect(m->rdNet, SIGNAL(clicked()), this, SLOT(slotCheckBotNet()));
	disconnect(m->rdNet, SIGNAL(clicked()), this, SLOT(slotCheckNet()));

	disconnect(m->btnOk, SIGNAL(clicked()), this, SLOT(accept()));
	disconnect(m->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

	delete m;
}

void LNewGame::slotCheckBi()
{
	m->gbColor->setVisible(true);
	m->lblName1->setVisible(true);
	m->lblName2->setVisible(true);
	m->leName1->setVisible(true);
	m->leName2->setVisible(true);
}

void LNewGame::slotCheckBiBot()
{
	m->gbNetType->setVisible(false);
}

void LNewGame::slotCheckBiNet()
{
	m->gbBotPower->setVisible(false);
}

void LNewGame::slotCheckBot()
{
	m->gbColor->setVisible(true);
	m->gbBotPower->setVisible(true);
}

void LNewGame::slotCheckBotNet()
{
	m->lblName1->setVisible(false);
	m->lblName2->setVisible(false);
	m->leName1->setVisible(false);
	m->leName2->setVisible(false);
}

void LNewGame::slotCheckNet()
{
	m->gbNetType->setVisible(true);
	m->gbColor->setVisible(false);
}

int LNewGame::getGameType() const
{
	if (m->rdBi->isChecked())
	{
		return LConst::L_TYPE_BI;
	}
	else if (m->rdBot->isChecked())
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
	if (m->rdWhite->isChecked())
	{
		return LConst::L_COLOR_WHITE;
	}
	else if (m->rdBlack->isChecked())
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
	if (m->rdBegin->isChecked())
	{
		return LConst::L_BOT_BEGIN;
	}
	else if (m->rdWeak->isChecked())
	{
		return LConst::L_BOT_WEAK;
	}
	else if (m->rdAverage->isChecked())
	{
		return LConst::L_BOT_AVERAGE;
	}
	else if (m->rdStrong->isChecked())
	{
		return LConst::L_BOT_STRONG;
	}

	return 0;
}

int LNewGame::getNetType() const
{
	if (m->rdWebClient->isChecked())
	{
		return LConst::L_CLIENT_WEB;
	}
	else if (m->rdTcpClient->isChecked())
	{
		return LConst::L_CLIENT_TCP;
	}
	else if (m->rdTcpServer->isChecked())
	{
		return LConst::L_SERVER_TCP;
	}

	return 0;
}

QString LNewGame::getName1() const
{
	return m->leName1->text();
}

QString LNewGame::getName2() const
{
	return m->leName2->text();
}
