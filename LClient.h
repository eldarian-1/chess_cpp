#pragma once

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;

class QDomDocument;

class LPlayer;
class LPath;

class LClient :
	public QObject
{
	Q_OBJECT

private:
	static QString urlSite;
	static QString uriConnect;
	static QString uriNewGame;
	static QString uriSendPath;
	static QString uriGetPath;

	static LClient* instance;

	QNetworkAccessManager* networkAccessManager;

	QString player;
	QString path;

	LClient(QObject* object = nullptr);

public:
	static LClient* getInstance();

signals:
	void signalDownloadProgress(qint64, qint64);
	void signalConnecting(bool isConnect);
	void signalNewGame(LPlayer* player);
	void signalGetPath(LPath* path);

private slots:
	void slotFinished(QNetworkReply* reply);

private:
	void download(const QUrl& url);
	void done(const QUrl& url, const QByteArray& array);

public:
	void connecting();
	void newGame(LPlayer* player);
	void sendPath(LPath* path);
	void getPath();

};
