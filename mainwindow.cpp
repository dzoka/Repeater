#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    status = new QLabel;
    ui->statusBar->addWidget(status);

    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyUSB0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if(serial->open(QIODevice::ReadOnly))
    {
        data = new QString();
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
        showStatusMessage(tr("Connected"));
    }
    else
    {
        showStatusMessage(tr("Port open error"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}

void MainWindow::readData()
{
    QByteArray buf = serial->readAll();
    data->append(buf);
    if(data->contains(QRegExp("[\\n]")))
    {
        ui->lineEdit->setText(data->simplified());
        data->clear();
        if(ui->lineEdit->styleSheet().contains("rgb(255, 255, 255)"))
        {
            ui->lineEdit->setStyleSheet("background-color: rgb(255, 250, 210);");
        }
        else
        {
            ui->lineEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
        }
    }
}
