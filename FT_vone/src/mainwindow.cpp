#include <.\headers\mainwindow.h>
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <sstream>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setText("Serial Connection: \tDisconnected\nDatabase Connection: \tDisconnected");
}
MainWindow::~MainWindow()
{
    delete ui;
    serial.close();
    db.close();
}
void MainWindow:: delay(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::on_pushButton_clicked()
{
    initialize_serialcom();
    //this is called when datas are received
    QObject::connect(&serial, &QSerialPort::readyRead, [&]
    {
        update_comstatus();
        datas = serial.readAll();
        //Split parts with "\n" and ignore empty strings
        str = datas.split(("\n"), QString::SkipEmptyParts);
        delay(1);
        //Print strings per line in console
        for (int strlength = 0; strlength < str.length(); strlength++) {
            std::cout << str.at(strlength).toStdString() << std::endl;
            if(str[strlength].contains("error:")){
                msgbox.critical(nullptr,"Stop!",str[strlength].remove("error: "));
            }
            else{}
        }
        //Read Vone Values when Extract Button is clicked (in Database Page)
        if (extractButton_clicked){

            str.filter(datas);
            for (int i=0; i<str.length();i++){
                get_calibration(i);
            }
        }
        if(probepinsButton_clicked)
        {
            str.filter(datas);
            for (int i=0; i<str.length();i++){
                if(probemounted && probetriggered && probedisconnected){
                    ui->probeBrowser->setText("Probe Pogo Pin Passed!");
                    probepinsButton_clicked = false;
                    break;
                }
                else{
                    check_probepins(i);
                }
            }
        }
        if(probetest_clicked){
            str.filter(datas);
            for (int i=0; i<str.length();i++){
                probe_measurements(i);
            }
        }
        else{
        }
        datas.clear();
    });
    //this is called when serial com error occurs
    QObject::connect(&serial,static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                     (&QSerialPort::error),
                     [&](QSerialPort::SerialPortError error)
    {
        qDebug() << "An error occured: " << error;
        serialcom=false;
        update_comstatus();
    });
}

