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

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE


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

 //MYSQL

    QSqlDatabase db;
    QString SerialNum ;
    QString Skew;
    QString Backlash;


//Serial Communication
    QStringList str;
    QSerialPort serial;
    QString datas;
    QStringList list;
    const char *gline[30];
    bool extractButton_clicked;
    bool probepinsButton_clicked=false;
    bool serialcom = false;
    bool dbcom;
    int motorspeed;
//Probe testing
    bool probemounted=false;
    bool probetriggered=false;
    bool probedisconnected=false;
    bool firstrun=false;
    int countdown = 10;

QMessageBox msgbox;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void delay(int sec);
    void sendcommand(const char *gCode);

  //Serial Com
    void initialize_serialcom();

 //Main Menu
    void on_pushButton_clicked();
    void on_MenuButton_clicked();
    void on_BridgeButton_clicked();
    void on_DrillButton_clicked();
    void on_ProbeButton_clicked();
    void on_DatabaseButton_clicked();
    void on_HomeButton_clicked();
    void update_comstatus();

 //Bridge
    void on_HomeXButton_clicked();
    void on_ExtractButton_clicked();
    void on_SpeedXButton_clicked();
    void on_SpinEButton_clicked();
    void on_HomeZDButton_clicked();
    void on_HomeZUButton_clicked();
//    void on_FullBridgeTestButton_clicked();
    void on_ProbePinsButton_clicked();
    void probestatus();
    void check_probepins(int i);

 //Drill
    void on_SetDrillButton_clicked();
    void on_FullRunOutButton_clicked();
    void on_SpinMotorButton_clicked();
    void on_LineEdit_returnPressed();
    void on_MotorSpeedSlider_valueChanged(int value);
    void on_MotorSpeedSlider_sliderReleased();
    void on_RunOutButton_clicked();
    void on_NoiseButton_clicked();

 //Database
    void on_SearchButton_clicked();
    void on_SaveButton_clicked();
    void get_calibration(int i);
    void on_dbButton_clicked();


    void on_BSaveButton_clicked();

    void on_BPassButton_clicked();

    void on_clearB_Button_clicked();

    void on_DSaveButton_clicked();

    void on_DPassButton_clicked();

    void on_ViewGraphButton_clicked();

    void on_clearD_Button_clicked();

    void on_sqlline_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
