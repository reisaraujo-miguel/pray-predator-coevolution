// AVERAGE OVER TIME CONSIDERING FITTEST

#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QtMath>
#include <QScrollArea>
#include <QTimer>

#define SPECTRUM 10

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    fileName = "";

    energyHerb.resize(0);
    healthHerb.resize(0);
    hurtHerb.resize(0);
    energyCarn.resize(0);
    averageHerb.resize(0);
    averageHealth.resize(0);
    averageHurt.resize(0);
    averageCarn.resize(0);

    averageCarnTime1.resize(0);
    averageCarnTime2.resize(0);
    averageCarnTime3.resize(0);
    averageHerbTime1.resize(0);
    averageHerbTime2.resize(0);
    averageHerbTime3.resize(0);

    averageCarnFitTime1.resize(0);
    averageCarnFitTime2.resize(0);
    averageCarnFitTime3.resize(0);
    averageHerbFitTime1.resize(0);
    averageHerbFitTime2.resize(0);
    averageHerbFitTime3.resize(0);

    b_herbDisp = true;
    b_herbMean = true;
    b_herbFit = true;
    b_carnDisp = true;
    b_carnMean = true;
    b_carnFit = true;

    updateData = false;

    TIME_1 = 5;
    TIME_2 = 10;
    TIME_3 = 50;

    comparison_carn_scale = 1;

    generations = 0;

    scrollArea = new QScrollArea(this);
    //scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setGeometry(20,290,841,380);
    //scrollArea->setWidgetResizable(true);
    //scrollArea->ensureWidgetVisible(ui->graphWidget);
    scrollArea->setWidget(ui->graphWidget);
/*
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->tabWidget,0,0,0,1);
    layout->addWidget(ui->graphManagerBox,0,2,0,2);
    layout->addWidget(scrollArea,2,0,2,4);
    this->setLayout(layout);
*/
    DataTimer = new QTimer(this);
    connect(DataTimer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    DataTimer->start(1000); // timeout() at 1 second interval
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_importButton_clicked()
{
    QString dataDir;

    //----- Find data directory -----//
    QString currDir = qApp->applicationDirPath(); // the pointer qApp refers to the application
    QStringList pieces = currDir.split( "/" ); // spliting directory path, the "/" are lost

    for(int i=0;i<pieces.length()-1;i++){ // the last two folders Qt and DataAnalyzer are ignored
        dataDir+=pieces.value(i);
        dataDir+="/";
    }
    dataDir+="evolutionaryAlgorithm/plotterData/";

    //----- Get file -----//
   fileName = QFileDialog::getOpenFileName(this, "Select the data file", dataDir, "Text Files (*txt)");

    if(fileName.size()==0) // if the user presses cancel, getOpenFileName returns a null string
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }


    //----- Read file header -----//
    QTextStream in(&file);

    QString line;
    QStringList fields;

    qDebug()<<"...";

    fields = fileName.split("/");
    ui->editFileName->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editHerb->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editCarn->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editPlants->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editGen->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editHealth->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editHurt->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editFrames->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editHerHerb->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editHerCarn->setText(fields.back());
    line = in.readLine();
    fields = line.split(" ");
    ui->editEvaluate->setText(fields.back());



    //-------- Get graph values ------//
    line = in.readLine(); // empty line
    int i, j, k, g, h, c;
    g = ui->editGen->text().toInt();
    generations = g;
    h = ui->editHerb->text().toInt();
    c = ui->editCarn->text().toInt();

    energyHerb.resize(g+1);
    healthHerb.resize(g+1);
    hurtHerb.resize(g+1);
    energyCarn.resize(g+1);

    averageHerb.resize(g+1);
    averageHealth.resize(g+1);
    averageHurt.resize(g+1);
    averageCarn.resize(g+1);

    averageCarnTime1.resize(g+1);
    averageCarnTime2.resize(g+1);
    averageCarnTime3.resize(g+1);

    averageHerbTime1.resize(g+1);
    averageHerbTime2.resize(g+1);
    averageHerbTime3.resize(g+1);

    averageCarnFitTime1.resize(g+1);
    averageCarnFitTime2.resize(g+1);
    averageCarnFitTime3.resize(g+1);

    averageHerbFitTime1.resize(g+1);
    averageHerbFitTime2.resize(g+1);
    averageHerbFitTime3.resize(g+1);


    for(i=0; i<(g+1); i++){
        energyHerb[i].resize(h);
        healthHerb[i].resize(h);
        hurtHerb[i].resize(h);
        energyCarn[i].resize(c);

        averageHerb[i] = 0;
        averageHealth[i] = 0;
        averageHurt[i] = 0;
        averageCarn[i] = 0;

        line = in.readLine(); // generation header
        line = in.readLine(); // herbivores
        fields = line.split(" ");
        for(j=0; j<h; j++){
            energyHerb[i][j] = fields[j+1].toInt();
            averageHerb[i] += energyHerb[i][j];
            //printf("%d\n",energyHerb[i][j]);
        }
        averageHerb[i] = averageHerb[i]/h;
        //printf("%f ",averageHerb[i]);

        line = in.readLine(); // health
        fields = line.split(" ");
        for(j=0; j<h; j++){
            healthHerb[i][j] = fields[j+1].toInt();
            averageHealth[i] += healthHerb[i][j];
        }
        averageHealth[i] = averageHealth[i]/h;

        line = in.readLine(); // hurt
        fields = line.split(" ");
        for(j=0; j<h; j++){
            hurtHerb[i][j] = fields[j+1].toInt();
            averageHurt[i] += hurtHerb[i][j];
        }
        averageHurt[i] = averageHurt[i]/h;

        line = in.readLine(); // carnivores
        fields = line.split(" ");
        for(j=0; j<c; j++){
            energyCarn[i][j] = fields[j+1].toInt();
            averageCarn[i] += energyCarn[i][j];
            //printf("%d\n",energyCarn[i][j]);
        }
        averageCarn[i] = averageCarn[i]/h;

        // Mean value of mean and fittest energy over interval TIME_1

        if(i >= (TIME_1 - 1)){
            averageHerbTime1[i] = 0;
            averageCarnTime1[i] = 0;
            averageHerbFitTime1[i] = 0;
            averageCarnFitTime1[i] = 0;

            for(k = (i - TIME_1 + 1); k<=i; k++){
                averageHerbTime1[i] = averageHerbTime1[i] + averageHerb[k];
                averageCarnTime1[i] = averageCarnTime1[i] + averageCarn[k];

                averageHerbFitTime1[i] = averageHerbFitTime1[i] + energyHerb[k][0];
                averageCarnFitTime1[i] = averageCarnFitTime1[i] + energyCarn[k][0];
            }
            averageHerbTime1[i] = averageHerbTime1[i]/TIME_1;
            averageCarnTime1[i] = averageCarnTime1[i]/TIME_1;
            averageHerbFitTime1[i] = averageHerbFitTime1[i]/TIME_1;
            averageCarnFitTime1[i] = averageCarnFitTime1[i]/TIME_1;
        }
        else{
            averageHerbTime1[i] = 0;
            averageCarnTime1[i] = 0;
            averageHerbFitTime1[i] = 0;
            averageCarnFitTime1[i] = 0;
        }

        // Mean value over interval TIME_2

        if(i >= (TIME_2 - 1)){
            averageHerbTime2[i] = 0;
            averageCarnTime2[i] = 0;
            averageHerbFitTime2[i] = 0;
            averageCarnFitTime2[i] = 0;

            for(k = (i - TIME_2 + 1); k<=i; k++){
                averageHerbTime2[i] = averageHerbTime2[i] + averageHerb[k];
                averageCarnTime2[i] = averageCarnTime2[i] + averageCarn[k];

                averageHerbFitTime2[i] = averageHerbFitTime2[i] + energyHerb[k][0];
                averageCarnFitTime2[i] = averageCarnFitTime2[i] + energyCarn[k][0];
            }
            averageHerbTime2[i] = averageHerbTime2[i]/TIME_2;
            averageCarnTime2[i] = averageCarnTime2[i]/TIME_2;
            averageHerbFitTime2[i] = averageHerbFitTime2[i]/TIME_2;
            averageCarnFitTime2[i] = averageCarnFitTime2[i]/TIME_2;
        }
        else{
            averageHerbTime2[i] = 0;
            averageCarnTime2[i] = 0;
            averageHerbFitTime2[i] = 0;
            averageCarnFitTime2[i] = 0;
        }

        // Mean value over interval TIME_3

        if(i >= (TIME_3 - 1)){
            averageHerbTime3[i] = 0;
            averageCarnTime3[i] = 0;
            averageHerbFitTime3[i] = 0;
            averageCarnFitTime3[i] = 0;

            for(k = (i - TIME_3 + 1); k<=i; k++){
                averageHerbTime3[i] = averageHerbTime3[i] + averageHerb[k];
                averageCarnTime3[i] = averageCarnTime3[i] + averageCarn[k];

                averageHerbFitTime3[i] = averageHerbFitTime3[i] + energyHerb[k][0];
                averageCarnFitTime3[i] = averageCarnFitTime3[i] + energyCarn[k][0];
            }
            averageHerbTime3[i] = averageHerbTime3[i]/TIME_3;
            averageCarnTime3[i] = averageCarnTime3[i]/TIME_3;
            averageHerbFitTime3[i] = averageHerbFitTime3[i]/TIME_3;
            averageCarnFitTime3[i] = averageCarnFitTime3[i]/TIME_3;
        }
        else{
            averageHerbTime3[i] = 0;
            averageCarnTime3[i] = 0;
            averageHerbFitTime3[i] = 0;
            averageCarnFitTime3[i] = 0;
        }

        if(in.atEnd()==true){
            g = i;
            generations = g;
            ui->editGen->setText(QString::number(g));
            //printf("%d\n",g);
        }

    }
    ui->interval1SpinBox->setMaximum(generations);
    ui->interval2SpinBox->setMaximum(generations);
    ui->interval3SpinBox->setMaximum(generations);
    ui->timeBegin->setMaximum(generations);
    ui->timeEnd->setMaximum(generations);

    ui->interval1SpinBox->setValue(TIME_1);
    ui->interval2SpinBox->setValue(TIME_2);
    ui->interval3SpinBox->setValue(TIME_3);

    ui->timeBegin->setValue(0);
    ui->timeEnd->setValue(generations);
    time_begin = 0;
    time_end = generations;

    file.close();

    //----- when getting data from new file -----//
    ui->graphCarn->xAxis->setRange(0,1);
    ui->graphCarn->yAxis->setRange(0,1);

    ui->graphHerb->xAxis->setRange(0,1);
    ui->graphHerb->yAxis->setRange(0,1);

    ui->graphHerbHealth->xAxis->setRange(0,1);
    ui->graphHerbHealth->yAxis->setRange(0,1);

    ui->graphHerbHurt->xAxis->setRange(0,1);
    ui->graphHerbHurt->yAxis->setRange(0,1);


    updatePlot();
}



