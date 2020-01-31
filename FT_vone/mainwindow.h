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

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void delay();
    void sendcommand(const char *gCode);
    void on_pushButton_clicked();
    void on_MenuButton_clicked();
    void on_BridgeButton_clicked();
    void on_DrillButton_clicked();
    void on_ProbeButton_clicked();
    void on_DatabaseButton_clicked();
    void on_HomeButton_clicked();
    void on_gCodeButton_clicked();
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
    void on_MotorSpeedSlider_actionTriggered(int action);
    void on_gCodeLine_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
