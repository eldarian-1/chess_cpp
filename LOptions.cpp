#include "LOptions.h"

#include "LConst.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>

LOptions* LOptions::instance = nullptr;

class LOptionsPrivate
{
public:
	QWidget* wgtMain;

	QString playerName;
	int windowSize;
	int windowWidth;
	int windowHeight;

	QVBoxLayout* lytMain;
	QLabel* lblPlayer;
	QGroupBox* gbScreen;
	QVBoxLayout* lytSizes;
	QPushButton* btnApply;

	QLineEdit* leName;
	QRadioButton* rdSizeNHD;
	QRadioButton* rdSizeFWVGA;
	QRadioButton* rdSizeHD;
	QRadioButton* rdSizeHDP;
	QRadioButton* rdSizeFHD;
	QRadioButton* rdSizeFULL;

	LOptionsPrivate(QWidget* widget);
	~LOptionsPrivate();
};

LOptionsPrivate::LOptionsPrivate(QWidget* widget)
	:
	wgtMain(widget),

	playerName("Player"),
	windowSize(L_SIZE_HD),
	windowWidth(L_SIZE_HD_WIDTH),
	windowHeight(L_SIZE_HD_HEIGHT),

	lytMain(new QVBoxLayout),
	lblPlayer(new QLabel("Player")),
	gbScreen(new QGroupBox("Screen Option")),
	lytSizes(new QVBoxLayout),
	btnApply(new QPushButton("Apply")),

	leName(new QLineEdit(playerName)),
	rdSizeNHD(new QRadioButton("nHD - 640x360")),
	rdSizeFWVGA(new QRadioButton("FWVGA - 854x480")),
	rdSizeHD(new QRadioButton("HD - 1280x720")),
	rdSizeHDP(new QRadioButton("HD+ - 1600x900")),
	rdSizeFHD(new QRadioButton("FullHD - 1920x1080")),
	rdSizeFULL(new QRadioButton("Full screen"))
{
	lytMain->addWidget(lblPlayer);
	lytMain->addWidget(leName);
	lytMain->addWidget(gbScreen);
	lytMain->addWidget(btnApply);

	gbScreen->setLayout(lytSizes);
	lytSizes->addWidget(rdSizeNHD);
	lytSizes->addWidget(rdSizeFWVGA);
	lytSizes->addWidget(rdSizeHD);
	lytSizes->addWidget(rdSizeHDP);
	lytSizes->addWidget(rdSizeFHD);
	lytSizes->addWidget(rdSizeFULL);

	rdSizeHD->setChecked(true);
}

LOptionsPrivate::~LOptionsPrivate()
{
	delete lblPlayer;
	delete btnApply;

	delete leName;
	delete rdSizeNHD;
	delete rdSizeFWVGA;
	delete rdSizeHD;
	delete rdSizeHDP;
	delete rdSizeFHD;
	delete rdSizeFULL;

	delete lytSizes;
	delete gbScreen;
	delete lytMain;
}

LOptions* LOptions::getInstance(QWidget* mainWidget, QWidget* widget)
{
	if (!instance)
		instance = new LOptions(mainWidget, widget);

	return instance;
}

LOptions::LOptions(QWidget* mainWidget, QWidget* widget)
	:
	QDialog(widget),
	m(new LOptionsPrivate(mainWidget))
{
	connect(m->btnApply, SIGNAL(clicked()), SLOT(slotAccepted()));
	connect(this, SIGNAL(finished(int)), SLOT(slotFinished()));

	setLayout(m->lytMain);
	setWindowTitle("Options");
}

LOptions::~LOptions()
{
	delete m;
}

void LOptions::showDialog()
{
	setModal(true);
	show();
}

QString LOptions::getName() const
{
	return m->playerName;
}

int LOptions::getWidth() const
{
	return m->windowWidth;
}

int LOptions::getHeight() const
{
	return m->windowHeight;
}

void LOptions::slotAccepted()
{
	m->playerName = m->leName->text();

	if (m->windowSize == L_SIZE_FULL && !m->rdSizeFULL->isChecked())
	{
		m->wgtMain->hide();
		m->wgtMain->showNormal();
	}

	if (m->rdSizeNHD->isChecked())
	{
		if (m->windowSize != L_SIZE_NHD)
		{
			m->windowSize = L_SIZE_NHD;
			m->windowWidth = L_SIZE_NHD_WIDTH;
			m->windowHeight = L_SIZE_NHD_HEIGHT;
		}
	}
	else if (m->rdSizeFWVGA->isChecked())
	{
		if (m->windowSize != L_SIZE_FWVGA)
		{
			m->windowSize = L_SIZE_FWVGA;
			m->windowWidth = L_SIZE_FWVGA_WIDTH;
			m->windowHeight = L_SIZE_FWVGA_HEIGHT;
		}
	}
	else if (m->rdSizeHD->isChecked())
	{
		if (m->windowSize != L_SIZE_HD)
		{
			m->windowSize = L_SIZE_HD;
			m->windowWidth = L_SIZE_HD_WIDTH;
			m->windowHeight = L_SIZE_HD_HEIGHT;
		}
	}
	else if (m->rdSizeHDP->isChecked())
	{
		if (m->windowSize != L_SIZE_HDP)
		{
			m->windowSize = L_SIZE_HDP;
			m->windowWidth = L_SIZE_HDP_WIDTH;
			m->windowHeight = L_SIZE_HDP_HEIGHT;
		}
	}
	else if (m->rdSizeFHD->isChecked())
	{
		if (m->windowSize != L_SIZE_FHD)
		{
			m->windowSize = L_SIZE_FHD;
			m->windowWidth = L_SIZE_FHD_WIDTH;
			m->windowHeight = L_SIZE_FHD_HEIGHT;
		}
	}
	else if (m->rdSizeFULL->isChecked())
	{
		if (m->windowSize != L_SIZE_FULL)
		{
			m->windowSize = L_SIZE_FULL;
			m->wgtMain->hide();
			m->wgtMain->showFullScreen();
		}
	}

	if (m->windowSize != L_SIZE_FULL)
	{
		m->wgtMain->setFixedSize(m->windowWidth, m->windowHeight);

		m->wgtMain->setGeometry(
			QStyle::alignedRect(
				Qt::LeftToRight,
				Qt::AlignCenter,
				m->wgtMain->size(),
				QApplication::desktop()->screenGeometry()
			)
		);
	}

}

void LOptions::slotFinished()
{
	m->leName->setText(m->playerName);

	switch(m->windowSize)
	{
	case L_SIZE_NHD:
		m->rdSizeNHD->setChecked(true);
		break;
	case L_SIZE_FWVGA:
		m->rdSizeFWVGA->setChecked(true);
		break;
	case L_SIZE_HD:
		m->rdSizeHD->setChecked(true);
		break;
	case L_SIZE_HDP:
		m->rdSizeHDP->setChecked(true);
		break;
	case L_SIZE_FHD:
		m->rdSizeFHD->setChecked(true);
		break;
	case L_SIZE_FULL:
		m->rdSizeFULL->setChecked(true);
		break;
	}
}
