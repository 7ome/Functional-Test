#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>


void MainWindow::on_SetDrillButton_clicked()
{
    sendcommand("G28\n");
    sendcommand("G1 X120 Y120 F12000\n");
}

void MainWindow::on_FullRunOutButton_clicked()
{
    sendcommand("G4\n");
    sendcommand("G1 X20 Y40\n");
    sendcommand("G1 X120 Y115\n");
    sendcommand("D110 R8\n");
    sendcommand("G1 Y120 F300\n");
    sendcommand("G4 S2\n");
    sendcommand("G1 Y110 F1000\n");
    sendcommand("D110 R0\n");
    sendcommand("G1 X20 Y40 F12000\n");
    sendcommand("D110 R100\n");
    sendcommand("D110 R75\n");
    sendcommand("D110 R50\n");
    sendcommand("D110 R25\n");
    delay(1);
    sendcommand("D110 R0\n");
}

void MainWindow::on_SpinMotorButton_clicked()
{
    std::string s = std::to_string(motorspeed);
    char const *speed= s.c_str();
    sendcommand("D110 R");
    sendcommand(speed);
    sendcommand("\n");
    //qDebug()<<motorspeed<<endl;
    delay(1);
}

void MainWindow::on_MotorSpeedSlider_valueChanged(int value)
{
    motorspeed = value;
}
void MainWindow::on_MotorSpeedSlider_sliderReleased()
{
    on_SpinMotorButton_clicked();
}
void MainWindow::on_RunOutButton_clicked()
{
    sendcommand("G1 X120 Y115\n");
    sendcommand("D110 R8\n");
    sendcommand("G1 Y120 F300\n");
    sendcommand("G4 S2\n");
    sendcommand("G1 Y110 F1000\n");
    sendcommand("D110 R0\n");
    sendcommand("G1 X20 Y40 F12000\n");
}

void MainWindow::on_NoiseButton_clicked()
{
    sendcommand("D110 R100\n");
    sendcommand("D110 R75\n");
    sendcommand("D110 R50\n");
    sendcommand("D110 R25\n");
    sendcommand("D110 R0\n");
}
void MainWindow::on_clearD_Button_clicked()
{
    ui->Drillother->setText("");
     ui->noise_checkBox->setChecked(0);
      ui->radioButton2_5->setChecked(0);
       ui->radioButton3_5->setChecked(0);
}

void MainWindow::on_DSaveButton_clicked()
{
    QString runout;

    QString noise = QString::number(ui->noise_checkBox->checkState());
    QString drillOther= ui->Drillother->text();
    if(ui->radioButton2_5->isChecked()){
        runout = ">2.5";
    }
    if(ui->radioButton3_5->isChecked()){
        runout = ">3.5";
    }
    else{
        runout = "<2.5";
    }
    QSqlQuery* qry = new QSqlQuery(db);
    if(!qry->exec("INSERT into drillinfo ( runout, noise, other) VALUES ('"+runout+"','"+noise+"','"+drillOther+"')")){
        qDebug()<<"error:" <<qry->lastError();
    }
    else{
        qDebug()<<" Saved Successfully!"<<endl;
        on_clearD_Button_clicked();
    }
}
void MainWindow::on_DPassButton_clicked()
{
    QSqlQuery* qry = new QSqlQuery(db);
    if(!qry->exec("INSERT into drillinfo ( runout, noise, other) VALUES ('<2.5','0','')")){
        qDebug()<<"error:" <<qry->lastError();
    }
    else{
        qDebug()<<" Saved Successfully!"<<endl;
        on_clearD_Button_clicked();
    }
}

