#include "LMainWidget.h"

#include "LConst.h"
#include "LDesk.h"
#include "LGame.h"
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
	optionsDIalog(LOptions::getInstance(app, this)),
	game(nullptr),
	desk(LDesk::getInstance(this)),
	newGame(new QPushButton(QIcon(":/LBQueen.png"), "New Game")),
	saveGame(new QPushButton(QIcon(":/LBElephant.png"), "Save Game")),
	loadGame(new QPushButton(QIcon(":/LBHorse.png"), "Load Game")),
	options(new QPushButton(QIcon(":/LBRook.png"), "Options")),
	quit(new QPushButton(QIcon(":/LBPawn.png"), "Quit")),
	pathList(new QTextEdit)
{
	this->setFixedSize(this->optionsDIalog->getWidth(), this->optionsDIalog->getHeight());
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
	connect(this->quit, SIGNAL(clicked()), app, SLOT(quit()));
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

		switch (dialog->getGameType())
		{
		case L_TYPE_BI:
			this->pathList->setText("New Game: " + dialog->getName1() + " vs " + dialog->getName2());
			break;
		case L_TYPE_BOT:
			this->pathList->setText("New Game: " + this->optionsDIalog->getName() + " vs Computer");
			break;
		case L_TYPE_NET:
			this->pathList->setText("New Game: " + this->optionsDIalog->getName() + " vs Internet player");
			break;
		}

		this->saveGame->setVisible(true);
	}

	delete dialog;
}

void LMainWidget::slotSaveGame()
{
	LSaveGame* dialog = new LSaveGame(this->game);

	dialog->exec();

	delete dialog;
}

void LMainWidget::slotLoadGame()
{
	LLoadGame* dialog = new LLoadGame;

	if (dialog->exec() == QDialog::Accepted)
	{
		LGame::setGame(dialog->getSelectedSave());
	}

	delete dialog;
}

void LMainWidget::slotOptions()
{
	this->optionsDIalog->showDialog();
	this->optionsDIalog->exec();
	this->optionsDIalog->hide();
}

LGame* LMainWidget::getGame() const
{
	return this->game;
}

void LMainWidget::pathListAppend(QString string)
{
	this->pathList->setText(string + "\n"+ this->pathList->toPlainText());
}

void LMainWidget::messageAlert(QString string)
{
	QMessageBox::information(nullptr, "Info", string);
}
