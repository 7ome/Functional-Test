#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSerialPort serial;
    QString datas;
    QStringList list;
    const char *gline[30];
    bool check;
    bool extractButton_clicked;
    int motorspeed;
    QString SerialNum = "V1-05-000-002";
    QString SkewX       ="0.0123";
    QString SkewY       ="0.0234";
    QString BackslashX  ="0.0456";
    QString BackslashY  ="0.0789";

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void delay(int sec);
    void sendcommand(const char *gCode);
    void on_pushButton_clicked();
    void on_MenuButton_clicked();
    void on_BridgeButton_clicked();
    void on_DrillButton_clicked();
    void on_ProbeButton_clicked();
    void on_DatabaseButton_clicked();
    void on_HomeButton_clicked();
 //Bridge
    void on_HomeXButton_clicked();
    void on_ExtractButton_clicked();
    void on_SpeedXButton_clicked();
    void on_SpinEButton_clicked();
    void on_HomeZDButton_clicked();
    void on_HomeZUButton_clicked();
    void on_SetDrillButton_clicked();
    void on_runoutButton_clicked();
    void on_SpinMotorButton_clicked();
    void on_LineEdit_returnPressed();

    void on_MotorSpeedSlider_valueChanged(int value);

    void on_MotorSpeedSlider_sliderReleased();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
