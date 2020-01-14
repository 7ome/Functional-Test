#include <mainwindow.h>
#include <ui_mainwindow.h>



void MainWindow::on_HomeButton_clicked()
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
