#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onRenderButtonClicked();
    void onColorChange(double c);
    void onGenerateButtonClicked();

signals:
    void fileSelected(const QString &filePath); // Custom signal

private slots:
    void onImportButtonClicked(); // Slot to handle button click

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
