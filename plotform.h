#ifndef PLOTFORM_H
#define PLOTFORM_H

#include <QWidget>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"

namespace Ui {
class PlotForm;
}

class PlotForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlotForm(QWidget *parent = 0);
    ~PlotForm();

    void setPlottingData(QString title, QVector<double> xdata, QVector<double> ydata, QwtText xtext, QwtText ytext, QColor color/*, double xmin, double xmax, double ymin, double ymax*/);

private:
    Ui::PlotForm *ui;
    QwtPlotCurve *curve;
    QwtSymbol *symbol;
};

#endif // PLOTFORM_H
