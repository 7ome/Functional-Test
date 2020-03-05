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
    on_SpinEButton_clicked();
    for (int x=0;x<3;x++){
        on_HomeZDButton_clicked();
    }
}

void MainWindow::on_ProbePinsButton_clicked()
{
    sendcommand("M125\n");
    probepinsButton_clicked = true;
    firstrun=true;
    probemounted = false;
    probetriggered =false;
    probedisconnected = false;
}

void MainWindow:: probestatus()
{
    ui->progressBar->setMaximum(countdown*10);
    ui->progressBar->setMinimum(0);

  if(probemounted && probetriggered && probedisconnected){
       ui->probeBrowser->setText("Probe Pogo Pin Passed!");
       probepinsButton_clicked = false;
    }
    else{
        while(!probemounted || !probetriggered || !probedisconnected)
        {
            if(countdown<0){
                ui->probeBrowser->setText("Probe Pogo Pin Failed!");
                qDebug("error: Probe Not Detected.");
                probepinsButton_clicked = false;
                break;
            }
            else{
                ui->progressBar->setValue(countdown*10);
                qDebug()<<countdown;
                countdown--;
                sendcommand("M125\n");
                delay(1);
            }
        }
    }
}
void MainWindow::check_probepins(int i)
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
