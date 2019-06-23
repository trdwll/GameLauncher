#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <user.h>

#include <QMessageBox>
#include <QDir>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_User;
}

void MainWindow::on_btnPlay_clicked()
{
    //if (HasUpdate())
    //{
    //    DownloadFile("https://trdwll.com/f/lol.patch", "Cool.exe", "tmpDir");
    //}
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

bool MainWindow::HasUpdate()
{
    return false;
}

void MainWindow::on_btnLogin_clicked()
{
    QString Username = ui->txtUsername->toPlainText();
    QString Password = ui->txtPassword->toPlainText();

    // TODO: Check if Username or Password are empty

    qDebug() << "Username: " << Username << " Password: " << Password;

    m_User = new User(this);
    SUserData userdata;
    userdata.Username = Username;
    userdata.Password = Password;
    if (m_User->Login(userdata))
    {
        qDebug() << "User has been authorized";
        ui->label->setText(m_User->GetUsername());

        // This isn't ideal, and logging in should be done via another form rather than MainWindow
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
