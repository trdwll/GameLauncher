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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_User;
}

bool MainWindow::HasUpdate()
{
	QNetworkAccessManager manager;
	QNetworkRequest request(m_UpdateCheckURL);

	m_CurrentUpdateReply = manager.get(request);

	QJsonObject jsonObject = QJsonDocument::fromJson(m_CurrentUpdateReply->readAll()).object();

	// We could also check the checksums (we would have to store checksums of all files on the client and server then compare - then we only download the specific files and patch them), but that could be a performance issue down the line

	QFile file(qApp->applicationDirPath() + QDir::separator() + "version.txt");
	file.open(QIODevice::ReadOnly);
	QString localVersionFileContent = file.readAll();

	QVersionNumber localVersion(QVersionNumber::fromString(localVersionFileContent));
	QVersionNumber remoteVersion(QVersionNumber::fromString(jsonObject["CurrentVersion"].toString()));
	
	// -1 == local < remote, 0 == local == remote, 1 == local > remote
	if (QVersionNumber::compare(localVersion, remoteVersion) == -1)
	{
		return true;
	}
	/**
	{
		"CurrentVersion": "1.0.0.0",
		"ReleaseDate": "June 30, 2019"
	}
	*/

	return false;
}


void MainWindow::on_btnPlay_clicked()
{
	// if (Utils::HasUpdate())
	{
		qDebug() << QDir::currentPath();
		QString url = "http://www.ovh.net/files/10Mio.dat";
		// QString url = "http://www.ovh.net/files/10Gio.dat";
		m_DownloadManager.DownloadFile(url);

		return;
	}
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

//    m_User = new User(this);
//    SUserData userdata;
//    userdata.Username = Username;
//    userdata.Password = Password;
//    if (m_User->Login(userdata))
//    {
        qDebug() << "User has been authorized";
//        ui->label->setText(m_User->GetUsername());

        // This isn't ideal, and logging in should be done via another form rather than MainWindow
        ui->tabWidget->removeTab(0);

        ui->btnPlay->setEnabled(true);
        ui->pbDownload->setEnabled(true);
//    }
//    else
//    {
//        ui->label->setText("Unable to login");
//        qDebug() << "User hasn't been authenticated";
        //    }
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
	}
}
