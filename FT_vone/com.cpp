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
void MainWindow::on_dbButton_clicked()
{
    //Initialize database connection to local server
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("batch7");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    if(db.open()){
        qDebug()<<"Connection to Database("<<db.databaseName()<<") Succesfull";
        dbcom=true;
        update_comstatus();
    }
    else{
        qDebug()<<"error"<<db.lastError();
        dbcom=false;
    }
}
//Writes to the serial
void MainWindow::sendcommand(const char * gCode)
{
    serial.write(gCode);
    serial.flush();
}
