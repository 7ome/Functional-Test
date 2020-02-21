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
    serial.close();
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
     datas = serial.readAll();

   //Split parts with "\n" and ignore empty strings
                str = datas.split(("\n"), QString::SkipEmptyParts);
               delay(1);
               //Print strings per line in console
               for (int strlength = 0; strlength < str.length(); strlength++) {
              std::cout << str.at(strlength).toStdString() << std::endl;
          }
    //Read Vone Values when Extract Button is clicked (in Database Page)
              if (extractButton_clicked)
              {
    //Search for Serial Number, Skew and Backslash
    //Remove unecessary tags (eg. logs)
                str.filter(datas);
                for (int i=0; i<str.length();i++){
                       str[i].remove("log:  ");
                       if(str[i].contains("M504")){
                           SerialNum =str[i].remove("M504 S:");
                           qDebug()<<SerialNum;
                       }
                       if(str[i].contains("M506")){
                           Skew = str[i].remove("M506 ");
                           qDebug()<<Skew;
                       }
                       if(str[i].contains("M507")){
                           Backslash = str[i].remove("M507 ");
                           qDebug()<<Backslash;
                       }
                       else{
                       }
                         extractButton_clicked = false;
                       }
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
        delay(2);
        ui->textBrowser->setText("Status: Disconnected\n");
    });
        }
    }
}
//Writes to the serial
void MainWindow::sendcommand(const char * gCode)
{
    serial.write(gCode);
}
void MainWindow::on_HomeButton_clicked()
{
    sendcommand("G28\n");
}
//Write gCodes directly to the unit
void MainWindow::on_LineEdit_returnPressed()
{
   QString cmdline =ui->LineEdit->text();
   const char *ready = cmdline.toLatin1().toUpper().data();
   sendcommand(ready);
   sendcommand("\n");
   ui->LineEdit->clear();
}


