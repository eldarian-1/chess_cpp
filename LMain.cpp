#include "LMain.h"

#include "LConst.h"
#include "LDesk.h"
#include "LGame.h"
#include "LConfirm.h"
#include "LNewGame.h"
#include "LLoadGame.h"
#include "LSaveGame.h"
#include "LOptions.h"

#include <QApplication>
#include <QPalette>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

LMain* LMain::instance = nullptr;

struct LMainPrivate
{
	LGame* game;
	LDesk* wgtDesk;
	LOptions* dlgOptions;

	QHBoxLayout* lytMain;
	QVBoxLayout* lytMenu;

	QPushButton* btnNewGame;
	QPushButton* btnSaveGame;
	QPushButton* btnLoadGame;
	QPushButton* btnOptions;
	QPushButton* btnQuit;
	QTextEdit* teGameDesc;

	LMainPrivate(LMain* wgtMain);
	~LMainPrivate();
};

LMainPrivate::LMainPrivate(LMain* wgtMain)
	:
	dlgOptions(LOptions::getInstance(wgtMain)),
	wgtDesk(LDesk::getInstance(wgtMain)),
	game(nullptr),
	lytMain(new QHBoxLayout),
	lytMenu(new QVBoxLayout),
	btnNewGame(new QPushButton(QIcon(":/LBQueen.png"), "New Game")),
	btnSaveGame(new QPushButton(QIcon(":/LBElephant.png"), "Save Game")),
	btnLoadGame(new QPushButton(QIcon(":/LBHorse.png"), "Load Game")),
	btnOptions(new QPushButton(QIcon(":/LBRook.png"), "Options")),
	btnQuit(new QPushButton(QIcon(":/LBPawn.png"), "Quit")),
	teGameDesc(new QTextEdit)
{
	
}

LMainPrivate::~LMainPrivate()
{
	delete btnNewGame;
	delete btnSaveGame;
	delete btnLoadGame;
	delete btnOptions;
	delete btnQuit;
	delete teGameDesc;
	delete lytMenu;
	delete lytMain;
}

LMain* LMain::getInstance()
{
	if (!instance)
        instance = new LMain();

	return instance;
}

LMain::LMain(QWidget* widget)
	:
	QWidget(widget),
	m(new LMainPrivate(this))
{
	setFixedSize(m->dlgOptions->getWidth(), m->dlgOptions->getHeight());
	setPalette(QPalette(QColor(255, 255, 255)));
	m->teGameDesc->setDisabled(true);

	setLayout(m->lytMain);
	m->lytMain->setMargin(0);
	m->lytMain->setSpacing(0);
	m->lytMain->addLayout(m->lytMenu, 1);
	m->lytMain->addWidget(m->wgtDesk, 6);

	m->lytMenu->setMargin(10);
	m->lytMenu->setSpacing(10);
	m->lytMenu->addWidget(m->btnNewGame);
	m->lytMenu->addWidget(m->btnSaveGame);
	m->lytMenu->addWidget(m->btnLoadGame);
	m->lytMenu->addWidget(m->btnOptions);
	m->lytMenu->addWidget(m->btnQuit);
	m->lytMenu->addWidget(m->teGameDesc);

	setWindowTitle("Chess by Eldarian Studio");
	setWindowIcon(QIcon(":/LBKing.png"));
	m->btnSaveGame->setVisible(false);

	connect(m->btnNewGame, SIGNAL(clicked()), SLOT(slotNewGame()));
	connect(m->btnSaveGame, SIGNAL(clicked()), SLOT(slotSaveGame()));
	connect(m->btnLoadGame, SIGNAL(clicked()), SLOT(slotLoadGame()));
	connect(m->btnOptions, SIGNAL(clicked()), SLOT(slotOptions()));
	connect(m->btnQuit, SIGNAL(clicked()), SLOT(slotQuit()));
}

LMain::~LMain()
{
	connect(m->btnNewGame, SIGNAL(clicked()), this, SLOT(slotNewGame()));
	connect(m->btnSaveGame, SIGNAL(clicked()), this, SLOT(slotSaveGame()));
	connect(m->btnLoadGame, SIGNAL(clicked()), this, SLOT(slotLoadGame()));
	connect(m->btnOptions, SIGNAL(clicked()), this, SLOT(slotOptions()));
	connect(m->btnQuit, SIGNAL(clicked()), this, SLOT(slotQuit()));

	delete m;
}

void LMain::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	painter.setPen(QPen(QColor(200, 200, 200)));
	painter.drawLine(0, 0, width(), 0);
	painter.end();
}

void LMain::slotNewGame()
{
	LNewGame* dialog = new LNewGame;

	bool flag = dialog->exec() == QDialog::Accepted;

	while (flag)
	{
		QString text = "Are you sure you want to start a new game:\n";
		QString gameType;
		int type = dialog->getGameType();

		switch (type)
		{
		case L_TYPE_BI:
			gameType = dialog->getName1() + " vs " + dialog->getName2();
			break;
		case L_TYPE_BOT:
			gameType = m->dlgOptions->getName() + " vs Computer";
			break;
		case L_TYPE_NET:
			gameType = m->dlgOptions->getName() + " vs Internet player";
			break;
		}

		LConfirm* confirm = new LConfirm(text + gameType);

		if (confirm->exec() == QDialog::Accepted)
		{
			LGame::newGame(dialog);

			m->teGameDesc->setText(gameType);

			if (type == L_TYPE_BI || type == L_TYPE_BOT)
			{
				m->btnSaveGame->setVisible(true);
			}
			else
			{
				m->btnSaveGame->setVisible(false);
			}

			flag = false;
		}
		else
		{
			flag = dialog->exec() == QDialog::Accepted;
		}

		delete confirm;
	}

	delete dialog;
}

void LMain::slotSaveGame()
{
	LSaveGame* dialog = new LSaveGame;
	dialog->exec();
	delete dialog;
}

void LMain::slotLoadGame()
{
	LLoadGame* dialog = new LLoadGame;

	bool flagDialog = dialog->exec() == QDialog::Accepted;

	while (flagDialog)
	{
		LGame* game = dialog->getSelectedSave();

		if (game)
		{
			LGame::setGame(game);
			m->btnSaveGame->setVisible(true);
			flagDialog = false;
		}
		else
		{
			flagDialog = dialog->exec() == QDialog::Accepted;
		}
	}

	delete dialog;
}

void LMain::slotOptions()
{
	m->dlgOptions->showDialog();
	m->dlgOptions->exec();
	m->dlgOptions->hide();
}

void LMain::slotQuit()
{
	LConfirm* confirm = new LConfirm("Are you sure you want to get out?");

	if (confirm->exec() == QDialog::Accepted)
	{
		qApp->quit();
	}

	delete confirm;
}

LGame* LMain::getGame() const
{
	return m->game;
}

void LMain::setGameDesc(QString string)
{
	m->teGameDesc->setText(string);
}

void LMain::appendGameDesc(QString string)
{
	m->teGameDesc->setText(string + "\n"+ m->teGameDesc->toPlainText());
}

void LMain::messageAlert(QString string)
{
	QMessageBox::information(nullptr, "Info", string);
}
