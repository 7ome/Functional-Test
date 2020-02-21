#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>


void MainWindow::on_ExtractButton_clicked()
{
    sendcommand("M520\n");
    extractButton_clicked = true;
    delay(1);


}
void MainWindow::on_SearchButton_clicked()
{
    QString searchline =ui->Searchline->text();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(db);
    if(searchline==""){
        qry->prepare("SELECT * From UnitInfo");
        qry->exec();
    }
   else{
    qry->prepare("Select * From UnitInfo WHERE Serial='"+searchline+"'");
    qry->exec();

    }
    model->setQuery(*qry);
    ui->tableView->setModel(model);
}
void MainWindow::on_SaveButton_clicked()
{

    QSqlQuery* qry = new QSqlQuery(db);
    qry->prepare("INSERT into UnitInfo ( Serial, SKEW, BACKSLASH) VALUES (:Serial, :SKEW, :BACKSLASH)");
    qry->bindValue(":Serial", SerialNum);
    qry->bindValue(":SKEW", Skew);
    qry->bindValue(":BACKSLASH",Backslash);
    qry->exec();

    if(!qry->exec()){
        qDebug()<<"error:" <<qry->lastError();
    }
}
