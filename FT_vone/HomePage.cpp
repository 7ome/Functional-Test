#include <mainwindow.h>
#include <ui_mainwindow.h>


void MainWindow::on_MenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_BridgeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_DrillButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_ProbeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_DatabaseButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(4);
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
void MainWindow::update_comstatus(){

    if(serialcom && dbcom){
        ui->textBrowser->setText("Serial Connection: \t Connected\nDatabase Connection:\t Connected");
    }
    if(!serialcom && dbcom){
        ui->textBrowser->setText("Serial Connection: \t Disconnected\nDatabase Connection: \t Connected");
    }
    if(serialcom && !dbcom){
        ui->textBrowser->setText("Serial Connection: \t Connected\nDatabase Connection: \t Disconnected");
    }
    if(!serialcom && !dbcom){
        ui->textBrowser->setText("Serial Connection: \tDisconnected\nDatabase Connection: \tDisconnected");
    }
    else{}
}
