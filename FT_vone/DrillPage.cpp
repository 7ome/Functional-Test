#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>


void MainWindow::on_SetDrillButton_clicked()
{
   sendcommand("G28\n");
   sendcommand("G1 X120 Y120 F12000\n");
   sendcommand("G4 S25\n");
    sendcommand("G1 X20 Y40\n");
    sendcommand("M18\n");
}

void MainWindow::on_runoutButton_clicked()
{
  sendcommand("G1 X120 Y115\n");
       sendcommand("D110 R100\n");
      sendcommand("D110 R75\n");
              sendcommand("D110 R50\n");
              sendcommand("D110 R25\n");
              sendcommand("D110 R8\n");
              sendcommand("G1 Y120 F300\n");
              sendcommand("G4 S3\n");
              sendcommand("G1 Y110 F1000\n");
              sendcommand("D110 R0\n");
              sendcommand("G1 X20 Y40 F12000\n");
//     sendcommand("M18\n");
}

void MainWindow::on_SpinMotorButton_clicked()
{

}

void MainWindow::on_MotorSpeedSlider_actionTriggered(int action)
{

}