void Widget::updatePlot()
{

    ui->graphCarn->clearGraphs();
    ui->graphHerb->clearGraphs();
    ui->graphHerbHurt->clearGraphs();
    ui->graphHerbHealth->clearGraphs();
    ui->graphCarnPro->clearGraphs();
    ui->graphHerbPro->clearGraphs();
    ui->graphCarnProFit->clearGraphs();
    ui->graphHerbProFit->clearGraphs();
    ui->graphBoth->clearGraphs();

    int i, j, g, h, c;
    g = ui->editGen->text().toInt();
    h = ui->editHerb->text().toInt();
    c = ui->editCarn->text().toInt();

    ui->graphHerb->yAxis->setTickLabels(true);
    ui->graphHerb->xAxis->setTickLabels(true);
    ui->graphHerb->yAxis->setLabel("Energy");
    ui->graphHerb->xAxis->setLabel("Generation");

    ui->graphHerbHealth->yAxis->setTickLabels(true);
    ui->graphHerbHealth->xAxis->setTickLabels(true);
    ui->graphHerbHealth->yAxis->setLabel("Health");
    ui->graphHerbHealth->xAxis->setLabel("Generation");

    ui->graphHerbHurt->yAxis->setTickLabels(true);
    ui->graphHerbHurt->xAxis->setTickLabels(true);
    ui->graphHerbHurt->yAxis->setLabel("Hurt");
    ui->graphHerbHurt->xAxis->setLabel("Generation");

    ui->graphCarn->yAxis->setTickLabels(true);
    ui->graphCarn->xAxis->setTickLabels(true);
    ui->graphCarn->yAxis->setLabel("Energy");
    ui->graphCarn->xAxis->setLabel("Generation");

    ui->graphCarnPro->yAxis->setTickLabels(true);
    ui->graphCarnPro->xAxis->setTickLabels(true);
    ui->graphCarnPro->yAxis->setLabel("Mean energy value");
    ui->graphCarnPro->xAxis->setLabel("Generation");
    ui->graphCarnPro->legend->setVisible(true);
    ui->graphCarnPro->setFont(QFont("Helvetica", 9));
    // LEGEND ALIGNMENT
    ui->graphCarnPro->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphHerbPro->yAxis->setTickLabels(true);
    ui->graphHerbPro->xAxis->setTickLabels(true);
    ui->graphHerbPro->yAxis->setLabel("Mean energy value");
    ui->graphHerbPro->xAxis->setLabel("Generation");
    ui->graphHerbPro->legend->setVisible(true);
    ui->graphHerbPro->setFont(QFont("Helvetica", 9));
    ui->graphHerbPro->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphCarnProFit->yAxis->setTickLabels(true);
    ui->graphCarnProFit->xAxis->setTickLabels(true);
    ui->graphCarnProFit->yAxis->setLabel("Fittest energy value");
    ui->graphCarnProFit->xAxis->setLabel("Generation");
    ui->graphCarnProFit->legend->setVisible(true);
    ui->graphCarnProFit->setFont(QFont("Helvetica", 9));
    ui->graphCarnProFit->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphHerbProFit->yAxis->setTickLabels(true);
    ui->graphHerbProFit->xAxis->setTickLabels(true);
    ui->graphHerbProFit->yAxis->setLabel("Fittest energy value");
    ui->graphHerbProFit->xAxis->setLabel("Generation");
    ui->graphHerbProFit->legend->setVisible(true);
    ui->graphHerbProFit->setFont(QFont("Helvetica", 9));
    ui->graphHerbProFit->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphBoth->yAxis->setTickLabels(true);
    ui->graphBoth->xAxis->setTickLabels(true);
    ui->graphBoth->yAxis->setLabel("Mean energy value");
    ui->graphBoth->xAxis->setLabel("Generation");
    ui->graphBoth->legend->setVisible(true);
    ui->graphBoth->setFont(QFont("Helvetica",9));
    ui->graphBoth->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);


    // HERBIVORE GRAPH

    // best herbivore
    ui->graphHerb->addGraph();
    ui->graphHerb->graph(0)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerb->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerb->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_herbFit == true){
        for(j=0; j<(g+1); j++){
            ui->graphHerb->graph(0)->addData(j,energyHerb[j][0]);
        }
        //ui->graphHerb->graph(0)->rescaleAxes(true);
        ui->graphHerb->graph(0)->rescaleKeyAxis(true);
        ui->graphHerb->graph(0)->rescaleValueAxis(true,true);
    }


    for(i=1; i<h; i++){
        ui->graphHerb->addGraph();
        ui->graphHerb->graph(i)->setPen(QPen(QColor(0,0,255,255)));
        ui->graphHerb->graph(i)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsNone));
        ui->graphHerb->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

        if(b_herbDisp == true){
            for(j=0; j<(g+1); j++){
                ui->graphHerb->graph(i)->addData(j,energyHerb[j][i]);
            }
            //ui->graphHerb->graph(i)->rescaleAxes(true);
            ui->graphHerb->graph(i)->rescaleKeyAxis(true);
            ui->graphHerb->graph(i)->rescaleValueAxis(true,true);
        }
    }

    // herbivore mean graph
    ui->graphHerb->addGraph();
    ui->graphHerb->graph(h)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerb->graph(h)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerb->graph(h)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_herbMean == true){
        for(j=0; j<(g+1); j++){
            ui->graphHerb->graph(h)->addData(j,averageHerb[j]);
            //printf("%f ",averageHerb[j]);
            ui->graphHerb->graph(h)->rescaleKeyAxis(true);
            ui->graphHerb->graph(h)->rescaleValueAxis(true,true);
        }
    }

    // HEALTH GRAPH

    // best herbivore
    ui->graphHerbHealth->addGraph();
    ui->graphHerbHealth->graph(0)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerbHealth->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbHealth->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_herbFit == true){
        for(j=0; j<(g+1); j++){
            ui->graphHerbHealth->graph(0)->addData(j,healthHerb[j][0]);
        }
        ui->graphHerbHealth->graph(0)->rescaleKeyAxis(true);
        ui->graphHerbHealth->graph(0)->rescaleValueAxis(true,true);
    }

    for(i=1; i<h; i++){
        ui->graphHerbHealth->addGraph();
        ui->graphHerbHealth->graph(i)->setPen(QPen(QColor(0,0,255,255)));
        ui->graphHerbHealth->graph(i)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsNone));
        ui->graphHerbHealth->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

        if(b_herbDisp == true){
            for(j=0; j<(g+1); j++){
                ui->graphHerbHealth->graph(i)->addData(j,healthHerb[j][i]);
            }
            ui->graphHerbHealth->graph(i)->rescaleKeyAxis(true);
            ui->graphHerbHealth->graph(i)->rescaleValueAxis(true,true);
        }
    }

    // herbivore mean graph
    ui->graphHerbHealth->addGraph();
    ui->graphHerbHealth->graph(h)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerbHealth->graph(h)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbHealth->graph(h)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_herbMean == true){
        for(j=0; j<(g+1); j++){
            ui->graphHerbHealth->graph(h)->addData(j,averageHealth[j]);
        }
        ui->graphHerbHealth->graph(h)->rescaleKeyAxis(true);
        ui->graphHerbHealth->graph(h)->rescaleValueAxis(true,true);
    }

    // HURT GRAPH

    // best herbivore
    ui->graphHerbHurt->addGraph();
    ui->graphHerbHurt->graph(0)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerbHurt->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbHurt->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_herbFit == true){
        for(j=0; j<(g+1); j++){
            ui->graphHerbHurt->graph(0)->addData(j,hurtHerb[j][0]);
        }
        ui->graphHerbHurt->graph(0)->rescaleKeyAxis(true);
        ui->graphHerbHurt->graph(0)->rescaleValueAxis(true,true);
    }

    for(i=1; i<h; i++){
        ui->graphHerbHurt->addGraph();
        ui->graphHerbHurt->graph(i)->setPen(QPen(QColor(0,0,255,255)));
        ui->graphHerbHurt->graph(i)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsNone));
        ui->graphHerbHurt->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

        if(b_herbDisp == true){
            for(j=0; j<(g+1); j++){
                ui->graphHerbHurt->graph(i)->addData(j,hurtHerb[j][i]);
            }
            ui->graphHerbHurt->graph(i)->rescaleKeyAxis(true);
            ui->graphHerbHurt->graph(i)->rescaleValueAxis(true,true);
        }
    }

    // herbivore mean graph
    ui->graphHerbHurt->addGraph();
    ui->graphHerbHurt->graph(h)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerbHurt->graph(h)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbHurt->graph(h)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_herbMean == true){
        for(j=0; j<(g+1); j++){
            ui->graphHerbHurt->graph(h)->addData(j,averageHurt[j]);
        }
        ui->graphHerbHurt->graph(h)->rescaleKeyAxis(true);
        ui->graphHerbHurt->graph(h)->rescaleValueAxis(true,true);
    }

    // CARNIVORE GRAPH

    // best carnivore
    ui->graphCarn->addGraph();
    ui->graphCarn->graph(0)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphCarn->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarn->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_carnFit == true){
        for(j=0; j<(g+1); j++){
            ui->graphCarn->graph(0)->addData(j,energyCarn[j][0]);
        }

        //ui->graphCarn->graph(0)->rescaleAxes(true);
        ui->graphCarn->graph(0)->rescaleKeyAxis(true);
        ui->graphCarn->graph(0)->rescaleValueAxis(true,true);
    }

    for(i=1; i<c; i++){
        ui->graphCarn->addGraph();
        ui->graphCarn->graph(i)->setPen(QPen(QColor(0,0,255,255)));
        ui->graphCarn->graph(i)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsNone));
        ui->graphCarn->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

        if(b_carnDisp == true){
            for(j=0; j<(g+1); j++){
                ui->graphCarn->graph(i)->addData(j,energyCarn[j][i]);
            }

            //ui->graphCarn->graph(i)->rescaleAxes(true);
            ui->graphCarn->graph(i)->rescaleKeyAxis(true);
            ui->graphCarn->graph(i)->rescaleValueAxis(true,true);
        }
    }

    // carnivore mean graph
    ui->graphCarn->addGraph();
    ui->graphCarn->graph(c)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphCarn->graph(c)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarn->graph(c)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

    if(b_carnMean == true){
        for(j=0; j<(g+1); j++){
            ui->graphCarn->graph(c)->addData(j,averageCarn[j]);
            //printf("%f ",averageCarn[j]);
        }
        ui->graphCarn->graph(c)->rescaleKeyAxis(true);
        ui->graphCarn->graph(c)->rescaleValueAxis(true,true);
    }

    //------------------------- PROCESSED DATA -------------------------//

    // HERBIVORES

    // time1
    ui->graphHerbPro->addGraph();
    ui->graphHerbPro->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerbPro->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbPro->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbPro->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbPro->graph(0)->addData(j,averageHerbTime1[j]);
        }
        ui->graphHerbPro->graph(0)->rescaleKeyAxis(false);
        ui->graphHerbPro->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphHerbProFit->addGraph();
    ui->graphHerbProFit->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerbProFit->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbProFit->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbProFit->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbProFit->graph(0)->addData(j,averageHerbFitTime1[j]);
        }
        ui->graphHerbProFit->graph(0)->rescaleKeyAxis(false);
        ui->graphHerbProFit->graph(0)->rescaleValueAxis(false,true);
    //}

    // time2
    ui->graphHerbPro->addGraph();
    ui->graphHerbPro->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerbPro->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbPro->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbPro->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbPro->graph(1)->addData(j,averageHerbTime2[j]);
        }
        ui->graphHerbPro->graph(1)->rescaleKeyAxis(true);
        ui->graphHerbPro->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphHerbProFit->addGraph();
    ui->graphHerbProFit->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerbProFit->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbProFit->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbProFit->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbProFit->graph(1)->addData(j,averageHerbFitTime2[j]);
        }
        ui->graphHerbProFit->graph(1)->rescaleKeyAxis(true);
        ui->graphHerbProFit->graph(1)->rescaleValueAxis(true,true);
    //}

    // time3
    ui->graphHerbPro->addGraph();
    ui->graphHerbPro->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphHerbPro->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbPro->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbPro->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbPro->graph(2)->addData(j,averageHerbTime3[j]);
        }
        ui->graphHerbPro->graph(2)->rescaleKeyAxis(true);
        ui->graphHerbPro->graph(2)->rescaleValueAxis(true,true);
    //}

    ui->graphHerbProFit->addGraph();
    ui->graphHerbProFit->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphHerbProFit->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbProFit->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbProFit->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbProFit->graph(2)->addData(j,averageHerbFitTime3[j]);
        }
        ui->graphHerbProFit->graph(2)->rescaleKeyAxis(true);
        ui->graphHerbProFit->graph(2)->rescaleValueAxis(true,true);
    //}

    // CARNIVORES

    // time1
    ui->graphCarnPro->addGraph();
    ui->graphCarnPro->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphCarnPro->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnPro->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnPro->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnPro->graph(0)->addData(j,averageCarnTime1[j]);
        }
        ui->graphCarnPro->graph(0)->rescaleKeyAxis(false);
        ui->graphCarnPro->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphCarnProFit->addGraph();
    ui->graphCarnProFit->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphCarnProFit->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnProFit->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnProFit->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnProFit->graph(0)->addData(j,averageCarnFitTime1[j]);
        }
        ui->graphCarnProFit->graph(0)->rescaleKeyAxis(false);
        ui->graphCarnProFit->graph(0)->rescaleValueAxis(false,true);
    //}

    // time2
    ui->graphCarnPro->addGraph();
    ui->graphCarnPro->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphCarnPro->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnPro->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnPro->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnPro->graph(1)->addData(j,averageCarnTime2[j]);
        }
        ui->graphCarnPro->graph(1)->rescaleKeyAxis(true);
        ui->graphCarnPro->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphCarnProFit->addGraph();
    ui->graphCarnProFit->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphCarnProFit->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnProFit->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnProFit->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnProFit->graph(1)->addData(j,averageCarnFitTime2[j]);
        }
        ui->graphCarnProFit->graph(1)->rescaleKeyAxis(true);
        ui->graphCarnProFit->graph(1)->rescaleValueAxis(true,true);
    //}

    // time3
    ui->graphCarnPro->addGraph();
    ui->graphCarnPro->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphCarnPro->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnPro->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnPro->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnPro->graph(2)->addData(j,averageCarnTime3[j]);
        }
        ui->graphCarnPro->graph(2)->rescaleKeyAxis(true);
        ui->graphCarnPro->graph(2)->rescaleValueAxis(true,true);
    //}

    ui->graphCarnProFit->addGraph();
    ui->graphCarnProFit->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphCarnProFit->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnProFit->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnProFit->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnProFit->graph(2)->addData(j,averageCarnFitTime3[j]);
        }
        ui->graphCarnProFit->graph(2)->rescaleKeyAxis(true);
        ui->graphCarnProFit->graph(2)->rescaleValueAxis(true,true);
    //}

    //------------------------- COMPARISON -------------------------//

    ui->graphBoth->addGraph();
    ui->graphBoth->graph(0)->setPen(QPen(QColor(255,0,0,255)));
    ui->graphBoth->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphBoth->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphBoth->graph(0)->setName("Carnivores - " + QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphBoth->graph(0)->addData(j,comparison_carn_scale*averageCarnTime3[j]);
        }
        ui->graphBoth->graph(0)->rescaleKeyAxis(false);
        ui->graphBoth->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphBoth->addGraph();
    ui->graphBoth->graph(1)->setPen(QPen(QColor(0,0,255,255)));
    ui->graphBoth->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphBoth->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphBoth->graph(1)->setName("Herbivores - " + QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphBoth->graph(1)->addData(j,averageHerbTime3[j]);
        }
        ui->graphBoth->graph(1)->rescaleKeyAxis(true);
        ui->graphBoth->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphHerb->replot();
    ui->graphCarn->replot();
    ui->graphHerbHurt->replot();
    ui->graphHerbHealth->replot();
    ui->graphHerbPro->replot();
    ui->graphCarnPro->replot();
    ui->graphHerbProFit->replot();
    ui->graphCarnProFit->replot();
    ui->graphBoth->replot();
}

