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
    QString dbpath = "C:\\Users\\Tome\\Documents\\Funtional-Test\\Database\\Batch7.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("root");
    db.setDatabaseName(dbpath);
    //db.setUserName("Tome");
   // db.setPassword("password");

    db.open();
    QSqlQuery* qry = new QSqlQuery(db);
    qry->prepare("select * from calibration");
        bool ok = db.open();
      ui->stackedWidget->setCurrentIndex(4);

    if(db.open()){
        qDebug("Database is open");
        db.close();

    }
    else
        qDebug()<<"error"<<db.lastError();
}
