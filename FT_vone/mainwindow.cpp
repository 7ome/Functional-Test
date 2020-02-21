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
ui->textBrowser->setText("Status: Disconnected");
}

MainWindow::~MainWindow()
{
    delete ui;
    serial.close();
}
void MainWindow:: delay(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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
            ui->textBrowser->setText("Status: Connecting...");



    //Set and open coms
    serial.setPortName(info.portName());
    serial.setBaudRate(250000);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);
    delay(2);
    ui->textBrowser->setText("Status: Connected");

    //this is called when datas are received
 QObject::connect(&serial, &QSerialPort::readyRead, [&]
    {

     QStringList str;
     QString sNumber;
     datas = serial.readAll();
                     //Split parts with "\n" and ignore empty strings
                     str = datas.split(("\n"), QString::SkipEmptyParts);
                     delay(1);
                     //Print strings per line in console
                     for (int strlength = 0; strlength < str.length(); strlength++) {
                         std::cout << str.at(strlength).toStdString() << std::endl;
                     }
                     if (extractButton_clicked) {
                       //sNumber = str.startsWith("M504");
                            delay(1);
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
        delay(2);
        ui->textBrowser->setText("Status: Disconnected\n");
    });
}

    }
}
void MainWindow::sendcommand(const char * gCode){

serial.write(gCode);
    //qDebug()<<gCode;
}
void MainWindow::on_HomeButton_clicked()
{
    sendcommand("G28\n");
}
void MainWindow::on_LineEdit_returnPressed()
{
   QString cmdline =ui->LineEdit->text();

   const char *ready = cmdline.toLatin1().toUpper().data();
   sendcommand(ready);
   sendcommand("\n");
   ui->LineEdit->clear();
}


void MainWindow::on_MotorSpeedSlider_sliderReleased()
{
    on_SpinMotorButton_clicked();
}
