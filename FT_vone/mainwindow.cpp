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

     //check printer error
      datas = serial.readLine();
     if(datas.contains("ok", Qt::CaseInsensitive)){
         qDebug("si si si si");
         check = true;
     }
     else{
         qDebug("no bueno");

     }
     qDebug()<<datas<<endl;
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
//  sendcommand("G28X\n");
}

void MainWindow::sendcommand(const char * gCode){
serial.write(gCode);
int n = 0;
while(n < 100){
    n++;
}
}




