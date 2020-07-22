#include "LLoadGame.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

#include "LSaveKeeper.h"

LLoadGame::LLoadGame()
	:
	selectedSave(nullptr)
{
	QStringList names = LSaveKeeper::getNameSaves();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->saves = new QListWidget;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	QPushButton* delButton = new QPushButton("Delete");
	QPushButton* loadButton = new QPushButton("Load");

	for (int i = 0; i < names.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setText(names[i]);
		this->saves->addItem(item);

		if (i == 0)
		{
			item->setSelected(true);
			this->selectedSave = item;
		}
	}

	connect(this->saves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	connect(delButton, SIGNAL(clicked()), SLOT(slotDeleteSave()));
	connect(loadButton, SIGNAL(clicked()), SLOT(accept()));

	mainLayout->addWidget(this->saves);
	mainLayout->addLayout(buttonLayout);

	buttonLayout->addWidget(delButton);
	buttonLayout->addWidget(loadButton);

	this->setWindowTitle("Load Game");
	this->setLayout(mainLayout);
	this->setModal(true);
	this->show();
}

LLoadGame::~LLoadGame()
{
	delete this->selectedSave;
	delete this->saves;
}

LGame* LLoadGame::getSelectedSave()
{
	LGame* game = nullptr;

	if (this->selectedSave)
	{
		game = LSaveKeeper::loadSave(this->selectedSave->text());
	}

	return game;
}

void LLoadGame::slotSelectSave(QListWidgetItem* item)
{
	this->selectedSave = item;
}

void LLoadGame::slotDeleteSave()
{
	if (this->selectedSave)
	{
		LSaveKeeper::deleteSave(this->selectedSave->text());

		this->saves->removeItemWidget(this->selectedSave);

		delete this->selectedSave;
		this->selectedSave = nullptr;
	}
}
