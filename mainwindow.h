#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void openNewWindows();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setCurrentIndex(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
