//#ifndef HTTP_H
//#define HTTP_H

//#include <QObject>

//class HTTP : public QObject
//{
//    Q_OBJECT
//public:
//    explicit HTTP(QObject *parent = nullptr);
//    ~HTTP();

//    void Init();


//private:

//    class QNetworkAccessManager* m_Manager;

//    float   m_currentSpeed;
//    bool    m_bDownloading;
//    int     m_downloadedSize;
//    int     m_lastDownloadedSize;
//    int     m_chronoSize;
//    QString m_password;
//    QUrl*   m_ftpClient;
//    class QFile*  m_currentFile;
//    QTime*  m_chrono;
//    class QTimer* m_timeoutTimer;
//    class QTimer* m_speedUpdateTimer;
//    class QTimer* m_downloadUpdateTimer;
//    QString m_currentFtpDir;
//    QString m_currentFtpFile;
//    class QNetworkReply* m_reply;

//signals:
//    void FileDownloaded(QString downloadedFile);

//public slots:
//    void DownloadFile(const QString& Directory, const QString& File);

//    void FilePart();
//    void FileError(class QNetworkReply::NetworkError code);
//    void FileFinished(class QNetworkReply* reply);
//};

//#endif // HTTP_H
