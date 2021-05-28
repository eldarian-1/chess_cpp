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
	connect(this, SIGNAL(signalFindNewGame(QString)), SLOT(slotNewGame(QString)));
	connect(this, SIGNAL(signalGetNextPath()), SLOT(slotGetPath()));
	connect( m->manager, SIGNAL(finished(QNetworkReply*)), SLOT(slotFinished(QNetworkReply*)));
}

LWebClient::~LWebClient()
{
	disconnect(this, SIGNAL(signalFindNewGame(QString)), this, SLOT(slotNewGame(QString)));
	disconnect(this, SIGNAL(signalGetNextPath()), this, SLOT(slotGetPath()));
	disconnect(m->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)));
	delete m;
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
	m->manager->get(request);
}

void LWebClient::done(const QUrl& url, const QByteArray& array)
{
	QString string = array;
	QJsonDocument document = QJsonDocument::fromJson(array);
	QJsonObject jsonObject = document.object();

	QString gameId = (m->gameId != "") ? (m->gameId + "&") : ("");
	QString player = "name=" + m->player;

	if (url == urlSite + uriNewGame + "?" + gameId + m->clientId + "&" + player)
	{
		if (m->gameId == "")
		{
			m->gameId = "gameId=" + QString::number(jsonObject["gameId"].toInt());
		}

		LPlayer* player = LPlayer::playerFromJson(&jsonObject);
		if(player)
			emit signalNewGame(player);
		else
			emit signalFindNewGame(m->player);
	}
	else if (url == urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId)
	{
		LPath* path = LPath::pathFromJson(&jsonObject);
		if(path)
			emit signalGetPath(path);
		else
			emit signalGetNextPath();
	}
}

void LWebClient::sendPath(LPath* p)
{
	QString path = "path=" + p->toUriString();
	QString url = urlSite + uriSendPath + "?" + m->gameId + "&" + m->clientId + "&" + path;
	download(QUrl(url));
}

void LWebClient::slotNewGame(QString name)
{
	m->player = name;
	QString player = "name=" + name;
	QString gameId = (m->gameId != "") ? (m->gameId + "&") : ("");
	QString url = urlSite + uriNewGame + "?" + gameId + m->clientId + "&" + player;
	download(QUrl(url));
}

void LWebClient::slotGetPath()
{
	QString url = urlSite + uriGetPath + "?" + m->gameId + "&" + m->clientId;
	download(QUrl(url));
}
