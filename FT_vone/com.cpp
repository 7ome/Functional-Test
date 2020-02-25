#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

void MainWindow::initialize_com()
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
}
    }
}
