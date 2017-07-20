#include "plotform.h"
#include "ui_plotform.h"

PlotForm::PlotForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotForm)
{
    ui->setupUi(this);
    curve = new QwtPlotCurve();
    symbol = new QwtSymbol(QwtSymbol::Rect);
}

PlotForm::~PlotForm()
{
//    delete curve;
//    delete symbol;
    delete ui;
}

void PlotForm::setPlottingData(QString title, QVector<double> xdata, QVector<double> ydata, QwtText xtext, QwtText ytext, QColor color)
{
    QwtText titleText = title;
    QFont font;
    font.setBold(true);
    font.setPointSize(6);
    titleText.setFont(font);

    QVector<double> sorted_xdata = xdata;
    qSort(sorted_xdata);
    double Xmin = sorted_xdata.first();
    double Xmax = sorted_xdata.last();
    QVector<double> sorted_ydata = ydata;
    qSort(sorted_ydata);
    double Ymin = sorted_ydata.first();
    double Ymax = sorted_ydata.last();

    curve->detach();
    ui->plotFrame->detachItems();
    ui->plotFrame->setTitle(titleText);
    ui->plotFrame->setAxisTitle(QwtPlot::xBottom, xtext);
    ui->plotFrame->setAxisTitle(QwtPlot::yLeft, ytext);
    curve->setSymbol(symbol);
    curve->setSamples(xdata, ydata);
    curve->setPen(QPen(color, 1));
    curve->attach(ui->plotFrame);
    ui->plotFrame->setAxisScale(QwtPlot::xBottom, Xmin-0.1, Xmax+0.1);
    ui->plotFrame->setAxisScale(QwtPlot::yLeft, Ymin-0.1, Ymax+0.1);
//    ui->plotFrame->setAxisAutoScale(QwtPlot::xBottom, true);
//    ui->plotFrame->setAxisAutoScale(QwtPlot::yLeft, true);
    ui->plotFrame->setCanvasBackground(Qt::white);
    ui->plotFrame->replot();
}