void Widget::update_processed_comparison_plot()
{
    ui->graphCarnPro->clearGraphs();
    ui->graphHerbPro->clearGraphs();
    ui->graphCarnProFit->clearGraphs();
    ui->graphHerbProFit->clearGraphs();
    ui->graphBoth->clearGraphs();

    int i, j, g, h, c;
    g = ui->editGen->text().toInt();
    h = ui->editHerb->text().toInt();
    c = ui->editCarn->text().toInt();

    ui->graphCarnPro->yAxis->setTickLabels(true);
    ui->graphCarnPro->xAxis->setTickLabels(true);
    ui->graphCarnPro->yAxis->setLabel("Mean energy value");
    ui->graphCarnPro->xAxis->setLabel("Generation");
    ui->graphCarnPro->legend->setVisible(true);
    ui->graphCarnPro->setFont(QFont("Helvetica", 9));
    // LEGEND ALIGNMENT
    ui->graphCarnPro->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphHerbPro->yAxis->setTickLabels(true);
    ui->graphHerbPro->xAxis->setTickLabels(true);
    ui->graphHerbPro->yAxis->setLabel("Mean energy value");
    ui->graphHerbPro->xAxis->setLabel("Generation");
    ui->graphHerbPro->legend->setVisible(true);
    ui->graphHerbPro->setFont(QFont("Helvetica", 9));
    ui->graphHerbPro->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphCarnProFit->yAxis->setTickLabels(true);
    ui->graphCarnProFit->xAxis->setTickLabels(true);
    ui->graphCarnProFit->yAxis->setLabel("Fittest energy value");
    ui->graphCarnProFit->xAxis->setLabel("Generation");
    ui->graphCarnProFit->legend->setVisible(true);
    ui->graphCarnProFit->setFont(QFont("Helvetica", 9));
    ui->graphCarnProFit->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphHerbProFit->yAxis->setTickLabels(true);
    ui->graphHerbProFit->xAxis->setTickLabels(true);
    ui->graphHerbProFit->yAxis->setLabel("Fittest energy value");
    ui->graphHerbProFit->xAxis->setLabel("Generation");
    ui->graphHerbProFit->legend->setVisible(true);
    ui->graphHerbProFit->setFont(QFont("Helvetica", 9));
    ui->graphHerbProFit->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->graphBoth->yAxis->setTickLabels(true);
    ui->graphBoth->xAxis->setTickLabels(true);
    ui->graphBoth->yAxis->setLabel("Mean energy value");
    ui->graphBoth->xAxis->setLabel("Generation");
    ui->graphBoth->legend->setVisible(true);
    ui->graphBoth->setFont(QFont("Helvetica",9));
    ui->graphBoth->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    //------------------------- PROCESSED DATA -------------------------//

    // HERBIVORES

    // time1
    ui->graphHerbPro->addGraph();
    ui->graphHerbPro->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerbPro->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbPro->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbPro->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbPro->graph(0)->addData(j,averageHerbTime1[j]);
        }
        ui->graphHerbPro->graph(0)->rescaleKeyAxis(false);
        ui->graphHerbPro->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphHerbProFit->addGraph();
    ui->graphHerbProFit->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphHerbProFit->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbProFit->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbProFit->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbProFit->graph(0)->addData(j,averageHerbFitTime1[j]);
        }
        ui->graphHerbProFit->graph(0)->rescaleKeyAxis(false);
        ui->graphHerbProFit->graph(0)->rescaleValueAxis(false,true);
    //}

    // time2
    ui->graphHerbPro->addGraph();
    ui->graphHerbPro->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerbPro->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbPro->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbPro->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbPro->graph(1)->addData(j,averageHerbTime2[j]);
        }
        ui->graphHerbPro->graph(1)->rescaleKeyAxis(true);
        ui->graphHerbPro->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphHerbProFit->addGraph();
    ui->graphHerbProFit->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphHerbProFit->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbProFit->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbProFit->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbProFit->graph(1)->addData(j,averageHerbFitTime2[j]);
        }
        ui->graphHerbProFit->graph(1)->rescaleKeyAxis(true);
        ui->graphHerbProFit->graph(1)->rescaleValueAxis(true,true);
    //}

    // time3
    ui->graphHerbPro->addGraph();
    ui->graphHerbPro->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphHerbPro->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbPro->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbPro->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbPro->graph(2)->addData(j,averageHerbTime3[j]);
        }
        ui->graphHerbPro->graph(2)->rescaleKeyAxis(true);
        ui->graphHerbPro->graph(2)->rescaleValueAxis(true,true);
    //}

    ui->graphHerbProFit->addGraph();
    ui->graphHerbProFit->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphHerbProFit->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphHerbProFit->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphHerbProFit->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphHerbProFit->graph(2)->addData(j,averageHerbFitTime3[j]);
        }
        ui->graphHerbProFit->graph(2)->rescaleKeyAxis(true);
        ui->graphHerbProFit->graph(2)->rescaleValueAxis(true,true);
    //}

    // CARNIVORES

    // time1
    ui->graphCarnPro->addGraph();
    ui->graphCarnPro->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphCarnPro->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnPro->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnPro->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnPro->graph(0)->addData(j,averageCarnTime1[j]);
        }
        ui->graphCarnPro->graph(0)->rescaleKeyAxis(false);
        ui->graphCarnPro->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphCarnProFit->addGraph();
    ui->graphCarnProFit->graph(0)->setPen(QPen(QColor(255,0,0,255)/*,2*/));
    ui->graphCarnProFit->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnProFit->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnProFit->graph(0)->setName(QString::number(TIME_1) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnProFit->graph(0)->addData(j,averageCarnFitTime1[j]);
        }
        ui->graphCarnProFit->graph(0)->rescaleKeyAxis(false);
        ui->graphCarnProFit->graph(0)->rescaleValueAxis(false,true);
    //}

    // time2
    ui->graphCarnPro->addGraph();
    ui->graphCarnPro->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphCarnPro->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnPro->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnPro->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnPro->graph(1)->addData(j,averageCarnTime2[j]);
        }
        ui->graphCarnPro->graph(1)->rescaleKeyAxis(true);
        ui->graphCarnPro->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphCarnProFit->addGraph();
    ui->graphCarnProFit->graph(1)->setPen(QPen(QColor(0,255,0,255)/*,2*/));
    ui->graphCarnProFit->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnProFit->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnProFit->graph(1)->setName(QString::number(TIME_2) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnProFit->graph(1)->addData(j,averageCarnFitTime2[j]);
        }
        ui->graphCarnProFit->graph(1)->rescaleKeyAxis(true);
        ui->graphCarnProFit->graph(1)->rescaleValueAxis(true,true);
    //}

    // time3
    ui->graphCarnPro->addGraph();
    ui->graphCarnPro->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphCarnPro->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnPro->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnPro->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnPro->graph(2)->addData(j,averageCarnTime3[j]);
        }
        ui->graphCarnPro->graph(2)->rescaleKeyAxis(true);
        ui->graphCarnPro->graph(2)->rescaleValueAxis(true,true);
    //}

    ui->graphCarnProFit->addGraph();
    ui->graphCarnProFit->graph(2)->setPen(QPen(QColor(0,0,255,255)/*,2*/));
    ui->graphCarnProFit->graph(2)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphCarnProFit->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphCarnProFit->graph(2)->setName(QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphCarnProFit->graph(2)->addData(j,averageCarnFitTime3[j]);
        }
        ui->graphCarnProFit->graph(2)->rescaleKeyAxis(true);
        ui->graphCarnProFit->graph(2)->rescaleValueAxis(true,true);
    //}

    //------------------------- COMPARISON -------------------------//

    ui->graphBoth->addGraph();
    ui->graphBoth->graph(0)->setPen(QPen(QColor(255,0,0,255)));
    ui->graphBoth->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphBoth->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphBoth->graph(0)->setName("Carnivores - " + QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphBoth->graph(0)->addData(j,comparison_carn_scale*averageCarnTime3[j]);
        }
        ui->graphBoth->graph(0)->rescaleKeyAxis(false);
        ui->graphBoth->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphBoth->addGraph();
    ui->graphBoth->graph(1)->setPen(QPen(QColor(0,0,255,255)));
    ui->graphBoth->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphBoth->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphBoth->graph(1)->setName("Herbivores - " + QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphBoth->graph(1)->addData(j,averageHerbTime3[j]);
        }
        ui->graphBoth->graph(1)->rescaleKeyAxis(true);
        ui->graphBoth->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphHerbPro->replot();
    ui->graphCarnPro->replot();
    ui->graphHerbProFit->replot();
    ui->graphCarnProFit->replot();
    ui->graphBoth->replot();
}

