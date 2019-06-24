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
    QString GetPatchToolPath();

    QString m_CurrentDirectory;

    QString m_ToolsBasePath;
    QString m_PatchToolPath;

    // TODO: Add option for only selecting a binary instead of directory
    QString m_SelectedInputDirectory;
    QString m_SelectedOutputDirectory;

    void Patch();

    void ToggleStatus(bool bEnabled);

private slots:
    void on_btnPatch_clicked();

    void on_btnBrowseInputDirectory_clicked();
    void on_btnBrowseOutputDirectory_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
