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
        if(!qry->exec("select * from unitinfo;")){
            qDebug("Command failed!!!!");
             qDebug()<<"error:" <<qry->lastError();
        }

    }
    else{
        qry->prepare("Select * From unitinfo WHERE Serial='"+searchline+"'");
        qry->exec();
    }
    model->setQuery(*qry);

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void MainWindow::on_SaveButton_clicked()
{

    QSqlQuery* qry = new QSqlQuery(db);
    //qry->prepare("INSERT into unitinfo ( Serial, SKEW, BACKLASH) VALUES (:Serial, :SKEW, :BACKLASH)");
//    qry->bindValue(":Serial", SerialNum);
//    qry->bindValue(":SKEW", Skew);
//    qry->bindValue(":BACKLASH",Backlash);
    qry->exec("INSERT into unitinfo ( Serial, SKEW, BACKLASH) VALUES ('"+SerialNum+"','"+Skew+"','"+Backlash+"')");

    if(!qry->exec()){
        qDebug()<<"error:" <<qry->lastError();
    }
}
