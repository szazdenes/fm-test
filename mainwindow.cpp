#include "mainwindow.h"
#include "ui_mainwindow.h"

QList<int> MainWindow::A3Level;
QList<int> MainWindow::A2Level;
QList<int> MainWindow::A1Level;
QList<int> MainWindow::A0Level;

QList<int> MainWindow::B3Level;
QList<int> MainWindow::B2Level;
QList<int> MainWindow::B1Level;
QList<int> MainWindow::B0Level;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    A3Level = QList<int>() << 0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  1 <<  1 <<  1 <<  1 <<  1 <<  1 <<  1 <<  1;
    A2Level = QList<int>() << 0 <<  0 <<  0 <<  0 <<  1 <<  1 <<  1 <<  1 <<  0 <<  0 <<  0 <<  0 <<  1 <<  1 <<  1 <<  1;
    A1Level = QList<int>() << 0 <<  0 <<  1 <<  1 <<  0 <<  0 <<  1 <<  1 <<  0 <<  0 <<  1 <<  1 <<  0 <<  0 <<  1 <<  1;
    A0Level = QList<int>() << 0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1;

    B3Level = QList<int>() << 1 <<  1 <<  1 <<  1 <<  1 <<  1 <<  1 <<  1 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0;
    B2Level = QList<int>() << 1 <<  1 <<  1 <<  1 <<  0 <<  0 <<  0 <<  0 <<  1 <<  1 <<  1 <<  1 <<  0 <<  0 <<  0 <<  0;
    B1Level = QList<int>() << 1 <<  1 <<  0 <<  0 <<  1 <<  1 <<  0 <<  0 <<  1 <<  1 <<  0 <<  0 <<  1 <<  1 <<  0 <<  0;
    B0Level = QList<int>() << 1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0 <<  1 <<  0;

    firmata = new QtFirmata("ttyACM0", 57600);

//    connect(this, &MainWindow::signalConnected, this, &MainWindow::initialize);

    connectFirmata();
    initialize();
}

MainWindow::~MainWindow()
{
    firmata->disconnect();
    delete ui;
}

void MainWindow::connectFirmata()
{
    firmata->connect();
    QEventLoop loop;
    QTimer::singleShot(4000, &loop, &QEventLoop::quit);
    loop.exec();
    if(firmata->available())
        qDebug("success");
    else
        qDebug("failure");
}

void MainWindow::initialize()
{
    if(firmata->available()){
        firmata->pinMode(panelAddressPin_0, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(panelAddressPin_1, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(panelAddressPin_2, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(panelAddressPin_3, QtFirmata::PINMODE_OUTPUT);

        firmata->pinMode(photoAddressPin_0, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(photoAddressPin_1, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(photoAddressPin_2, QtFirmata::PINMODE_OUTPUT);
        firmata->pinMode(photoAddressPin_3, QtFirmata::PINMODE_OUTPUT);

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

void MainWindow::setPanelAddress(int plateIndex)
{
    if(firmata->available()){
        if(A0Level.at(plateIndex) == 0) firmata->digitalWrite(panelAddressPin_0, QtFirmata::DIGITAL_LOW);
        if(A0Level.at(plateIndex) == 1) firmata->digitalWrite(panelAddressPin_0, QtFirmata::DIGITAL_HIGH);
        if(A1Level.at(plateIndex) == 0) firmata->digitalWrite(panelAddressPin_1, QtFirmata::DIGITAL_LOW);
        if(A1Level.at(plateIndex) == 1) firmata->digitalWrite(panelAddressPin_1, QtFirmata::DIGITAL_HIGH);
        if(A2Level.at(plateIndex) == 0) firmata->digitalWrite(panelAddressPin_2, QtFirmata::DIGITAL_LOW);
        if(A2Level.at(plateIndex) == 1) firmata->digitalWrite(panelAddressPin_2, QtFirmata::DIGITAL_HIGH);
        if(A3Level.at(plateIndex) == 0) firmata->digitalWrite(panelAddressPin_3, QtFirmata::DIGITAL_LOW);
        if(A3Level.at(plateIndex) == 1) firmata->digitalWrite(panelAddressPin_3, QtFirmata::DIGITAL_HIGH);
    }
    else{
        qDebug("Device not available.");
        return;
    }
}

void MainWindow::setPhotoAddress(int photoIndex)
{
    if(firmata->available()){
        if(B0Level.at(photoIndex) == 0) firmata->digitalWrite(photoAddressPin_0, QtFirmata::DIGITAL_LOW);
        if(B0Level.at(photoIndex) == 1) firmata->digitalWrite(photoAddressPin_0, QtFirmata::DIGITAL_HIGH);
        if(B1Level.at(photoIndex) == 0) firmata->digitalWrite(photoAddressPin_1, QtFirmata::DIGITAL_LOW);
        if(B1Level.at(photoIndex) == 1) firmata->digitalWrite(photoAddressPin_1, QtFirmata::DIGITAL_HIGH);
        if(B2Level.at(photoIndex) == 0) firmata->digitalWrite(photoAddressPin_2, QtFirmata::DIGITAL_LOW);
        if(B2Level.at(photoIndex) == 1) firmata->digitalWrite(photoAddressPin_2, QtFirmata::DIGITAL_HIGH);
        if(B3Level.at(photoIndex) == 0) firmata->digitalWrite(photoAddressPin_3, QtFirmata::DIGITAL_LOW);
        if(B3Level.at(photoIndex) == 1) firmata->digitalWrite(photoAddressPin_3, QtFirmata::DIGITAL_HIGH);
    }
    else{
        qDebug("Device not available.");
        return;
    }
}

void MainWindow::setPhotoRange(int rangeNum)
{
    if(firmata->available()){
        switch(rangeNum){
        case 1:
            firmata->digitalWrite(measurementRangePin_1, QtFirmata::DIGITAL_LOW);
            firmata->digitalWrite(measurementRangePin_2, QtFirmata::DIGITAL_LOW);
            break;
        case 2:
            firmata->digitalWrite(measurementRangePin_1, QtFirmata::DIGITAL_HIGH);
            firmata->digitalWrite(measurementRangePin_2, QtFirmata::DIGITAL_LOW);
            break;
        case 3:
            firmata->digitalWrite(measurementRangePin_1, QtFirmata::DIGITAL_LOW);
            firmata->digitalWrite(measurementRangePin_2, QtFirmata::DIGITAL_HIGH);
            break;
        }
    }
    else{
        qDebug("Device not available.");
        return;
    }

}

void MainWindow::setVoltageAndCurrentLimit(double voltage, double current)
{
    if(firmata->available()){
        if(voltage <= 40) firmata->analogWrite(voltageValuePin, (int)(voltage*255.0/40.0));
        if(current <= 20) firmata->analogWrite(currentLimitPin, (int)(current*255.0/20.0));

        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
    }
    else{
        qDebug("Device not available.");
        return;
    }
}

void MainWindow::on_pushButton_clicked()
{
    firmata->digitalWrite(allowancePin, QtFirmata::DIGITAL_HIGH);
    if(firmata->available())
            qDebug("success");
        else
            qDebug("failure");
    setVoltageAndCurrentLimit(10,10);

}
