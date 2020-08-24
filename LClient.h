#pragma once

#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;

class QDomDocument;

class LPlayer;
class LPath;

struct LClientPrivate;

class LClient :
	public QObject
{
	Q_OBJECT

private:
	LClientPrivate* m;

	LClient(QObject* object = nullptr);

public:
	static LClient* newClient(int type);
	~LClient();

signals:
	void signalNewGame(LPlayer* player);
	void signalGetPath(LPath* path);

private slots:
	void slotFinished(QNetworkReply* reply);

private:
	void download(const QUrl& url);
	void done(const QUrl& url, const QByteArray& array);

public:
	void newGame(QString name);
	void sendPath(LPath* path);
	void getPath();

};
