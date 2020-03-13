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
            qDebug()<<"error:" <<qry->lastError();
        }
    }
    else{
        qry->exec("Select * From unitinfo WHERE Serial='"+searchline+"'");
    }
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

}
void MainWindow::on_SaveButton_clicked()
{
    QSqlQuery* qry = new QSqlQuery(db);

    if(!qry->exec("INSERT into unitinfo ( Serial, SKEW, BACKLASH) VALUES ('"+SerialNum+"','"+Skew+"','"+Backlash+"')")){
        qDebug()<<"error:" <<qry->lastError();
    }
    else
    {
    }
}

void MainWindow::get_calibration(int i)
{
    //Search for Serial Number, Skew and Backlash
    //Remove unecessary tags (eg. logs)
    str[i].remove("log:  ");
    //m504 is serial tag
    if(str[i].contains("M504")){
        SerialNum =str[i].remove("M504 S");
        qDebug()<<SerialNum;
    }
    //m506 is skew tag
    if(str[i].contains("M506")){
        Skew = str[i].remove("M506 ");
        qDebug()<<Skew;
    }
    //m507 is backlash tag
    if(str[i].contains("M507")){
        Backlash = str[i].remove("M507 ");
        qDebug()<<Backlash;
        //after extracting backlash, skew and serial, print them in msgbox and ask user to save it
        QMessageBox::StandardButton reply;
        reply=msgbox.information(nullptr,"Unit Info", "Serial No:\t"+SerialNum+"\n Skew:\t"+Skew+"\n Backlash:\t"+Backlash,QMessageBox::Cancel | QMessageBox::Save);
        if(reply==QMessageBox::Save){
            on_SaveButton_clicked();
        }
        else{
        }
    }
    else{
        extractButton_clicked = false;
    }
}

void MainWindow::on_dbButton_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("batch7");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    if(db.open()){
        qDebug()<<"Connection to Database("<<db.databaseName()<<") Succesfull";
        dbcom=true;
        update_comstatus();

    }
   else{
        qDebug()<<"error"<<db.lastError();
        dbcom=false;
    }

}
