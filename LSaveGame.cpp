#include "LSaveGame.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

#include "LSaveKeeper.h"
#include "LConfirm.h"

LSaveGame::LSaveGame()
	:
	saveKeeper(LSaveKeeper::getInstance()),
	selectedSave(nullptr)
{
	QStringList names = saveKeeper->getNameSaves();

	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->saves = new QListWidget;
	this->lineEdit = new QLineEdit;
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	this->delButton = new QPushButton("Delete");
	this->saveButton = new QPushButton("save");

	for (int i = 0; i < names.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setText(names[i]);
		this->saves->addItem(item);
	}

	connect(this->saves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	connect(this->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&)));
	connect(this->delButton, SIGNAL(clicked()), SLOT(slotDeleteSave()));
	connect(this->saveButton, SIGNAL(clicked()), SLOT(accept()));
	connect(this->saveButton, SIGNAL(clicked()), SLOT(slotSave()));

	mainLayout->addWidget(this->saves);
	mainLayout->addWidget(this->lineEdit);
	mainLayout->addLayout(buttonLayout);

	buttonLayout->addWidget(this->delButton);
	buttonLayout->addWidget(this->saveButton);

	this->delButton->setEnabled(false);
	this->saveButton->setEnabled(false);

	this->setWindowTitle("Save Game");
	this->setLayout(mainLayout);
	this->setModal(true);
	this->show();
}

LSaveGame::~LSaveGame()
{
	delete this->selectedSave;
	delete this->saves;

	delete this->delButton;
	delete this->saveButton;
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

		this->delButton->setEnabled(true);
		this->saveButton->setText("Rewrite");
	}
	else if(this->selectedSave)
	{
		this->selectedSave->setSelected(false);
		this->selectedSave = nullptr;

		this->delButton->setEnabled(false);
		this->saveButton->setText("Save");
	}

	if (text == "")
	{
		this->saveButton->setEnabled(false);
	}
	else
	{
		this->saveButton->setEnabled(true);
	}
}

void LSaveGame::slotSave()
{
	if (this->selectedSave)
	{
		LConfirm* confirm = new LConfirm("Are you sure you want to rewrite the game: " + this->lineEdit->text());

		if (confirm->exec() == QDialog::Accepted)
		{
			saveKeeper->rewriteSave(this->lineEdit->text());
		}

		delete confirm;
	}
	else
	{
		LConfirm* confirm = new LConfirm("Are you sure you want to save the game: " + this->lineEdit->text());

		if (confirm->exec() == QDialog::Accepted)
		{
			saveKeeper->save(this->lineEdit->text());
		}

		delete confirm;
	}
}

void LSaveGame::slotDeleteSave()
{
	LConfirm* confirm = new LConfirm("Are you sure you want to delete the game: " + this->selectedSave->text());

	if (confirm->exec() == QDialog::Accepted)
	{
		saveKeeper->deleteSave(this->selectedSave->text());

		this->saves->removeItemWidget(this->selectedSave);

		delete this->selectedSave;
		this->selectedSave = nullptr;

		this->delButton->setEnabled(false);
		this->saveButton->setText("Save");
	}

	delete confirm;
}
