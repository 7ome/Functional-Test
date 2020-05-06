#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <sstream>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->textBrowser->setText("Serial Connection: \tDisconnected\nDatabase Connection: \tDisconnected");
}
MainWindow::~MainWindow()
{
    delete ui;
    serial.close();
    db.close();
}
void MainWindow:: delay(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::on_pushButton_clicked()
{
    initialize_serialcom();
    //this is called when datas are received
    QObject::connect(&serial, &QSerialPort::readyRead, [&]
    {
        update_comstatus();
        datas = serial.readAll();
        //Split parts with "\n" and ignore empty strings
        str = datas.split(("\n"), QString::SkipEmptyParts);
        delay(1);
        //Print strings per line in console
        for (int strlength = 0; strlength < str.length(); strlength++) {
            std::cout << str.at(strlength).toStdString() << std::endl;
            if(str[strlength].contains("error:")){
                msgbox.critical(nullptr,"ERROR!",str[strlength].remove("error: "));
            }
            else
            {}
        }
        //Read Vone Values when Extract Button is clicked (in Database Page)
        if (extractButton_clicked){
            str.filter(datas);
            for (int i=0; i<str.length();i++){
                get_calibration(i);
            }
        }
        if(probepinsButton_clicked)
        {
            str.filter(datas);
            for (int i=0; i<str.length();i++){
                check_probepins(i);
            }
        }
        if(probetest_clicked){
            str.filter(datas);
            for (int i=0; i<str.length();i++){
                probe_measurements(i);
            }

        }
        else{}
    }
    );
    datas.clear();
    //this is called when serial com error occurs
    QObject::connect(&serial,static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                     (&QSerialPort::error),
                     [&](QSerialPort::SerialPortError error)
    {
        qDebug() << "An error occured: " << error;
        serialcom=false;
        update_comstatus();
    });
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