void Widget::update_comparison_plot()
{

    ui->graphBoth->clearGraphs();

    int j, g, h, c;
    g = ui->editGen->text().toInt();
    h = ui->editHerb->text().toInt();
    c = ui->editCarn->text().toInt();

    ui->graphBoth->yAxis->setTickLabels(true);
    ui->graphBoth->xAxis->setTickLabels(true);
    ui->graphBoth->yAxis->setLabel("Mean energy value");
    ui->graphBoth->xAxis->setLabel("Generation");
    ui->graphBoth->legend->setVisible(true);
    ui->graphBoth->setFont(QFont("Helvetica",9));
    ui->graphBoth->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    //------------------------- COMPARISON -------------------------//

    ui->graphBoth->addGraph();
    ui->graphBoth->graph(0)->setPen(QPen(QColor(255,0,0,255)));
    ui->graphBoth->graph(0)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphBoth->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphBoth->graph(0)->setName("Carnivores - " + QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphBoth->graph(0)->addData(j,comparison_carn_scale*averageCarnTime3[j]);
        }
        ui->graphBoth->graph(0)->rescaleKeyAxis(false);
        ui->graphBoth->graph(0)->rescaleValueAxis(false,true);
    //}

    ui->graphBoth->addGraph();
    ui->graphBoth->graph(1)->setPen(QPen(QColor(0,0,255,255)));
    ui->graphBoth->graph(1)->setLineStyle(QCPGraph::LineStyle(QCPGraph::lsLine));
    ui->graphBoth->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->graphBoth->graph(1)->setName("Herbivores - " + QString::number(TIME_3) + " generation interval");

    //if(b_herbFit == true){
        for(j=time_begin; j<(time_end+1); j++){
            ui->graphBoth->graph(1)->addData(j,averageHerbTime3[j]);
        }
        ui->graphBoth->graph(1)->rescaleKeyAxis(true);
        ui->graphBoth->graph(1)->rescaleValueAxis(true,true);
    //}

    ui->graphBoth->replot();
}




