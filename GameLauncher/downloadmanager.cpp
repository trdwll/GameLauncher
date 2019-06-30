#include "downloadmanager.h"

#include <QApplication>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>
#include <QDateTime>

DownloadManager::DownloadManager(QObject* parent) :
    QObject(parent)
{
    connect(&m_manager, &QNetworkAccessManager::finished, this, &DownloadManager::OnReply);
}

bool DownloadManager::DownloadFile(const QUrl &url, const QString &FileName)
{
    if (url.isEmpty())
    {
        return false;
    }

	m_startTime = QDateTime::currentDateTime().toTime_t();

    QString path = qApp->applicationDirPath() + QDir::separator() + "tmp" + QDir::separator();
	QString file = path + (FileName.isEmpty() ? url.fileName() : FileName);

	qDebug() << "Download Path: " << path;
	qDebug() << "Download File Path: " << file;

	if (!QDir(path).exists())
	{
		QDir().mkdir(path);
	}

    m_file = new QFile(file);
    if (!m_file->open(QIODevice::WriteOnly))
    {
        delete m_file;
        m_file = nullptr;
        return false;
    }

    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    m_currentReply = m_manager.get(request);

    connect(m_currentReply, &QNetworkReply::readyRead, this, &DownloadManager::OnReadyRead);
	connect(m_currentReply, &QNetworkReply::downloadProgress, this, &DownloadManager::UpdateDownloadProgress);

    return true;
}

QString DownloadManager::GetTimeRemaining(qint64 bytesReceived, qint64 bytesTotal)
{
	uint difference = QDateTime::currentDateTime().toTime_t() - m_startTime;

	if (difference > 0) 
	{
		QString timeString;
		qreal timeRemaining = bytesTotal / (bytesReceived / difference);

		if (timeRemaining > 7200) 
		{
			timeRemaining /= 3600;
			int hours = int(timeRemaining + 0.5);

			timeString = hours > 1 ? tr("about %1 hours").arg(hours) : tr("about one hour");
		}
		else if (timeRemaining > 60)
		{
			timeRemaining /= 60;
			int minutes = int(timeRemaining + 0.5);

			timeString = minutes > 1 ? tr("%1 minutes").arg(minutes) : tr("1 minute");
		}
		else if (timeRemaining <= 60) 
		{
			int seconds = int(timeRemaining + 0.5);

			timeString = seconds > 1 ? tr("%1 seconds").arg(seconds) : tr("1 second");
		}
		
		return timeString;
	}

	return "unknown";
}

void DownloadManager::OnReadyRead()
{
    if (m_file)
    {
        m_file->write(m_currentReply->readAll());
    }
}

void DownloadManager::CancelDownload()
{
    if (m_currentReply)
    {
        m_currentReply->abort();
    }
}

void DownloadManager::OnReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        m_file->flush();
        m_file->close();
    }
    else
    {
        m_file->remove();
    }

    delete m_file;
    m_file = nullptr;
    reply->deleteLater();
}
