#include <.\headers\mainwindow.h>
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
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(db);
    QString searchline =ui->Searchline->text();
    bool VoneRButton = ui->VoneRButton->isChecked();
    bool BridgeRButton = ui->BridgeRButton->isChecked();

    if(VoneRButton && searchline==NULL){
        if(!qry->exec("select * from unitinfo;")){
            qDebug()<<"error:" <<qry->lastError();
        }
    }
    if(BridgeRButton && searchline==NULL){
        if(!qry->exec("select * from bridgeinfo;")){
            qDebug()<<"error:" <<qry->lastError();
        }
    }
    if(VoneRButton && searchline!=NULL){
        if(!qry->exec("select * from unitinfo where Serial=' "+searchline+"';")){
            qDebug()<<"error:" <<qry->lastError();
        }
    }
    if(BridgeRButton && searchline!=NULL){
        if(!qry->exec("select * from bridgeinfo where BSerial='"+searchline+"';")){
            qDebug()<<"error:" <<qry->lastError();
        }
    }
    else{ }
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
        qDebug()<<SerialNum<<" Datas Saved Successfully!"<<endl;
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
        else{}
    }
    else{
        extractButton_clicked = false;
    }
}
void MainWindow::on_ViewGraphButton_clicked()
{
    QMainWindow secwindow;
    QChart *chart = new QChart();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
    QStringList categories;
    QBarSeries *series = new QBarSeries();
    QBarSet *set0 = new QBarSet("Pass");
    QBarSet *set1 = new QBarSet("Fail");

    *set0 << 10 << 20 << 30 ;
    *set1 << 50 << 10 << 10 ;
    series->append(set0);
    series->append(set1);

    categories<<"Bridge"<<"Drill"<<"Probe";
    chart->addSeries(series);
    chart->setTitle("Monthly Update");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY->setRange(0,60);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    secwindow.resize(420,300);
    secwindow.show();

    //    setCentralWidget(chartView);
    //    resize(420, 300);
    //    show();
}

void MainWindow::on_sqlline_returnPressed()
{
    QSqlQuery* qry = new QSqlQuery(db);
    QString sql_cmdline =ui->sqlline->text();
    QSqlQueryModel * model = new QSqlQueryModel();
    const char *ready = sql_cmdline.toLatin1().data();
    if(!qry->exec(ready)){
        qDebug()<<"error:" <<qry->lastError();
    }
    else{
        ui->sqlline->clear();
    }
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}
