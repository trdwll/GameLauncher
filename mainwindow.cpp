#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <user.h>

#include <QStringList>
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
}

void MainWindow::on_btnPlay_clicked()
{
    User* const user = new User(this, "trdwll", "temp12134");
    if (user->Login())
    {
        qDebug() << "User has been authorized";
        DownloadFile("https://trdwll.com/f/lol.patch", "Cool.exe", "tmpDir");
        ui->label->setText(user->GetUsername());
    }
    else
    {
        ui->label->setText("Unable to login");
        qDebug() << "User hasn't been authenticated";
    }

    // delete user;
}

bool MainWindow::DownloadFile(const QString &URL, const QString &FileName, const QString &Downloadlocation)
{
    //if (!HasUpdate())
    //{
    //    return;
    //}

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

void MainWindow::InitDownload()
{

}

