#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    bool HasUpdate();

    void DownloadFile(const QString& URL, const QString& FileName, const QString& DownloadLocation);

    // Store a reference for a temporary directory so we can delete it on cleanup
    QString m_tmpDir;

    /**
     * @brief Patch old content with new content
     * @param OldDir        If the directory doesn't exist then the call gets aborted
     * @param NewDir        If the directoy doesn't exist then it'll be created
     * @param PatchFileName
     */
    void Patch(const QString& OldDir, const QString& NewDir, const QString& PatchFileName);


private slots:
    void on_btnPlay_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
