#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>


void MainWindow::on_TestProbe_Button_clicked()
{
    sendcommand("M93 R255 V180 B1 P30\n");
    probetest_clicked = true;
    for(int x=0;x<3;x++){
        sendcommand("D104\n");
    }
    sendcommand("G28Z\n");
}
void MainWindow:: probe_measurements(int i)
{
    QString probedisplacement;
    QSqlQuery* qry = new QSqlQuery(db);
    if(str[i].contains("log: measureProbeDisplacement") && ui->ProbeRecord_checkBox->isChecked()){
        probedisplacement = str[i].remove("log: measureProbeDisplacement returnValue:0 displacement:");
        ui->Probe_textBrowser->setText(probedisplacement);
        if(!qry->exec("INSERT into probeinfo (Displacement) VALUES ('"+probedisplacement+"')")){
            qDebug()<<"error:" <<qry->lastError();
        }
        else{
            if(probedisplacement.toDouble() <0.100 || probedisplacement.toDouble() >0.400){
                qDebug()<<probedisplacement.toDouble()<<endl;
                sendcommand("M93 R255 V1 B1 P0.2\n");
                msgbox.critical(nullptr,"U shall not PASS!","Probe displacement out of range!\n"+probedisplacement);}
            else{}
            qDebug("Probe Displacement Saved!");
        }
        probetest_clicked = false;
    }
    if(str[i].contains("log: measureProbeDisplacement")){
        probedisplacement = str[i].remove("log: measureProbeDisplacement returnValue:0 displacement:");
        ui->Probe_textBrowser->setText(probedisplacement);
        if(probedisplacement.toDouble() <0.100 || probedisplacement.toDouble() >0.400){
            sendcommand("M93 R255 V1 B1 P0.2\n");
            msgbox.critical(nullptr,"U shall not PASS!","Probe displacement out of range!\n"+probedisplacement);}

        else{}
        probetest_clicked = false;
    }
    else{}
}
void MainWindow::on_ProbeSave_Button_clicked()
{
    QSqlQuery* qry = new QSqlQuery(db);
    QString probeother = ui->Probeother->text();
    if(ui->Probeother->text() !=""){
        if(!qry->exec("INSERT into probeinfo (Displacement, Other) VALUES ('','"+probeother+"')")){
            qDebug()<<"error:" <<qry->lastError();
        }
        else{
            qDebug()<<probeother+"Succesfully Saved!"<<endl;
            ui->Probeother->clear();
        }
    }
    else{
    }
}
