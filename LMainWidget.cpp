#include "LMainWidget.h"

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

LMainWidget* LMainWidget::instance = nullptr;

LMainWidget* LMainWidget::getInstance(QApplication* app, QWidget* widget)
{
	if (!instance)
		instance = new LMainWidget(app, widget);

	return instance;
}

LMainWidget::LMainWidget(QApplication* app, QWidget* widget)
	:
	QWidget(widget),
	app(app),
	optionsDialog(LOptions::getInstance(app, this)),
	game(nullptr),
	desk(LDesk::getInstance(this)),
	newGame(new QPushButton(QIcon(":/LBQueen.png"), "New Game")),
	saveGame(new QPushButton(QIcon(":/LBElephant.png"), "Save Game")),
	loadGame(new QPushButton(QIcon(":/LBHorse.png"), "Load Game")),
	options(new QPushButton(QIcon(":/LBRook.png"), "Options")),
	quit(new QPushButton(QIcon(":/LBPawn.png"), "Quit")),
	pathList(new QTextEdit)
{
	this->setFixedSize(this->optionsDialog->getWidth(), this->optionsDialog->getHeight());
	this->setPalette(QPalette(QColor(255, 255, 255)));
	this->pathList->setDisabled(true);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	QVBoxLayout* pVBoxLayout = new QVBoxLayout;

	this->setLayout(pHBoxLayout);
	pHBoxLayout->setMargin(0);
	pHBoxLayout->setSpacing(0);
	pHBoxLayout->addLayout(pVBoxLayout, 1);
	pHBoxLayout->addWidget(this->desk, 6);

	pVBoxLayout->setMargin(10);
	pVBoxLayout->setSpacing(10);
	pVBoxLayout->addWidget(this->newGame);
	pVBoxLayout->addWidget(this->saveGame);
	pVBoxLayout->addWidget(this->loadGame);
	pVBoxLayout->addWidget(this->options);
	pVBoxLayout->addWidget(this->quit);
	pVBoxLayout->addWidget(this->pathList);

	this->setWindowTitle("Chess by Eldarian Studio");
	this->setWindowIcon(QIcon(":/LBKing.png"));
	this->saveGame->setVisible(false);

	connect(this->newGame, SIGNAL(clicked()), SLOT(slotNewGame()));
	connect(this->saveGame, SIGNAL(clicked()), SLOT(slotSaveGame()));
	connect(this->loadGame, SIGNAL(clicked()), SLOT(slotLoadGame()));
	connect(this->options, SIGNAL(clicked()), SLOT(slotOptions()));
	connect(this->quit, SIGNAL(clicked()), SLOT(slotQuit()));
}

void LMainWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	painter.setPen(QPen(QColor(200, 200, 200)));
	painter.drawLine(0, 0, this->width(), 0);
	painter.end();
}

void LMainWidget::slotNewGame()
{
	LNewGame* dialog = new LNewGame;

	if (dialog->exec() == QDialog::Accepted)
	{
		LGame::newGame(dialog);

		int type = dialog->getGameType();

		switch (type)
		{
		case L_TYPE_BI:
			this->pathList->setText("New Game: " + dialog->getName1() + " vs " + dialog->getName2());
			break;
		case L_TYPE_BOT:
			this->pathList->setText("New Game: " + this->optionsDialog->getName() + " vs Computer");
			break;
		case L_TYPE_NET:
			this->pathList->setText("New Game: " + this->optionsDialog->getName() + " vs Internet player");
			break;
		}

		if (type == L_TYPE_BI || type == L_TYPE_BOT)
		{
			this->saveGame->setVisible(true);
		}
		else
		{
			this->saveGame->setVisible(false);
		}
	}

	delete dialog;
}

void LMainWidget::slotSaveGame()
{
	LSaveGame* dialog = new LSaveGame;

	dialog->exec();

	delete dialog;
}

void LMainWidget::slotLoadGame()
{
	LLoadGame* dialog = new LLoadGame;

	bool flagDialog = dialog->exec() == QDialog::Accepted;

	while (flagDialog)
	{
		LGame* game = dialog->getSelectedSave();

		if (game)
		{
			LGame::setGame(game);
			this->saveGame->setVisible(true);
			flagDialog = false;
		}
		else
		{
			flagDialog = dialog->exec() == QDialog::Accepted;
		}
	}

	delete dialog;
}

void LMainWidget::slotOptions()
{
	this->optionsDialog->showDialog();
	this->optionsDialog->exec();
	this->optionsDialog->hide();
}

void LMainWidget::slotQuit()
{
	LConfirm* confirm = new LConfirm("Are you sure you want to get out?");

	if (confirm->exec() == QDialog::Accepted)
	{
		this->app->quit();
	}

	delete confirm;
}

LGame* LMainWidget::getGame() const
{
	return this->game;
}

void LMainWidget::setPathList(QString string)
{
	this->pathList->setText(string);
}

void LMainWidget::pathListAppend(QString string)
{
	this->pathList->setText(string + "\n"+ this->pathList->toPlainText());
}

void LMainWidget::messageAlert(QString string)
{
	QMessageBox::information(nullptr, "Info", string);
}
