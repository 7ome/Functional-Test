#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>


void MainWindow::on_TestProbe_Button_clicked()
{
    probetest_clicked = true;
    sendcommand("D104\n");
    sendcommand("G28Z\n");
}
void MainWindow:: probe_measurements(int i)
{
    QString probedisplacement;
    if(str[i].contains(" Measuring probe displacement of ")){
        probedisplacement = str[i].remove(" Measuring probe displacement of  ");
        ui->Probe_textBrowser->setText(probedisplacement);
        qDebug()<<probedisplacement<<endl;
    }
    else{}
    probetest_clicked = false;
}
