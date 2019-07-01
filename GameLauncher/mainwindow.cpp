#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GameLauncher/user.h"
#include "GameLauncher/utils.h"

#include <QNetworkReply>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVersionNumber>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_DownloadManager, &DownloadManager::UpdateDownloadProgress, this, &MainWindow::onUpdateProgress);

	m_bHasUpdate = CheckForUpdates();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_User;
	delete m_NetworkManager;
}

void MainWindow::on_btnPlay_clicked()
{
	if (m_bHasUpdate)
	{
		qDebug() << "update available";
		m_DownloadManager.DownloadFile(m_DownloadManager.m_DownloadURL);

		return;
	}

	qDebug() << "Play the game boi";
}

bool MainWindow::CheckForUpdates()
{
	m_NetworkManager = new QNetworkAccessManager();
	QObject::connect(m_NetworkManager, &QNetworkAccessManager::finished, this,
		[=](QNetworkReply* reply) 
		{
			if (reply->error()) 
			{
				qDebug() << "ERROR (CheckForUpdates):" << reply->errorString();
				return;
			}

			QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
			m_RemoteVersion = jsonObject["CurrentVersion"].toString();

			QFile file(qApp->applicationDirPath() + QDir::separator() + "version.txt");
			file.open(QIODevice::ReadOnly);
			m_LocalVersion = file.readAll();

			qDebug() << "jsonObject: " << jsonObject;
			qDebug() << "Local Version: " << m_LocalVersion;
			qDebug() << "Remote Version: " << m_RemoteVersion;
			bool res = QVersionNumber::compare(QVersionNumber::fromString(m_LocalVersion), QVersionNumber::fromString(m_RemoteVersion)) == -1;
			qDebug() << res;

			ui->lbDownloadInfo->setText(res ? "Update " + m_RemoteVersion + " available! You're on " + m_LocalVersion + "." : "You're on the current version!");
		}
	);

	// We could also check the checksums (we would have to store checksums of all files on the client and server then compare - then we only download the specific files and patch them), but that could be a performance issue down the line

	m_Request.setUrl(QUrl(m_UpdateCheckURL));
	m_NetworkManager->get(m_Request);

	return QVersionNumber::compare(QVersionNumber::fromString(m_LocalVersion), QVersionNumber::fromString(m_RemoteVersion)) == -1;
}

bool MainWindow::DownloadFile(const QString &URL, const QString &FileName, const QString &Downloadlocation)
{
    m_tmpDir = Downloadlocation;

    if (!QDir(Downloadlocation).exists())
    {
        QDir().mkdir(Downloadlocation);
    }

    return false;
}

void MainWindow::Patch(const QString &OldDir, const QString &NewDir, const QString &PatchFileName)
{
    // TODO: Check the HTTP server and see if all files have been downloaded, ie check the checksums of all files in the m_tmpDir

    if (!QDir(OldDir).exists())
    {
        return;
    }

    if (!QDir(NewDir).exists())
    {
        QDir().mkdir(NewDir);
    }
}

void MainWindow::on_btnLogin_clicked()
{
    QString Username = ui->txtUsername->toPlainText();
    QString Password = ui->txtPassword->toPlainText();

    // TODO: Check if Username or Password are empty

    qDebug() << "Username: " << Username << " Password: " << Password;

	/**
	 * qDebug() << "User has been authorized";
//        ui->label->setText(m_User->GetUsername());

		// This isn't ideal, and logging in should be done via another form rather than MainWindow
		ui->tabWidget->removeTab(0);

		ui->btnPlay->setEnabled(true);
		ui->pbDownload->setEnabled(true);
	 */

    m_User = new User(this);
    SUserData userdata;
    userdata.Username = Username;
    userdata.Password = Password;
	m_User->Login(userdata);
    if (m_User->IsLoggedin())
    {
        qDebug() << "User has been authorized";
        ui->label->setText(m_User->GetUsername());

        ui->tabWidget->removeTab(0);

        ui->btnPlay->setEnabled(true);
        ui->pbDownload->setEnabled(true);
    }
    else
    {
        ui->label->setText("Unable to login");
        qDebug() << "User hasn't been authenticated";
    }
}

void MainWindow::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->pbDownload->setMaximum(bytesTotal);
    ui->pbDownload->setValue(bytesReceived);

	QString str = "Downloading " + Utils::ConvertToHuman(bytesReceived) + " / " + Utils::ConvertToHuman(bytesTotal) + " Estimated Remaining Time: " + m_DownloadManager.GetTimeRemaining(bytesReceived, bytesTotal);
	ui->lbDownloadInfo->setText(str);

	if (bytesReceived == bytesTotal)
	{
		ui->lbDownloadInfo->setText("Download Complete");
		ui->pbDownload->setVisible(false);
		ui->lbDownloadInfo->setVisible(false);

		m_DownloadManager.InitInstall();
	}
}
