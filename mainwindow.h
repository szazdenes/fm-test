#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>

#include "../QtFirmata/qtfirmata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signalConnected();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    static const uint8_t panelAddressPin_1 = 19;
    static const uint8_t panelAddressPin_2 = 18;
    static const uint8_t panelAddressPin_3 = 2;
    static const uint8_t panelAddressPin_4 = 3;

    static const uint8_t photoAddressPin_1 = 7;
    static const uint8_t photoAddressPin_2 = 6;
    static const uint8_t photoAddressPin_3 = 5;
    static const uint8_t photoAddressPin_4 = 4;

    static const uint8_t measurementRangePin_1 = 8;
    static const uint8_t measurementRangePin_2 = 9;

    static const uint8_t voltageValuePin = 10;
    static const uint8_t currentLimitPin = 11;

    static const uint8_t allowancePin = 13;

    static const uint8_t photoValueMeasurePin = 14;
    static const uint8_t panelCurrentMeasurePin = 15;

    QtFirmata *firmata;

    void connectFirmata();
    void initialize();
    void setPanelAddress(int panelNum);

};

#endif // MAINWINDOW_H
