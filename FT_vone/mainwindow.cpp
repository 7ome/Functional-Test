#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    serial.close();
}

void MainWindow::on_pushButton_clicked()
{
    //Scans all available ports but filters and set only the FTDI(V-one)com
    //Will change to v1 serial number later
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

      //Filter FTDI
        if(info.manufacturer()=="FTDI"){
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
           qDebug() << "Manufacturer: " << info.manufacturer();
           ui->textBrowser->setText("Connected to "+info.portName());
    //Set and open coms
    serial.setPortName(info.portName());
    serial.setBaudRate(250000);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);


    //this is called when datas are received
 QObject::connect(&serial, &QSerialPort::readyRead, [&]
    {
     QStringList str;
     QString sNumber;
     datas = serial.readAll();
                     //Split parts with "\n" and ignore empty strings
                     str = datas.split(("\n"), QString::SkipEmptyParts);

                     //Print strings per line in console
                     for (int strlength = 0; strlength < str.length(); strlength++) {
                         std::cout << str.at(strlength).toStdString() << std::endl;
                     }

                     if (extractButton_clicked) {
                       //sNumber = str.startsWith("M504");

                         ui->readtextbox->setText("" + datas);
                         extractButton_clicked = false;
                     }
                     return true;
         }
    );
datas.clear();
    //this is called when serial com error occurs
 QObject::connect(&serial,static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                         (&QSerialPort::error),
                         [&](QSerialPort::SerialPortError error)
    {
        qDebug() << "An error occured: " << error;
        //return qApp->quit();
    });
}

    }
}
void MainWindow::on_ExtractButton_clicked()
{ 
    sendcommand("M520\n");

    extractButton_clicked = true;
    delay();
}
void MainWindow:: delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::sendcommand(const char * gCode){

serial.write(gCode);

}