void Widget::on_herbDisp_clicked(bool checked)
{
    // true -> clicked
    if (checked == true){
        ui->herbDisp->setText("Invisible");
        b_herbDisp = false;
    }
    else{
        ui->herbDisp->setText("Visible");
        b_herbDisp = true;
    }
    updatePlot();
}

void Widget::on_herbMean_clicked(bool checked)
{
    if (checked == true){
        ui->herbMean->setText("Invisible");
        b_herbMean = false;
    }
    else{
        ui->herbMean->setText("Visible");
        b_herbMean = true;
    }
    updatePlot();
}

void Widget::on_herbFit_clicked(bool checked)
{
    if (checked == true){
        ui->herbFit->setText("Invisible");
        b_herbFit = false;
    }
    else{
        ui->herbFit->setText("Visible");
        b_herbFit = true;
    }
    updatePlot();
}

void Widget::on_carnDisp_clicked(bool checked)
{
    if (checked == true){
        ui->carnDisp->setText("Invisible");
        b_carnDisp = false;
    }
    else{
        ui->carnDisp->setText("Visible");
        b_carnDisp = true;
    }
    updatePlot();
}

void Widget::on_carnMean_clicked(bool checked)
{
    if (checked == true){
        ui->carnMean->setText("Invisible");
        b_carnMean = false;
    }
    else{
        ui->carnMean->setText("Visible");
        b_carnMean = true;
    }
    updatePlot();
}

