#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileDialog>
#include <QStandardPaths>
#include <QProcess>
#include <QDir>
#include <QSysInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Application starting", 2000);
    m_CurrentDirectory = QDir::currentPath();
    m_ToolsBasePath = m_CurrentDirectory+"/tools/";
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::GetPatchToolPath()
{
    // TODO: add architecture
    QString os, arch, file;
    QString kernel = QSysInfo::kernelType();
    file = "hdiffz";
    if (kernel == "winnt")
    {
        os = "win";
        file = "hdiffz.exe";
    }
    else if (kernel == "linux" || kernel == "freebsd")
    {
        os = "lin";
    }
    else if (kernel == "darwin")
    {
        os = "mac";
    }

    m_PatchToolPath = m_ToolsBasePath+os+"/"+file;

    return m_PatchToolPath;
}

void MainWindow::on_btnPatch_clicked()
{
    Patch();
    ToggleStatus(false);
}

void MainWindow::Patch()
{
    ui->statusBar->showMessage("Patching...");
    qDebug() << GetPatchToolPath();
    QProcess* proc = new QProcess(this);
    //proc->start(GetPatchToolPath());

    // ToggleStatus(true);
}

void MainWindow::ToggleStatus(bool bEnabled)
{
     ui->btnPatch->setEnabled(bEnabled);

     ui->btnBrowseInputDirectory->setEnabled(bEnabled);
     ui->txtInputDirectoryLocation->setEnabled(bEnabled);
     ui->btnBrowseOutputDirectory->setEnabled(bEnabled);
     ui->txtOutputDirectoryLocation->setEnabled(bEnabled);
     ui->txtPatchFileName->setEnabled(bEnabled);
}

void MainWindow::on_btnBrowseInputDirectory_clicked()
{
    m_SelectedInputDirectory = QFileDialog::getExistingDirectory(this, "Select Input Directory", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->txtInputDirectoryLocation->setText(m_SelectedInputDirectory);
}

void MainWindow::on_btnBrowseOutputDirectory_clicked()
{
    m_SelectedOutputDirectory = QFileDialog::getExistingDirectory(this, "Select Output Directory", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->txtOutputDirectoryLocation->setText(m_SelectedOutputDirectory);
}
