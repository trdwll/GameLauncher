//#include "http.h"

//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QFile>
//#include <QTimer>

//HTTP::HTTP(QObject *parent) : QObject(parent)
//{

//}

//HTTP::~HTTP() {}


//void HTTP::Init()
//{
//    connect(m_Manager, &QNetworkAccessManager::finished, this, &HTTP::FileFinished);
//}

//void HTTP::DownloadFile(const QString &Directory, const QString &File)
//{

//}

//void HTTP::FileFinished(QNetworkReply* reply)
//{
//    qDebug() << "Downloader::FileFinished";

//    disconnect(m_reply, &QNetworkReply::readyRead, this, &HTTP::FilePart);
//    disconnect(m_reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &HTTP::FileError);
//    reply->deleteLater();
//    m_lastDownloadedSize = 0;
//    m_downloadedSize = 0;

//    if (m_bDownloading)
//    {
//        m_bDownloading = false;
//        m_timeoutTimer->stop();
//        m_currentFile->close();
//        delete m_currentFile;

//        emit FileDownloaded(m_currentFtpFile);
//    }
//}
