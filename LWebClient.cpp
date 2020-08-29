#include "LWebClient.h"

#include "LPlayer.h"
#include "LPath.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

static const QString urlSite = "http://lchess.com/query/";
static const QString uriNewGame = "newgame.php";
static const QString uriSendPath = "sendpath.php";
static const QString uriGetPath = "getpath.php";

struct LWebClientPrivate
{
	QNetworkAccessManager* manager;
	QString gameId;
	QString clientId;
	QString player;

	LWebClientPrivate(LClient* client);
	~LWebClientPrivate();
};

LWebClientPrivate::LWebClientPrivate(LClient* client)
	:
	manager(new QNetworkAccessManager(client)),
	gameId(""),
	clientId("clientId=" + QString::number(rand())),
	player("")
{

}

LWebClientPrivate::~LWebClientPrivate()
{
	delete manager;
}

LWebClient::LWebClient()
	:
	LClient(),
	m(new LWebClientPrivate(this))
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
	QJsonDocument document = QJsonDocument::fromJson(array);
	QJsonObject jsonObject = document.object();

	QString gameId = (m->gameId != "") ? (m->gameId + "&") : ("");

	if (url == urlSite + uriNewGame + "?" + gameId + m->clientId + "&" + m->player)
	{
		if (m->gameId == "")
		{
			m->gameId = "gameId=" + QString::number(jsonObject["gameId"].toInt());
		}

		LPlayer* player = LPlayer::playerFromJson(&jsonObject);
		emit signalNewGame(player);
	}
	else if (url == urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId)
	{
		LPath* path = LPath::pathFromJson(&jsonObject);
		emit signalGetPath(path);
	}
}

void LWebClient::newGame(QString name)
{
	m->player = "name=" + name;
	QString gameId = (m->gameId != "") ? (m->gameId + "&") : ("");
	QString url = urlSite + uriNewGame + "?" + gameId + m->clientId + "&" + m->player;
	download(QUrl(url));
}

void LWebClient::sendPath(LPath* p)
{
	QString path = "path=" + p->toUriString();
	QString url = urlSite + uriSendPath + "?" + m->gameId + "&" + m->clientId + "&" + path;
	download(QUrl(url));
}

void LWebClient::getPath()
{
	QString url = urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId;
	download(QUrl(url));
}
