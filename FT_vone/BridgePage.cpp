#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>

void MainWindow::on_HomeXButton_clicked()
{

    serial.write("G28 X\n");
    serial.write("G01 X5 F1000\n");
    serial.write("M18\n");
}
void MainWindow::on_SpeedXButton_clicked()
{
    serial.write("G28 X\n");
    serial.write("G01 X128 F12000\n");
    serial.write("G01 X0 F12000\n");
}
void MainWindow::on_SpinEButton_clicked()
{

    sendcommand("G01 E0 F180\n");
    sendcommand("G04 P1\n");
    for (int e=0; e<10;e++){
        sendcommand("G01 E4.5 F180\n");
        sendcommand("G01 E5.5 F180\n");

    }
    delay(1);
    sendcommand("G04 P1\n");
    sendcommand("G01 E0 F180\n");
    sendcommand("M18\n");

}
void MainWindow::on_HomeZDButton_clicked()
{
    serial.write("G28 Z\n");
    serial.write("G01 Z0 F200\n");
    serial.write("M18\n");
}

void MainWindow::on_HomeZUButton_clicked()
{
    serial.write("G28 Z\n");
    serial.write("M18\n");
}
void MainWindow::on_FullBridgeTestButton_clicked()
{
    for (int x=0;x<3;x++){
        on_SpeedXButton_clicked();
    }
    for (int x=0;x<3;x++){
        on_SpinEButton_clicked();
    }
    for (int x=0;x<3;x++){
        on_HomeZDButton_clicked();
    }
}

void MainWindow::on_ProbePinsButton_clicked()
{
    sendcommand("M125\n");
    qDebug("Mount Probe");
    probepinsButton_clicked = true;
    probemounted = false;
    probetriggered =false;
    probedisconnected = false;
}
void MainWindow:: probestatus(QString stat)
{
   int countdown = 20;
    ui->progressBar->setMaximum(countdown*10);
    ui->progressBar->setMinimum(0);

   qDebug()<<stat;
  if(stat == "Start"){
   while(true)
   {
       if(countdown==0){
           probepinsButton_clicked = false;
           qDebug("error: Probe Not Detected.");
           break;
       }
       else{
           ui->progressBar->setValue(countdown*10);
           qDebug()<<countdown;
           countdown--;
                   delay(1);
       }
   }
   }
  else{
      qDebug("Disconnect Probe and Try again!");
  }
}


