#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>

class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readData(void);

private:
    void showStatusMessage(const QString &message);

    Ui::MainWindow *ui;
    QLabel *status;
    QSerialPort *serial;
    QString *data;
};

#endif // MAINWINDOW_H