void Widget::on_carnFit_clicked(bool checked)
{
    if (checked == true){
        ui->carnFit->setText("Invisible");
        b_carnFit = false;
    }
    else{
        ui->carnFit->setText("Visible");
        b_carnFit = true;
    }
    updatePlot();
}

void Widget::on_updateCheckBox_clicked(bool checked)
{
    // clicked -> true
    if(checked == true)
        updateData = true;
    else
        updateData = false;

}

void Widget::timeOutSlot(){

    if(updateData == true){

        energyHerb.resize(0);
        healthHerb.resize(0);
        hurtHerb.resize(0);
        energyCarn.resize(0);
        averageHerb.resize(0);
        averageHealth.resize(0);
        averageHurt.resize(0);
        averageCarn.resize(0);
        averageCarnTime1.resize(0);
        averageCarnTime2.resize(0);
        averageCarnTime3.resize(0);
        averageHerbTime1.resize(0);
        averageHerbTime2.resize(0);
        averageHerbTime3.resize(0);
        averageCarnFitTime1.resize(0);
        averageCarnFitTime2.resize(0);
        averageCarnFitTime3.resize(0);
        averageHerbFitTime1.resize(0);
        averageHerbFitTime2.resize(0);
        averageHerbFitTime3.resize(0);

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);


        //----- Read file header -----//
        QTextStream in(&file);

        QString line;
        QStringList fields;

        qDebug()<<"...";

        fields = fileName.split("/");
        ui->editFileName->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editHerb->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editCarn->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editPlants->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editGen->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editHealth->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editHurt->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editFrames->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editHerHerb->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editHerCarn->setText(fields.back());
        line = in.readLine();
        fields = line.split(" ");
        ui->editEvaluate->setText(fields.back());



        //-------- Get graph values ------//
        line = in.readLine(); // empty line
        int i, j, k, g, h, c;
        g = ui->editGen->text().toInt();
        generations = g;
        h = ui->editHerb->text().toInt();
        c = ui->editCarn->text().toInt();

        energyHerb.resize(g+1);
        healthHerb.resize(g+1);
        hurtHerb.resize(g+1);
        energyCarn.resize(g+1);

        averageHerb.resize(g+1);
        averageHealth.resize(g+1);
        averageHurt.resize(g+1);
        averageCarn.resize(g+1);

        averageCarnTime1.resize(g+1);
        averageCarnTime2.resize(g+1);
        averageCarnTime3.resize(g+1);

        averageHerbTime1.resize(g+1);
        averageHerbTime2.resize(g+1);
        averageHerbTime3.resize(g+1);

        averageCarnFitTime1.resize(g+1);
        averageCarnFitTime2.resize(g+1);
        averageCarnFitTime3.resize(g+1);

        averageHerbFitTime1.resize(g+1);
        averageHerbFitTime2.resize(g+1);
        averageHerbFitTime3.resize(g+1);


        for(i=0; i<(g+1); i++){
            energyHerb[i].resize(h);
            healthHerb[i].resize(h);
            hurtHerb[i].resize(h);
            energyCarn[i].resize(c);

            averageHerb[i] = 0;
            averageHealth[i] = 0;
            averageHurt[i] = 0;
            averageCarn[i] = 0;

            line = in.readLine(); // generation header
            line = in.readLine(); // herbivores
            fields = line.split(" ");
            for(j=0; j<h; j++){
                energyHerb[i][j] = fields[j+1].toInt();
                averageHerb[i] += energyHerb[i][j];
                //printf("%d\n",energyHerb[i][j]);
            }
            averageHerb[i] = averageHerb[i]/h;
            //printf("%f ",averageHerb[i]);

            line = in.readLine(); // health
            fields = line.split(" ");
            for(j=0; j<h; j++){
                healthHerb[i][j] = fields[j+1].toInt();
                averageHealth[i] += healthHerb[i][j];
            }
            averageHealth[i] = averageHealth[i]/h;

            line = in.readLine(); // hurt
            fields = line.split(" ");
            for(j=0; j<h; j++){
                hurtHerb[i][j] = fields[j+1].toInt();
                averageHurt[i] += hurtHerb[i][j];
            }
            averageHurt[i] = averageHurt[i]/h;

            line = in.readLine(); // carnivores
            fields = line.split(" ");
            for(j=0; j<c; j++){
                energyCarn[i][j] = fields[j+1].toInt();
                averageCarn[i] += energyCarn[i][j];
                //printf("%d\n",energyCarn[i][j]);
            }
            averageCarn[i] = averageCarn[i]/h;

            // Mean value of mean and fittest energy over interval TIME_1

            if(i >= (TIME_1 - 1)){
                averageHerbTime1[i] = 0;
                averageCarnTime1[i] = 0;
                averageHerbFitTime1[i] = 0;
                averageCarnFitTime1[i] = 0;

                for(k = (i - TIME_1 + 1); k<=i; k++){
                    averageHerbTime1[i] = averageHerbTime1[i] + averageHerb[k];
                    averageCarnTime1[i] = averageCarnTime1[i] + averageCarn[k];

                    averageHerbFitTime1[i] = averageHerbFitTime1[i] + energyHerb[k][0];
                    averageCarnFitTime1[i] = averageCarnFitTime1[i] + energyCarn[k][0];
                }
                averageHerbTime1[i] = averageHerbTime1[i]/TIME_1;
                averageCarnTime1[i] = averageCarnTime1[i]/TIME_1;
                averageHerbFitTime1[i] = averageHerbFitTime1[i]/TIME_1;
                averageCarnFitTime1[i] = averageCarnFitTime1[i]/TIME_1;
            }
            else{
                averageHerbTime1[i] = 0;
                averageCarnTime1[i] = 0;
                averageHerbFitTime1[i] = 0;
                averageCarnFitTime1[i] = 0;
            }

            // Mean value over interval TIME_2

            if(i >= (TIME_2 - 1)){
                averageHerbTime2[i] = 0;
                averageCarnTime2[i] = 0;
                averageHerbFitTime2[i] = 0;
                averageCarnFitTime2[i] = 0;

                for(k = (i - TIME_2 + 1); k<=i; k++){
                    averageHerbTime2[i] = averageHerbTime2[i] + averageHerb[k];
                    averageCarnTime2[i] = averageCarnTime2[i] + averageCarn[k];

                    averageHerbFitTime2[i] = averageHerbFitTime2[i] + energyHerb[k][0];
                    averageCarnFitTime2[i] = averageCarnFitTime2[i] + energyCarn[k][0];
                }
                averageHerbTime2[i] = averageHerbTime2[i]/TIME_2;
                averageCarnTime2[i] = averageCarnTime2[i]/TIME_2;
                averageHerbFitTime2[i] = averageHerbFitTime2[i]/TIME_2;
                averageCarnFitTime2[i] = averageCarnFitTime2[i]/TIME_2;
            }
            else{
                averageHerbTime2[i] = 0;
                averageCarnTime2[i] = 0;
                averageHerbFitTime2[i] = 0;
                averageCarnFitTime2[i] = 0;
            }

            // Mean value over interval TIME_3

            if(i >= (TIME_3 - 1)){
                averageHerbTime3[i] = 0;
                averageCarnTime3[i] = 0;
                averageHerbFitTime3[i] = 0;
                averageCarnFitTime3[i] = 0;

                for(k = (i - TIME_3 + 1); k<=i; k++){
                    averageHerbTime3[i] = averageHerbTime3[i] + averageHerb[k];
                    averageCarnTime3[i] = averageCarnTime3[i] + averageCarn[k];

                    averageHerbFitTime3[i] = averageHerbFitTime3[i] + energyHerb[k][0];
                    averageCarnFitTime3[i] = averageCarnFitTime3[i] + energyCarn[k][0];
                }
                averageHerbTime3[i] = averageHerbTime3[i]/TIME_3;
                averageCarnTime3[i] = averageCarnTime3[i]/TIME_3;
                averageHerbFitTime3[i] = averageHerbFitTime3[i]/TIME_3;
                averageCarnFitTime3[i] = averageCarnFitTime3[i]/TIME_3;
            }
            else{
                averageHerbTime3[i] = 0;
                averageCarnTime3[i] = 0;
                averageHerbFitTime3[i] = 0;
                averageCarnFitTime3[i] = 0;
            }

            if(in.atEnd()==true){
                g = i;
                generations = g;
                ui->editGen->setText(QString::number(g));
                //printf("%d\n",g);
            }

        }
        ui->interval1SpinBox->setMaximum(generations);
        ui->interval2SpinBox->setMaximum(generations);
        ui->interval3SpinBox->setMaximum(generations);
        ui->timeBegin->setMaximum(generations);
        ui->timeEnd->setMaximum(generations);

        ui->interval1SpinBox->setValue(TIME_1);
        ui->interval2SpinBox->setValue(TIME_2);
        ui->interval3SpinBox->setValue(TIME_3);

        ui->timeEnd->setValue(generations);
        time_end = generations;

        file.close();


        updatePlot();
    }

}


