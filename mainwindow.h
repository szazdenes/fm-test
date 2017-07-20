#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    static const uint8_t panelAddressPin_0 = 19;
    static const uint8_t panelAddressPin_1 = 18;
    static const uint8_t panelAddressPin_2 = 2;
    static const uint8_t panelAddressPin_3 = 3;

    static const uint8_t photoAddressPin_0 = 7;
    static const uint8_t photoAddressPin_1 = 6;
    static const uint8_t photoAddressPin_2 = 5;
    static const uint8_t photoAddressPin_3 = 4;

    static const uint8_t measurementRangePin_1 = 8;
    static const uint8_t measurementRangePin_2 = 9;

    static const uint8_t voltageValuePin = 10;
    static const uint8_t currentLimitPin = 11;

    static const uint8_t allowancePin = 13;

    static const uint8_t photoValueMeasurePin = 14;
    static const uint8_t panelCurrentMeasurePin = 15;


    //Led panel címek
    static QList<int> A3Level;
    static QList<int> A2Level;
    static QList<int> A1Level;
    static QList<int> A0Level;

    //fotodióda címzése
    static QList<int> B3Level;
    static QList<int> B2Level;
    static QList<int> B1Level;
    static QList<int> B0Level;

    QtFirmata *firmata;
    QVector<double> Y_value1, Y_value2, Y_value3, Y_value4, X_value;

    void connectFirmata();
    void initialize();
    void setPanelAddress(int plateIndex);
    void setPhotoAddress(int photoIndex);
    void setPhotoRange(int rangeNum);
    void setVoltageAndCurrentLimit(double voltage, double current);

};

#endif // MAINWINDOW_H
