#include "LWebClient.h"
#define LCHILD
#include "LClient.cpp"
#undef LCHILD

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

static const QString urlSite = "http://lchess.com/query/";
static const QString uriNewGame = "newgame.php";
static const QString uriSendPath = "sendpath.php";
static const QString uriGetPath = "getpath.php";

struct LWebClientPrivate : public LClientPrivate
{
	QNetworkAccessManager* manager;

	LWebClientPrivate(LClient* client);
	~LWebClientPrivate();
};

LWebClientPrivate::LWebClientPrivate(LClient* client)
	:
	LClientPrivate(),
	manager(new QNetworkAccessManager(client))
{

}

LWebClientPrivate::~LWebClientPrivate()
{
	delete manager;
}

LWebClient::LWebClient()
	: m(new LWebClientPrivate(this))
{
	connect(
		m->manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slotFinished(QNetworkReply*))
	);
}

LWebClient::~LWebClient()
{

}

void LWebClient::slotFinished(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		done(reply->url(), reply->readAll());
	}

	reply->deleteLater();
}

void LWebClient::download(const QUrl& url)
{
	QNetworkRequest request(url);
	QNetworkReply* reply = m->manager->get(request);

	connect(
		reply, SIGNAL(downloadProgress(qint64, qint64)),
		this, SIGNAL(signalDownloadProgress(qint64, qint64))
	);
}

void LWebClient::done(const QUrl& url, const QByteArray& array)
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

void LWebClient::newGame(QString name)
{
	m->player = "name=" + name;

	QString temp = (m->gameId != "") ? (m->gameId + "&") : ("");

	QString url = urlSite + uriNewGame + "?" + temp + m->clientId + "&" + m->player;
	download(QUrl(url));
}

void LWebClient::sendPath(LPath* p)
{
	m->path = "path=" + p->getText();
	QString url = urlSite + uriSendPath + "?" + m->gameId + "&" + m->clientId + "&" + m->path;
	download(QUrl(url));
}

void LWebClient::getPath()
{
	QString url = urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId;
	download(QUrl(url));
}
