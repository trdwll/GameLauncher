#include "downloadmanager.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>

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

    QString path = QDir::currentPath() + QDir::separator() + (FileName.isEmpty() ? url.fileName() : FileName);
    qDebug() << path;
    m_file = new QFile(path);
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
