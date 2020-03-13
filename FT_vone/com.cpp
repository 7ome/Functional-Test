#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

void MainWindow::initialize_serialcom()
{

    //Scans all available ports but filters and set only the FTDI(V-one)com
    //Will change to v1 serial number later
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        //Filter FTDI
        if(info.manufacturer()=="FTDI"){        
            //Set and open coms
            serial.close();
            serial.setPortName(info.portName());
            serial.setBaudRate(250000);
            serial.setDataBits(QSerialPort::Data8);
            serial.setParity(QSerialPort::NoParity);
            serial.setStopBits(QSerialPort::OneStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);
           if(serial.open(QIODevice::ReadWrite)){
                serialcom=true;
                qDebug("Initializing Connection.....");
                delay(2);
                qDebug("Connection to serial succesfull");
           }
           else{
           }
}
    }
      update_comstatus();
}
//Writes to the serial
void MainWindow::sendcommand(const char * gCode)
{
    serial.write(gCode);
    serial.flush();
}
