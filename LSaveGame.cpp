#include "LSaveGame.h"

#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QPushButton>

#include "LSaveKeeper.h"
#include "LConfirm.h"

class LSaveGamePrivate
{
public:
	LSaveKeeper* saveKeeper;

	QListWidgetItem* lstWgtSelected;
	QListWidget* lstSaves;

	QVBoxLayout* lytMain;
	QHBoxLayout* lytButton;

	QLineEdit* leSaveName;

	QPushButton* btnDelete;
	QPushButton* btnSave;

	LSaveGamePrivate();
	~LSaveGamePrivate();
};

LSaveGamePrivate::LSaveGamePrivate()
	:
	saveKeeper(LSaveKeeper::getInstance()),
	lstWgtSelected(nullptr),
	lstSaves(new QListWidget),
	lytMain(new QVBoxLayout),
	lytButton(new QHBoxLayout),
	leSaveName(new QLineEdit),
	btnDelete(new QPushButton("Delete")),
	btnSave(new QPushButton("Save"))
{
	QStringList names = saveKeeper->getNameSaves();

	for (int i = 0; i < names.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem;
		item->setText(names[i]);
		lstSaves->addItem(item);
	}

	lytMain->addWidget(lstSaves);
	lytMain->addWidget(leSaveName);
	lytMain->addLayout(lytButton);

	lytButton->addWidget(btnDelete);
	lytButton->addWidget(btnSave);

	btnDelete->setEnabled(false);
	btnSave->setEnabled(false);
}

LSaveGamePrivate::~LSaveGamePrivate()
{
	while (lstSaves->count())
	{
		QListWidgetItem* item = lstSaves->item(0);
		lstSaves->removeItemWidget(item);
		delete item;
	}

	delete leSaveName;
	delete btnDelete;
	delete btnSave;
	delete lytButton;
	delete lstSaves;
	delete lytMain;
}

LSaveGame::LSaveGame()
	:
	m(new LSaveGamePrivate)
{
	connect(m->lstSaves, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(slotSelectSave(QListWidgetItem*)));
	connect(m->leSaveName, SIGNAL(textChanged(const QString&)), SLOT(slotTextChanged(const QString&)));
	connect(m->btnDelete, SIGNAL(clicked()), SLOT(slotDeleteSave()));
	connect(m->btnSave, SIGNAL(clicked()), SLOT(accept()));
	connect(m->btnSave, SIGNAL(clicked()), SLOT(slotSave()));

	setWindowTitle("Save Game");
	setLayout(m->lytMain);
	setModal(true);
	show();
}

LSaveGame::~LSaveGame()
{
	disconnect(m->lstSaves, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotSelectSave(QListWidgetItem*)));
	disconnect(m->leSaveName, SIGNAL(textChanged(const QString&)), this, SLOT(slotTextChanged(const QString&)));
	disconnect(m->btnDelete, SIGNAL(clicked()), this, SLOT(slotDeleteSave()));
	disconnect(m->btnSave, SIGNAL(clicked()), this, SLOT(accept()));
	disconnect(m->btnSave, SIGNAL(clicked()), this, SLOT(slotSave()));

	delete m;
}

void LSaveGame::slotSelectSave(QListWidgetItem* item)
{
	m->lstWgtSelected = item;
	m->leSaveName->setText(item->text());
}

void LSaveGame::slotTextChanged(const QString& text)
{
	int i;
	bool flag = false;

	for (i = 0; i < m->lstSaves->count() && !flag; ++i)
	{
		flag = text == m->lstSaves->item(i)->text();
	}

	--i;

	if (flag)
	{
		m->lstSaves->item(i)->setSelected(true);
		m->lstWgtSelected = m->lstSaves->item(i);

		m->btnDelete->setEnabled(true);
		m->btnSave->setText("Rewrite");
	}
	else if(m->lstWgtSelected)
	{
		m->lstWgtSelected->setSelected(false);
		m->lstWgtSelected = nullptr;

		m->btnDelete->setEnabled(false);
		m->btnSave->setText("Save");
	}

	if (text == "")
	{
		m->btnSave->setEnabled(false);
	}
	else
	{
		m->btnSave->setEnabled(true);
	}
}

void LSaveGame::slotSave()
{
	if (m->lstWgtSelected)
	{
		LConfirm* confirm = new LConfirm("Are you sure you want to rewrite the game: " + m->leSaveName->text());

		if (confirm->exec() == QDialog::Accepted)
		{
			m->saveKeeper->rewriteSave(m->leSaveName->text());
		}

		delete confirm;
	}
	else
	{
		LConfirm* confirm = new LConfirm("Are you sure you want to save the game: " + m->leSaveName->text());

		if (confirm->exec() == QDialog::Accepted)
		{
			m->saveKeeper->save(m->leSaveName->text());
		}

		delete confirm;
	}
}

void LSaveGame::slotDeleteSave()
{
	LConfirm* confirm = new LConfirm("Are you sure you want to delete the game: " + m->lstWgtSelected->text());

	if (confirm->exec() == QDialog::Accepted)
	{
		m->saveKeeper->deleteSave(m->lstWgtSelected->text());

		m->lstSaves->removeItemWidget(m->lstWgtSelected);

		delete m->lstWgtSelected;
		m->lstWgtSelected = nullptr;

		m->btnDelete->setEnabled(false);
		m->btnSave->setText("Save");
	}

	delete confirm;
}
