#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ulong  g_data;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int hex_len;
    void formatHex(QString &string);


public slots:
    void turnCode();
    void turnBIN();
};

#endif // MAINWINDOW_H
