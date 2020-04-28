#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QTimer>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    QScrollArea* scrollArea;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_importButton_clicked();

    void on_herbDisp_clicked(bool checked);

    void on_herbMean_clicked(bool checked);

    void on_herbFit_clicked(bool checked);

    void on_carnDisp_clicked(bool checked);

    void on_carnMean_clicked(bool checked);

    void on_carnFit_clicked(bool checked);

    void on_updateCheckBox_clicked(bool checked);

    void timeOutSlot();

    void on_interval1SpinBox_valueChanged(int arg1);

    void on_interval2SpinBox_valueChanged(int arg1);

    void on_interval3SpinBox_valueChanged(int arg1);

    void on_carnScaleSpinBox_valueChanged(int arg1);

    void on_timeBegin_valueChanged(int arg1);

    void on_timeEnd_valueChanged(int arg1);

private:
    void updatePlot();
    void update_comparison_plot();
    void update_processed_comparison_plot();
    Ui::Widget *ui;
    QString fileName;
    QTimer *DataTimer;

    bool b_herbDisp, b_herbMean, b_herbFit, b_carnDisp, b_carnMean, b_carnFit;
    bool updateData;

    QVector<QVector<int>> energyHerb;
    QVector<QVector<int>> healthHerb;
    QVector<QVector<int>> hurtHerb;
    QVector<QVector<int>> energyCarn;
    QVector<float> averageHerb;
    QVector<float> averageHealth;
    QVector<float> averageHurt;
    QVector<float> averageCarn;

    QVector<float> averageHerbTime1;
    QVector<float> averageHerbTime2;
    QVector<float> averageHerbTime3;

    QVector<float> averageCarnTime1;
    QVector<float> averageCarnTime2;
    QVector<float> averageCarnTime3;

    QVector<float> averageHerbFitTime1;
    QVector<float> averageHerbFitTime2;
    QVector<float> averageHerbFitTime3;

    QVector<float> averageCarnFitTime1;
    QVector<float> averageCarnFitTime2;
    QVector<float> averageCarnFitTime3;

    int TIME_1;
    int TIME_2;
    int TIME_3;
    int generations;
    int comparison_carn_scale;
    int time_begin;
    int time_end;

};

#endif // WIDGET_H
