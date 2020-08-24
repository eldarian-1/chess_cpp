#pragma once

#include "LClient.h"

class QNetworkReply;

struct LWebClientPrivate;

class LWebClient : public LClient
{
	Q_OBJECT

private:
	friend class LClient;
	LWebClientPrivate* m;

protected:
	LWebClient();

public:
	~LWebClient();

	virtual void newGame(QString name) override;
	virtual void sendPath(LPath* path) override;
	virtual void getPath() override;

private:
	void download(const QUrl& url);

private slots:
	void slotFinished(QNetworkReply* reply);

private:
	void done(const QUrl& url, const QByteArray& array);

};
