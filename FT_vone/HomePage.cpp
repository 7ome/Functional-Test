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
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("Batch7");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    if(db.open()){
        qDebug("Database is open");
        ui->stackedWidget->setCurrentIndex(4);
    }
    else
        qDebug()<<"error"<<db.lastError();
}
