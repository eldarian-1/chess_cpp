#include "LLoadGame.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

#include "LSaveKeeper.h"
#include "LConfirm.h"

LLoadGame::LLoadGame()
	:
	saveKeeper(LSaveKeeper::getInstance()),
	selectedSave(nullptr)
{
	QStringList names = saveKeeper->getNameSaves();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->saves = new QListWidget;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	this->delButton = new QPushButton("Delete");
	this->loadButton = new QPushButton("Load");

	for (int i = 0; i < names.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setText(names[i]);
		this->saves->addItem(item);
	}

	connect(this->saves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	connect(delButton, SIGNAL(clicked()), SLOT(slotDeleteSave()));
	connect(loadButton, SIGNAL(clicked()), SLOT(accept()));

	mainLayout->addWidget(this->saves);
	mainLayout->addLayout(buttonLayout);

	buttonLayout->addWidget(this->delButton);
	buttonLayout->addWidget(this->loadButton);

	this->delButton->setEnabled(false);
	this->loadButton->setEnabled(false);

	this->setWindowTitle("Load Game");
	this->setLayout(mainLayout);
	this->setModal(true);
	this->show();
}

LLoadGame::~LLoadGame()
{
	delete this->selectedSave;
	delete this->saves;

	delete this->delButton;
	delete this->loadButton;
}

QString LLoadGame::getNameSelectedSave()
{
	return this->selectedSave->text();
}

LGame* LLoadGame::getSelectedSave()
{
	LGame* game = nullptr;

	LConfirm* confirm = new LConfirm("Are you sure you want to download the game: " + this->getNameSelectedSave());

	if (confirm->exec() == QDialog::Accepted)
	{
		game = saveKeeper->loadSave(this->selectedSave->text());
	}

	delete confirm;

	return game;
}

void LLoadGame::slotSelectSave(QListWidgetItem* item)
{
	this->selectedSave = item;

	this->delButton->setEnabled(true);
	this->loadButton->setEnabled(true);
}

void LLoadGame::slotDeleteSave()
{
	LConfirm* confirm = new LConfirm("Are you sure you want to delete the game: " + this->getNameSelectedSave());

	if (confirm->exec() == QDialog::Accepted)
	{
		saveKeeper->deleteSave(this->selectedSave->text());

		this->saves->removeItemWidget(this->selectedSave);

		delete this->selectedSave;
		this->selectedSave = nullptr;

		this->delButton->setEnabled(false);
		this->loadButton->setEnabled(false);
	}

	delete confirm;
}
