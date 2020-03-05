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
   initialize_db();
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
