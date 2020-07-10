#include "LOptions.h"

#include "LConst.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>

LOptions* LOptions::instance = nullptr;

LOptions* LOptions::getInstance(QWidget* mainWidget, QWidget* widget)
{
	if (!instance)
		instance = new LOptions(mainWidget, widget);

	return instance;
}

LOptions::LOptions(QWidget* mainWidget, QWidget* widget)
	:
	QDialog(widget),
	mainWidget(mainWidget),

	playerName("Player"),
	windowSize(L_SIZE_HD),
	windowWidth(L_SIZE_HD_WIDTH),
	windowHeight(L_SIZE_HD_HEIGHT),

	playerEdit(new QLineEdit(playerName)),
	winSizeNHD(new QRadioButton("nHD - ")),
	winSizeFWVGA(new QRadioButton("FWVGA - ")),
	winSizeHD(new QRadioButton("HD - ")),
	winSizeHDP(new QRadioButton("HD+ - ")),
	winSizeFHD(new QRadioButton("FullHD - ")),
	winSizeFULL(new QRadioButton("Full screen"))
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	QLabel* labelName = new QLabel("Player");
	QGroupBox* screenOption = new QGroupBox("Screen Option");
	QVBoxLayout* screenLayout = new QVBoxLayout;
	QPushButton* apply = new QPushButton("Apply");

	mainLayout->addWidget(labelName);
	mainLayout->addWidget(this->playerEdit);
	mainLayout->addWidget(screenOption);
	mainLayout->addWidget(apply);

	screenOption->setLayout(screenLayout);
	screenLayout->addWidget(this->winSizeNHD);
	screenLayout->addWidget(this->winSizeFWVGA);
	screenLayout->addWidget(this->winSizeHD);
	screenLayout->addWidget(this->winSizeHDP);
	screenLayout->addWidget(this->winSizeFHD);
	screenLayout->addWidget(this->winSizeFULL);

	this->winSizeHD->setChecked(true);

	this->setLayout(mainLayout);
	this->setWindowTitle("Options");

	connect(apply, SIGNAL(clicked()), this, SLOT(slotAccepted()));
	connect(this, SIGNAL(finished(int)), this, SLOT(slotFinished()));
}

void LOptions::showDialog()
{
	this->setModal(true);
	this->show();
}

QString LOptions::getName() const
{
	return this->playerName;
}

int LOptions::getWidth() const
{
	return this->windowWidth;
}

int LOptions::getHeight() const
{
	return this->windowHeight;
}

void LOptions::slotAccepted()
{
	this->playerName = this->playerEdit->text();

	if (this->windowSize == L_SIZE_FULL && !this->winSizeFULL->isChecked())
	{
		this->mainWidget->hide();
		this->mainWidget->showNormal();
	}

	if (this->winSizeNHD->isChecked())
	{
		if (this->windowSize != L_SIZE_NHD)
		{
			this->windowSize = L_SIZE_NHD;
			this->windowWidth = L_SIZE_NHD_WIDTH;
			this->windowHeight = L_SIZE_NHD_HEIGHT;
		}
	}
	else if (this->winSizeFWVGA->isChecked())
	{
		if (this->windowSize != L_SIZE_FWVGA)
		{
			this->windowSize = L_SIZE_FWVGA;
			this->windowWidth = L_SIZE_FWVGA_WIDTH;
			this->windowHeight = L_SIZE_FWVGA_HEIGHT;
		}
	}
	else if (this->winSizeHD->isChecked())
	{
		if (this->windowSize != L_SIZE_HD)
		{
			this->windowSize = L_SIZE_HD;
			this->windowWidth = L_SIZE_HD_WIDTH;
			this->windowHeight = L_SIZE_HD_HEIGHT;
		}
	}
	else if (this->winSizeHDP->isChecked())
	{
		if (this->windowSize != L_SIZE_HDP)
		{
			this->windowSize = L_SIZE_HDP;
			this->windowWidth = L_SIZE_HDP_WIDTH;
			this->windowHeight = L_SIZE_HDP_HEIGHT;
		}
	}
	else if (this->winSizeFHD->isChecked())
	{
		if (this->windowSize != L_SIZE_FHD)
		{
			this->windowSize = L_SIZE_FHD;
			this->windowWidth = L_SIZE_FHD_WIDTH;
			this->windowHeight = L_SIZE_FHD_HEIGHT;
		}
	}
	else if (this->winSizeFULL->isChecked())
	{
		if (this->windowSize != L_SIZE_FULL)
		{
			this->windowSize = L_SIZE_FULL;
			this->mainWidget->hide();
			this->mainWidget->showFullScreen();
		}
	}

	if (this->windowSize != L_SIZE_FULL)
	{
		this->mainWidget->setFixedSize(this->windowWidth, this->windowHeight);
	}


}

void LOptions::slotFinished()
{
	this->playerEdit->setText(this->playerName);

	switch(this->windowSize)
	{
	case L_SIZE_NHD:
		this->winSizeNHD->setChecked(true);
		break;
	case L_SIZE_FWVGA:
		this->winSizeFWVGA->setChecked(true);
		break;
	case L_SIZE_HD:
		this->winSizeHD->setChecked(true);
		break;
	case L_SIZE_HDP:
		this->winSizeHDP->setChecked(true);
		break;
	case L_SIZE_FHD:
		this->winSizeFHD->setChecked(true);
		break;
	case L_SIZE_FULL:
		this->winSizeFULL->setChecked(true);
		break;
	}
}