void Widget::on_interval1SpinBox_valueChanged(int arg1)
{
    TIME_1 = arg1;

    averageCarnTime1.resize(0);
    averageHerbTime1.resize(0);
    averageCarnFitTime1.resize(0);
    averageHerbFitTime1.resize(0);

    averageCarnTime1.resize(generations+1);
    averageHerbTime1.resize(generations+1);
    averageCarnFitTime1.resize(generations+1);
    averageHerbFitTime1.resize(generations+1);


    int i, k;
    for(i=0; i<(generations+1); i++){
        if(i >= (TIME_1 - 1)){
            averageHerbTime1[i] = 0;
            averageCarnTime1[i] = 0;
            averageHerbFitTime1[i] = 0;
            averageCarnFitTime1[i] = 0;

            for(k = (i - TIME_1 + 1); k<=i; k++){
                averageHerbTime1[i] = averageHerbTime1[i] + averageHerb[k];
                averageCarnTime1[i] = averageCarnTime1[i] + averageCarn[k];

                averageHerbFitTime1[i] = averageHerbFitTime1[i] + energyHerb[k][0];
                averageCarnFitTime1[i] = averageCarnFitTime1[i] + energyCarn[k][0];
            }
            averageHerbTime1[i] = averageHerbTime1[i]/TIME_1;
            averageCarnTime1[i] = averageCarnTime1[i]/TIME_1;
            averageHerbFitTime1[i] = averageHerbFitTime1[i]/TIME_1;
            averageCarnFitTime1[i] = averageCarnFitTime1[i]/TIME_1;
        }
        else{
            averageHerbTime1[i] = 0;
            averageCarnTime1[i] = 0;
            averageHerbFitTime1[i] = 0;
            averageCarnFitTime1[i] = 0;
        }
    }
    updatePlot();
}

