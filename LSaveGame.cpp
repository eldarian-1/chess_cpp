#include "LSaveGame.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

#include "LSaveKeeper.h"

LSaveGame::LSaveGame(LGame* game)
	:
	game(game),
	selectedSave(nullptr)
{
	QVector<QString> names = LSaveKeeper::getNameSaves();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->saves = new QListWidget;
	this->lineEdit = new QLineEdit;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	QPushButton* delButton = new QPushButton("Delete");
	QPushButton* saveButton = new QPushButton("save");

	for (int i = 0; i < names.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setText(names[i]);
		this->saves->addItem(item);
	}

	connect(this->saves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	connect(this->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&)));
	connect(delButton, SIGNAL(clicked()), SLOT(slotDeleteSave()));
	connect(saveButton, SIGNAL(clicked()), SLOT(accept()));
	connect(saveButton, SIGNAL(clicked()), SLOT(slotSave()));

	mainLayout->addWidget(this->saves);
	mainLayout->addWidget(this->lineEdit);
	mainLayout->addLayout(buttonLayout);

	buttonLayout->addWidget(delButton);
	buttonLayout->addWidget(saveButton);

	this->setWindowTitle("Load Game");
	this->setLayout(mainLayout);
	this->setModal(true);
	this->show();
}

LSaveGame::~LSaveGame()
{
	delete this->selectedSave;
	delete this->saves;
}

void LSaveGame::slotSelectSave(QListWidgetItem* item)
{
	this->selectedSave = item;
	this->lineEdit->setText(item->text());
}

void LSaveGame::slotTextChanged(const QString& text)
{
	int i;
	bool flag = false;

	for (i = 0; i < this->saves->count() && !flag; ++i)
	{
		flag = text == this->saves->item(i)->text();
	}

	--i;

	if (flag)
	{
		this->saves->item(i)->setSelected(true);
		this->selectedSave = this->saves->item(i);
	}
	else if(this->selectedSave)
	{
		this->selectedSave->setSelected(false);
		this->selectedSave = nullptr;
	}
}

void LSaveGame::slotSave()
{
	if (this->selectedSave)
	{
		LSaveKeeper::rewriteSave(this->lineEdit->text(), this->game);
	}
	else
	{
		LSaveKeeper::save(this->lineEdit->text(), this->game);
	}
}

void LSaveGame::slotDeleteSave()
{
	LSaveKeeper::deleteSave(this->selectedSave->text());

	this->saves->removeItemWidget(this->selectedSave);

	delete this->selectedSave;
	this->selectedSave = nullptr;
}
