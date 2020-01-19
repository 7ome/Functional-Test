#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>

void MainWindow::on_HomeXButton_clicked()
{

sendcommand("G28 X\n");
sendcommand("G01 X5 F1000\n");
sendcommand("M18\n");
}
void MainWindow::on_SpeedXButton_clicked()
{
    sendcommand("G28 X\n");
    sendcommand("G01 X128 F12000\n");
    sendcommand("G01 X0 F12000\n");
}
void MainWindow::on_SpinEButton_clicked()
{
   serial.write("G01 E5 F180\n");

<<<<<<< Updated upstream
    sendcommand("G04 P1\n");

    for (int e=0; e<10;e++){
        sendcommand("G01 E4.5 F180\n");
        sendcommand("G01 E5.5 F180\n");
    }
    sendcommand("G04 P1\n");
    sendcommand("G01 E0 F180\n");
    sendcommand("M18\n");
=======
    sendcommand("G01 E0 F180\n");
    sendcommand("G04 P1\n");
    for (int e=0; e<10;e++){
        sendcommand("G01 E4.5 F180\n");
        sendcommand("G01 E5.5 F180\n");
    }
    delay(3);
    sendcommand("G01 E0 F180\n");
    sendcommand("M18\n");

>>>>>>> Stashed changes

}
void MainWindow::on_HomeZDButton_clicked()
{
   sendcommand("G28 Z\n");
      sendcommand("G01 Z0 F200\n");
    sendcommand("M18\n");
}

void MainWindow::on_HomeZUButton_clicked()
{
    sendcommand("G28 Z\n");
   sendcommand("M18\n");
}