void Widget::on_interval2SpinBox_valueChanged(int arg1)
{
    TIME_2 = arg1;

    averageCarnTime2.resize(0);
    averageHerbTime2.resize(0);
    averageCarnFitTime2.resize(0);
    averageHerbFitTime2.resize(0);

    averageCarnTime2.resize(generations+1);
    averageHerbTime2.resize(generations+1);
    averageCarnFitTime2.resize(generations+1);
    averageHerbFitTime2.resize(generations+1);

    int i, k;
    for(i=0; i<(generations+1); i++){
        if(i >= (TIME_2 - 1)){
            averageHerbTime2[i] = 0;
            averageCarnTime2[i] = 0;
            averageHerbFitTime2[i] = 0;
            averageCarnFitTime2[i] = 0;

            for(k = (i - TIME_2 + 1); k<=i; k++){
                averageHerbTime2[i] = averageHerbTime2[i] + averageHerb[k];
                averageCarnTime2[i] = averageCarnTime2[i] + averageCarn[k];

                averageHerbFitTime2[i] = averageHerbFitTime2[i] + energyHerb[k][0];
                averageCarnFitTime2[i] = averageCarnFitTime2[i] + energyCarn[k][0];
            }
            averageHerbTime2[i] = averageHerbTime2[i]/TIME_2;
            averageCarnTime2[i] = averageCarnTime2[i]/TIME_2;
            averageHerbFitTime2[i] = averageHerbFitTime2[i]/TIME_2;
            averageCarnFitTime2[i] = averageCarnFitTime2[i]/TIME_2;
        }
        else{
            averageHerbTime2[i] = 0;
            averageCarnTime2[i] = 0;
            averageHerbFitTime2[i] = 0;
            averageCarnFitTime2[i] = 0;
        }
    }
    updatePlot();
}

void Widget::on_interval3SpinBox_valueChanged(int arg1)
{
    TIME_3 = arg1;

    averageCarnTime3.resize(0);
    averageHerbTime3.resize(0);
    averageCarnFitTime3.resize(0);
    averageHerbFitTime3.resize(0);

    averageCarnTime3.resize(generations+1);
    averageHerbTime3.resize(generations+1);
    averageCarnFitTime3.resize(generations+1);
    averageHerbFitTime3.resize(generations+1);

    int i, k;
    for(i=0; i<(generations+1); i++){
        if(i >= (TIME_3 - 1)){
            averageHerbTime3[i] = 0;
            averageCarnTime3[i] = 0;
            averageHerbFitTime3[i] = 0;
            averageCarnFitTime3[i] = 0;

            for(k = (i - TIME_3 + 1); k<=i; k++){
                averageHerbTime3[i] = averageHerbTime3[i] + averageHerb[k];
                averageCarnTime3[i] = averageCarnTime3[i] + averageCarn[k];

                averageHerbFitTime3[i] = averageHerbFitTime3[i] + energyHerb[k][0];
                averageCarnFitTime3[i] = averageCarnFitTime3[i] + energyCarn[k][0];
            }
            averageHerbTime3[i] = averageHerbTime3[i]/TIME_3;
            averageCarnTime3[i] = averageCarnTime3[i]/TIME_3;
            averageHerbFitTime3[i] = averageHerbFitTime3[i]/TIME_3;
            averageCarnFitTime3[i] = averageCarnFitTime3[i]/TIME_3;
        }
        else{
            averageHerbTime3[i] = 0;
            averageCarnTime3[i] = 0;
            averageHerbFitTime3[i] = 0;
            averageCarnFitTime3[i] = 0;
        }
    }
    updatePlot();
}



void Widget::on_carnScaleSpinBox_valueChanged(int arg1)
{
    comparison_carn_scale = arg1;
    update_comparison_plot();
}

void Widget::on_timeBegin_valueChanged(int arg1)
{
    time_begin = arg1;
    update_processed_comparison_plot();
}

void Widget::on_timeEnd_valueChanged(int arg1)
{
    time_end = arg1;
    update_processed_comparison_plot();
}
