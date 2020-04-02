#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QDebug>

void MainWindow::on_HomeXButton_clicked()
{

    sendcommand("G28 X\n");
    sendcommand("G01 X5 F1000\n");
    sendcommand("M18\n");
}
void MainWindow::on_SpeedXButton_clicked()
{
    sendcommand("G28 X\n");
    sendcommand("G01 X128 F12000\n");
    sendcommand("G01 X0 F12000\n");
}
void MainWindow::on_SpinEButton_clicked()
{
    sendcommand("G01 E0 F180\n");
    sendcommand("G04 P1\n");
    for (int e=0; e<10;e++){
        sendcommand("G01 E4.5 F180\n");
        sendcommand("G01 E5.5 F180\n");
    }
    delay(1);
    sendcommand("G04 P1\n");
    sendcommand("G01 E0 F180\n");
    sendcommand("M18\n");
}
void MainWindow::on_HomeZDButton_clicked()
{
    sendcommand("G28 Z\n");
    sendcommand("G01 Z0 F200\n");
    sendcommand("M18\n");
}
void MainWindow::on_HomeZUButton_clicked()
{
    sendcommand("G28 Z\n");
    sendcommand("M18\n");
}
void MainWindow::on_FullBridgeTestButton_clicked()
{
    QString bridgeline= ui->BridgeSN->text();

    if(bridgeline.startsWith("B")){
        fullbridgeButton_clicked=true;
        on_HomeXButton_clicked();
        on_SpeedXButton_clicked();
        on_HomeZDButton_clicked();
        on_HomeZUButton_clicked();
    }
    else{
        msgbox.critical(nullptr,"Error!","Invalid Bridge Serial Number");
    }
}
//void MainWindow::fullbridge_status(int i){

//        if(qry->exec("SELECT description FROM issues WHERE description ='"+str[i].remove("error:  ")+"'")){
//            qDebug()<<"SELECT description FROM issues WHERE description ='"+str[i].remove("error:  ")+"'";
//            if(qry->isValid()){
//                qry->exec("INSERT INTO issues(description) VALUES('"+str[i]+")'");
//                qDebug()<<"INSERT INTO issues(description) VALUES('"+str[i]+")'";
//            }
//            else{
//                qDebug()<<qry->lastError();
//            }
//        }
//        else{
//            qDebug()<<qry->lastError();
//        }
//    }

void MainWindow::on_ProbePinsButton_clicked(){
    sendcommand("M125\n");
    probepinsButton_clicked = true;
    firstrun=true;
    probemounted = false;
    probetriggered =false;
    probedisconnected = false;
}
void MainWindow:: probestatus()
{
    ui->progressBar->setMaximum(countdown*10);
    ui->progressBar->setMinimum(0);

    if(probemounted && probetriggered && probedisconnected){
        ui->probeBrowser->setText("Probe Pogo Pin Passed!");
        probepinsButton_clicked = false;
    }
    else{
        while(!probemounted || !probetriggered || !probedisconnected)
        {
            if(countdown<0){
                ui->probeBrowser->setText("Probe Pogo Pin Failed!");
                qDebug("error: Probe Not Detected.");
                probepinsButton_clicked = false;
                break;
            }
            else{
                ui->progressBar->setValue(countdown*10);
                qDebug()<<countdown;
                countdown--;
                sendcommand("M125\n");
                delay(1);
            }
        }
    }
}
/*this is a weird take on probe pin testing
probe pins has only 3 ouputs from the printer; mounted, not mounted and triggered
the test requires to
1st - check if any attaachment is mounted before starting
2nd - ask user to mount probe
3rd - ask user to trigger probe
4th - ask user to untrigger probe (printer just returns mounted)
5th - ask user to un mount probe
It's written in a ladder-like approach using boolean state from previous step
to make sure that the user is following the test, else it will fail
*/
void MainWindow::check_probepins(int i)
{
    if(str[i].contains("Probe: Not Mounted")&& firstrun){
        ui->probeBrowser->setText("Mount Probe");
        firstrun = false;
        probedisconnected = true;
        countdown = 10;
        probestatus();
    }
    if(str[i].contains("Probe: Probe Mounted")&& probedisconnected){
        ui->probeBrowser->setText("Trigger Probe");
        probemounted = true;
        probedisconnected = false;
        countdown = 10;
        probestatus();
    }
    if(str[i].contains("Probe: Triggered")&& probemounted){
        ui->probeBrowser->setText("Release Trigger");
        probemounted=false;
        probetriggered=true;
        countdown = 10;
        probestatus();
    }
    if(str[i].contains("Probe: Probe Mounted")&& probetriggered && probetriggered){
        ui->probeBrowser->setText("Disconnect Probe");
        probemounted=true;
        probetriggered=false;
        countdown = 10;
        probestatus();
    }
    if(str[i].contains("Probe: Not Mounted")&& probemounted){
        probedisconnected=true;
        probetriggered=true;
        probestatus();
    }
    if(str[i].contains("Probe: Probe Mounted") && !probemounted){
        qDebug("Disconnect Probe to begin");
    }
    else{
    }
}
