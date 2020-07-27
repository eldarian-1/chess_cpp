#include "LClient.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

#include "LPlayer.h"
#include "LPath.h"

QString LClient::urlSite = "http://lchess.com/query/";
QString LClient::uriConnect = "connect.php";
QString LClient::uriNewGame = "newgame.php";
QString LClient::uriSendPath = "sendpath.php";
QString LClient::uriGetPath = "getpath.php";

LClient* LClient::instance = nullptr;

LClient::LClient(QObject* object)
	:
	QObject(object),
	networkAccessManager(new QNetworkAccessManager(this))
{
	int cId = rand();
	this->clientId.setNum(cId);
	this->clientId = "clientId=" + this->clientId;

	this->gameId = "";

	connect(
		this->networkAccessManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slotFinished(QNetworkReply*))
	);
}

LClient* LClient::getInstance()
{
	if (!instance)
	{
		instance = new LClient;
	}

	return instance;
}

void LClient::slotFinished(QNetworkReply* reply)
{
	disconnect(
		reply, SIGNAL(downloadProgress(qint64, qint64)),
		this, SIGNAL(signalDownloadProgress(qint64, qint64))
	);

	if (reply->error() != QNetworkReply::NoError)
	{
		emit signalConnecting(false);
	}
	else
	{
		this->done(reply->url(), reply->readAll());
	}

	reply->deleteLater();
}

void LClient::download(const QUrl& url)
{
	QNetworkRequest request(url);
	QNetworkReply* reply = this->networkAccessManager->get(request);

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

	QString temp = (this->gameId != "") ? (this->gameId + "&") : ("");

	if (url == urlSite + uriConnect + "?" + this->clientId)
	{
		emit signalConnecting(true);
	}
	else if (url == urlSite + uriNewGame + "?" + temp + this->clientId + "&" + this->player)
	{
		if (this->gameId == "")
		{
			this->gameId =
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
	else if (url == urlSite + uriGetPath + "?" + this->gameId + "&" + this->clientId)
	{
		LPath* path = LPath::pathFromXml(document);
		emit signalGetPath(path);
	}

	delete document;
}

void LClient::connecting()
{
	QString url = urlSite + uriConnect;
	this->download(QUrl(url));
}

void LClient::newGame(QString name)
{
	this->player = "name=" + name;

	QString temp = (this->gameId != "") ? (this->gameId + "&") : ("");

	QString url = urlSite + uriNewGame + "?" + temp + this->clientId + "&" + this->player;
	this->download(QUrl(url));
}

void LClient::sendPath(LPath* p)
{
	this->path = "path=" + p->getText();
	QString url = urlSite + uriSendPath + "?" + this->gameId + "&" + this->clientId + "&" + this->path;
	this->download(QUrl(url));
}

void LClient::getPath()
{
	QString url = urlSite + uriGetPath + "?" + this->gameId + "&" + this->clientId;
	this->download(QUrl(url));
}
