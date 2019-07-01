#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameLauncher/downloadmanager.h"


class QStringList;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const QString m_DownloadBaseURL = "https://trdwll.com/f/Game/bin/";
    const QString m_UpdateCheckURL = "https://trdwll.com/f/Game/version.json";

    bool DownloadFile(const QString& URL, const QString& FileName, const QString& DownloadLocation);

    // Store a reference for a temporary directory so we can delete it on cleanup
    QString m_tmpDir;

    /**
     * @brief Patch old content with new content
     * @param OldDir        If the directory doesn't exist then the call gets aborted
     * @param NewDir        If the directory doesn't exist then it'll be created
     * @param PatchFileName
     */
    void Patch(const QString& OldDir, const QString& NewDir, const QString& PatchFileName);

    class User* m_User;

	/** Update code */
	QNetworkAccessManager* m_NetworkManager;
	QNetworkRequest m_Request;
	bool CheckForUpdates();
	bool m_bHasUpdate;

	QString m_RemoteVersion;
	QString m_LocalVersion;

private:
    DownloadManager m_DownloadManager;

	qint64 m_StartTime;

private slots:
    void on_btnPlay_clicked();

    void on_btnLogin_clicked();

    void onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
