#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>


void MainWindow::on_SetDrillButton_clicked()
{
   sendcommand("G28;G1 X120 Y120 F12000;G4 S25;G1 X20 Y40\n");
    sendcommand("M18\n");
}

void MainWindow::on_runoutButton_clicked()
{
  sendcommand("G1 X120 Y115;D110 R100;D110 R75;D110 R50;D110 R25;D110 R8;G1 Y120 F300;G4 S3;G1 Y110 F1000;D110 R0;G1 X20 Y40 F12000");
     sendcommand("M18\n");
}

void MainWindow::on_SpinMotorButton_clicked()
{

}

void MainWindow::on_MotorSpeedSlider_actionTriggered(int action)
{

}
