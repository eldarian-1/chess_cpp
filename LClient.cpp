#include "LClient.h"

#include "LWebClient.h"
#include "LTcpClient.h"
#include "LTcpServer.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

#include "LPlayer.h"
#include "LConst.h"
#include "LPath.h"

static const QString urlSite = "http://lchess.com/query/";
static const QString uriNewGame = "newgame.php";
static const QString uriSendPath = "sendpath.php";
static const QString uriGetPath = "getpath.php";

struct LClientPrivate
{
	QNetworkAccessManager* manager;
	QString gameId;
	QString clientId;
	QString player;
	QString path;

	LClientPrivate(LClient* client);
	~LClientPrivate();
};

LClientPrivate::LClientPrivate(LClient* client)
	:
	manager(new QNetworkAccessManager(client)),
	clientId("clientId=" + QString::number(rand())),
	gameId("")
{

}

LClientPrivate::~LClientPrivate()
{
	delete manager;
}

LClient::LClient(QObject* object)
	:
	QObject(object),
	m(new LClientPrivate(this))
{
	connect(
		m->manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slotFinished(QNetworkReply*))
	);
}

LClient* LClient::newClient(int type)
{
	switch (type)
	{
	case L_CLIENT_WEB:
		return new LWebClient;
	case L_CLIENT_TCP:
		return new LTcpClient;
	case L_SERVER_TCP:
		return new LTcpServer;
	}
}

LClient::~LClient()
{
	delete m;
}

void LClient::slotFinished(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		done(reply->url(), reply->readAll());
	}

	reply->deleteLater();
}

void LClient::download(const QUrl& url)
{
	QNetworkRequest request(url);
	QNetworkReply* reply = m->manager->get(request);

	connect(
		reply, SIGNAL(downloadProgress(qint64, qint64)),
		this, SIGNAL(signalDownloadProgress(qint64, qint64))
	);
}

void LClient::done(const QUrl& url, const QByteArray& array)
{
	QString string = array;
	QDomDocument* document = new QDomDocument;
	document->setContent(string);

	QString temp = (m->gameId != "") ? (m->gameId + "&") : ("");

	if (url == urlSite + uriNewGame + "?" + temp + m->clientId + "&" + m->player)
	{
		if (m->gameId == "")
		{
			m->gameId =
				"gameId="
				+ document
				->documentElement()
				.toElement()
				.childNodes()
				.at(0)
				.toElement()
				.text();
		}

		LPlayer* player = LPlayer::playerFromXml(document);
		emit signalNewGame(player);
	}
	else if (url == urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId)
	{
		LPath* path = LPath::pathFromXml(document);
		emit signalGetPath(path);
	}

	delete document;
}

void LClient::newGame(QString name)
{
	m->player = "name=" + name;

	QString temp = (m->gameId != "") ? (m->gameId + "&") : ("");

	QString url = urlSite + uriNewGame + "?" + temp + m->clientId + "&" + m->player;
	download(QUrl(url));
}

void LClient::sendPath(LPath* p)
{
	m->path = "path=" + p->getText();
	QString url = urlSite + uriSendPath + "?" + m->gameId + "&" + m->clientId + "&" + m->path;
	download(QUrl(url));
}

void LClient::getPath()
{
	QString url = urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId;
	download(QUrl(url));
}
