#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
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

 //SQLITE functions
    //QString dbpath = "C:\\Users\\Tome\\Documents\\Funtional-Test\\Database\\Batch7.db";
   QString dbpath = "C:\\Users\\WORKSTATION-1\\Documents\\GitHub\\Funtional-Test\\Database\\Batch7.db";
    QSqlDatabase db;
    QString SerialNum ;
    QString Skew;
    QString Backlash;

//Serial functions
    QSerialPort serial;
    QString datas;
    QStringList list;
    const char *gline[30];
    bool status;
    bool extractButton_clicked;
    bool probepinsButton_clicked;
    int motorspeed;

QMessageBox msgbox;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void delay(int sec);
    void sendcommand(const char *gCode);

 //Main Menu
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
 //Drill
    void on_SetDrillButton_clicked();
    void on_FullRunOutButton_clicked();
    void on_SpinMotorButton_clicked();
    void on_LineEdit_returnPressed();
    void on_MotorSpeedSlider_valueChanged(int value);
    void on_MotorSpeedSlider_sliderReleased();
 //Database
    void on_SearchButton_clicked();
    void on_SaveButton_clicked();
    void on_RunOutButton_clicked();
    void on_NoiseButton_clicked();

    void initialize_com();

    void on_FullBridgeTestButton_clicked();

    void on_ProbePinsButton_clicked();
    void probestatus(const char *stat);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
