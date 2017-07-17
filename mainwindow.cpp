#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firmata = new QtFirmata("ttyACM0", 57600);

//    connect(this, &MainWindow::signalConnected, this, &MainWindow::initialize);

    connectFirmata();
    bool available = firmata->available();
    int isavailable = 0;
    if(available) isavailable = 1;
    else isavailable = 0;
    initialize();
    firmata->digitalWrite(allowancePin, QtFirmata::DIGITAL_HIGH);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectFirmata()
{
    bool isAvailable = false;
    firmata->connect();
    while(isAvailable == false){
        isAvailable = firmata->available();
    }
    emit signalConnected();
}

void MainWindow::initialize()
{
    if(firmata->available()){
        firmata->pinMode(panelAddressPin_1, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(panelAddressPin_2, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(panelAddressPin_3, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(panelAddressPin_4, QtFirmata::PINMODE_OUTPUT);

        firmata->pinMode(photoAddressPin_1, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(photoAddressPin_2, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(photoAddressPin_3, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(photoAddressPin_4, QtFirmata::PINMODE_OUTPUT);

        firmata->pinMode(measurementRangePin_1, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(measurementRangePin_2, QtFirmata::PINMODE_OUTPUT);

        firmata->pinMode(allowancePin, QtFirmata::PINMODE_OUTPUT);

        firmata->pinMode(currentLimitPin, QtFirmata::PINMODE_PWM);
        firmata->pinMode(voltageValuePin, QtFirmata::PINMODE_PWM);

        firmata->pinMode(panelCurrentMeasurePin, QtFirmata::PINMODE_ANALOG);
        firmata->pinMode(photoValueMeasurePin, QtFirmata::PINMODE_ANALOG);
    }
    else{
        qDebug("Device not available.");
        return;
    }
}

void MainWindow::on_pushButton_clicked()
{
    firmata->digitalWrite(allowancePin, QtFirmata::DIGITAL_HIGH);


}
