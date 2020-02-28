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
    initialize_com();
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
            if(str[strlength].contains("error:")){
                msgbox.critical(nullptr,"ERROR!",str[strlength].remove("error: "));
            }
            else
            {
            }
        }
        //Read Vone Values when Extract Button is clicked (in Database Page)
        if (extractButton_clicked)
        {
            //Search for Serial Number, Skew and Backlash
            //Remove unecessary tags (eg. logs)
            str.filter(datas);
            for (int i=0; i<str.length();i++){
                str[i].remove("log:  ");

                //m504 is serial tag
                if(str[i].contains("M504")){
                    SerialNum =str[i].remove("M504 S:");
                    qDebug()<<SerialNum;
                }
                //m506 is skew tag
                if(str[i].contains("M506")){
                    Skew = str[i].remove("M506 ");
                    qDebug()<<Skew;
                }
                //m507 is backlash tag
                if(str[i].contains("M507")){
                    Backlash = str[i].remove("M507 ");
                    qDebug()<<Backlash;
                    //after extracting backlash, skew and serial, print them in msgbox and ask user to save it
                    QMessageBox::StandardButton reply;
                    reply=msgbox.information(nullptr,"Unit Info", "Serial No:\t"+SerialNum+"\n Skew:\t"+Skew+"\n Backlash:\t"+Backlash,QMessageBox::Cancel | QMessageBox::Save);
                    if(reply==QMessageBox::Save){
                        on_SaveButton_clicked();
                    }
                    else
                        break;
                }
                else{
                    extractButton_clicked = false;
                }
            }
        }
        if(probepinsButton_clicked)
        {
            str.filter(datas);
            for (int i=0; i<str.length();i++)
            {
                if(str[i].contains("Probe: Not Mounted")&& firstrun){
                    ui->probeBrowser->setText("Mount Probe");
                    firstrun = false;
                    probedisconnected = true;
                    countdown = 10;
                    probestatus();
                }
                if(str[i].contains("Probe: Probe Mounted")&& probedisconnected){
                    ui->probeBrowser->setText("Trigger Probe");
                    probemounted = true;
                    probedisconnected = false;
                    countdown = 10;
                    probestatus();
                }
                if(str[i].contains("Probe: Triggered")&& probemounted){
                   ui->probeBrowser->setText("Release Trigger");
                    probemounted=false;
                    probetriggered=true;
                    countdown = 10;
                    probestatus();
                }
                if(str[i].contains("Probe: Probe Mounted")&& probetriggered && probetriggered){
                   ui->probeBrowser->setText("Disconnect Probe");
                    probemounted=true;
                    probetriggered=false;
                    countdown = 10;
                    probestatus();

                }
                if(str[i].contains("Probe: Not Mounted")&& probemounted){
                    probedisconnected=true;
                    probetriggered=true;
                    probestatus();
                }
                if(str[i].contains("Probe: Probe Mounted") && !probemounted){
                    qDebug("Disconnect Probe to begin");
                }
                else{
                }
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

