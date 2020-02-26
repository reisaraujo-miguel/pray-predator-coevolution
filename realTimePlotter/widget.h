#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QTimer>

#define TIME_1 5
#define TIME_2 10
#define TIME_3 50

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

private:
    void updatePlot();
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

};

#endif // WIDGET_H
