#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QNetworkAccessManager>

class QNetworkReply;
class QFile;

class DownloadManager : public QObject
{
    Q_OBJECT

public:
    explicit DownloadManager(QObject* parent = nullptr);

	const class QUrl m_DownloadURL = "http://www.ovh.net/files/10Mio.dat";

    // TODO: Add possibility to download all files in a directory instead of single files
    bool DownloadFile(const QUrl& url, const QString& FileName = "");
	QString GetTimeRemaining(qint64 bytesReceived, qint64 bytesTotal);

	void InitInstall();

public slots:
    void CancelDownload();

signals:
    void UpdateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void OnReadyRead();
    void OnReply(QNetworkReply* reply);

private:
    QNetworkReply* m_currentReply;
    QFile* m_file;
    QNetworkAccessManager m_manager;

	uint m_startTime;
};

#endif // DOWNLOADMANAGER_H
