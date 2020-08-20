#include "LLoadGame.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

#include "LSaveKeeper.h"
#include "LConfirm.h"

class LLoadGamePrivate
{
public:
	LSaveKeeper* saveKeeper;

	QListWidgetItem* lstWgtSelected;
	QListWidget* lstSaves;

	QVBoxLayout* lytMain;
	QHBoxLayout* lytButton;

	QPushButton* btnDelete;
	QPushButton* btnLoad;

	LLoadGamePrivate();
	~LLoadGamePrivate();
};

LLoadGamePrivate::LLoadGamePrivate()
	:
	saveKeeper(LSaveKeeper::getInstance()),
	lstWgtSelected(nullptr),
	lstSaves(new QListWidget),
	lytMain(new QVBoxLayout),
	lytButton(new QHBoxLayout),
	btnDelete(new QPushButton("Delete")),
	btnLoad(new QPushButton("Load"))
{
	QStringList names = saveKeeper->getNameSaves();

	for (int i = 0; i < names.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setText(names[i]);
		lstSaves->addItem(item);
	}

	lytMain->addWidget(lstSaves);
	lytMain->addLayout(lytButton);

	lytButton->addWidget(btnDelete);
	lytButton->addWidget(btnLoad);

	btnDelete->setEnabled(false);
	btnLoad->setEnabled(false);
}

LLoadGamePrivate::~LLoadGamePrivate()
{
	while (lstSaves->count())
	{
		QListWidgetItem* item = lstSaves->item(0);
		lstSaves->removeItemWidget(item);
		delete item;
	}

	delete btnDelete;
	delete btnLoad;
	delete lytButton;
	delete lstSaves;
	delete lytMain;
}

LLoadGame::LLoadGame()
	:
	m(new LLoadGamePrivate)
{
	connect(m->lstSaves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	connect(m->btnDelete, SIGNAL(clicked()), SLOT(slotDeleteSave()));
	connect(m->btnLoad, SIGNAL(clicked()), SLOT(accept()));

	setWindowTitle("Load Game");
	setLayout(m->lytMain);
	setModal(true);
	show();
}

LLoadGame::~LLoadGame()
{
	disconnect(m->lstSaves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	disconnect(m->btnDelete, SIGNAL(clicked()), this, SLOT(slotDeleteSave()));
	disconnect(m->btnLoad, SIGNAL(clicked()), this, SLOT(accept()));

	delete m;
}

QString LLoadGame::getNameSelectedSave()
{
	return m->lstWgtSelected->text();
}

LGame* LLoadGame::getSelectedSave()
{
	LGame* game = nullptr;

	LConfirm* confirm = new LConfirm("Are you sure you want to download the game: " + getNameSelectedSave());

	if (confirm->exec() == QDialog::Accepted)
	{
		game = m->saveKeeper->loadSave(m->lstWgtSelected->text());
	}

	delete confirm;

	return game;
}

void LLoadGame::slotSelectSave(QListWidgetItem* item)
{
	m->lstWgtSelected = item;

	m->btnDelete->setEnabled(true);
	m->btnLoad->setEnabled(true);
}

void LLoadGame::slotDeleteSave()
{
	LConfirm* confirm = new LConfirm("Are you sure you want to delete the game: " + getNameSelectedSave());

	if (confirm->exec() == QDialog::Accepted)
	{
		m->saveKeeper->deleteSave(m->lstWgtSelected->text());

		m->lstSaves->removeItemWidget(m->lstWgtSelected);

		delete m->lstWgtSelected;
		m->lstWgtSelected = nullptr;

		m->btnDelete->setEnabled(false);
		m->btnLoad->setEnabled(false);
	}

	delete confirm;
}
