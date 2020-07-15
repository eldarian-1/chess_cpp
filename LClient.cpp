#include "LClient.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QDomDocument>

#include "LPlayer.h"
#include "LPath.h"

QString LClient::urlSite = "http://lchess.com/";
QString LClient::uriConnect = "connect.xml";
QString LClient::uriNewGame = "newgame.xml";
QString LClient::uriSendPath = "sendpath.xml";
QString LClient::uriGetPath = "getpath.xml";

LClient* LClient::instance = nullptr;

LClient::LClient(QObject* object)
	:
	QObject(object),
	networkAccessManager(new QNetworkAccessManager(this))
{
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

	if (url == urlSite + uriConnect)
	{
		emit signalConnecting(true);
	}
	else if (url == urlSite + uriNewGame + this->player)
	{
		LPlayer* player = LPlayer::playerFromXml(document);
		emit signalNewGame(player);
	}
	else if (url == urlSite + uriGetPath)
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

void LClient::newGame(LPlayer* p)
{
	this->player = p->getText();
	QString url = urlSite + uriNewGame + this->player;
	this->download(QUrl(url));
}

void LClient::sendPath(LPath* p)
{
	this->path = p->getText();
	QString url = urlSite + uriSendPath + this->path;
	this->download(QUrl(url));
}

void LClient::getPath()
{
	QString url = urlSite + uriGetPath;
	this->download(QUrl(url));
}
