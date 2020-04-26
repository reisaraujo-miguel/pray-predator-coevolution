#include "simulationmanager.h"
#include "ui_simulationmanager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <utility>

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTimer>
#include <QString>
#include <QtMath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// IF loop, reshuffle positions

SimulationManager::SimulationManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SimulationManager)
{
    ui->setupUi(this);

    herbivores.resize(0);
    carnivores.resize(0);

    herb_sim.resize(0);
    carn_sim.resize(0);
    plant_sim.resize(0);

    loop = true;
    do_simulate = false;

    environment = "Simulation";

    timeOutCount = 0;

    X=600;
    Y=400;
    RADIUS = 5;

    matrix = (int**)calloc(Y,sizeof(int*));
    int i;
    for(i=0; i<Y; i++){
        matrix[i] = (int*)calloc(X,sizeof(int));
    }

    DataTimer = new QTimer(this);
    connect(DataTimer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    DataTimer->start(50); // timeout() at 10 milisseconds interval
}

SimulationManager::~SimulationManager()
{
    delete ui;
}

void SimulationManager::on_importButton_clicked()
{

    QString dataDir;

    //----- Find data directory -----//
    QString currDir = qApp->applicationDirPath(); // the pointer qApp refers to the application
    QStringList pieces = currDir.split( "/" ); // spliting directory path, the "/" are lost

    for(int i=0;i<pieces.length()-1;i++){ // the last folder is ignored
        dataDir+=pieces.value(i);
        dataDir+="/";
    }
    dataDir+="evolutionaryAlgorithm/data/";

    //----- Get file -----//
   fileName = QFileDialog::getOpenFileName(this, "Select the data file", dataDir, "Text Files (*txt)");

    if(fileName.size()==0) // if the user presses cancel, getOpenFileName returns a null string
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }

    herbivores.resize(0);
    carnivores.resize(0);

    //----- Read file header -----//
    QTextStream in(&file);

    QString line;
    QStringList fields;

    QString textFileName;

    qDebug()<<"...";

    // needs to open herbivore and carnivore file

    fields = fileName.split("/");
    ui->editFileName->setText(fields.back());
    textFileName = fields.back();

    line = in.readLine();
    fields = line.split(" ");
    ui->editHerb->setText(fields.back());
    herb_pop = fields.back().toInt();

    line = in.readLine();
    fields = line.split(" ");
    ui->editCarn->setText(fields.back());
    carn_pop = fields.back().toInt();

    line = in.readLine();
    fields = line.split(" ");
    ui->editPlants->setText(fields.back());
    plants_pop = fields.back().toInt();

    line = in.readLine();
    fields = line.split(" ");
    ui->editGen->setText(fields.back());
    gen = 1+fields.back().toInt();

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
    //ui->editEvaluate->setText(fields.back());

    fields = textFileName.split("_");
    if(fields[0] == "wanderers"){

        // get wanderers data
        readWanderers(&in);
        file.close();

        // open carnivores file and get data
        openCarnivores();

    }else{  // carnivores

        // get carnivores data
        readCarnivores(&in);
        file.close();

        // open wanderers file and get data
        openWanderers();
    }

    ui->chooseGen->setMinimum(0);
    ui->chooseGen->setMaximum(gen-1);
    ui->chooseHerb->setMinimum(0);
    ui->chooseHerb->setMaximum(herb_pop-1);
    ui->chooseHerb->setMinimum(0);
    ui->chooseCarn->setMaximum(carn_pop-1);

    ui->chooseGen->setValue(gen-1);
    ui->chooseHerb->setValue(0);
    ui->chooseCarn->setValue(0);

    ui->frameRate->setValue(50);

    //on_chooseHerb_valueChanged(0);
    //on_chooseCarn_valueChanged(0);
}

void SimulationManager::readWanderers(QTextStream* in){

    QString line;
    QStringList fields;
    int i,j;

    line = (*in).readLine();    // empty line
    line = (*in).readLine();    // description
    line = (*in).readLine();    // empty line

    herbivores.resize(gen);

    for(i=0; i<gen; i++){

        if((*in).atEnd()==true){
            gen = i;
            ui->editGen->setText(QString::number(gen));
        }else{

            line = (*in).readLine();    // generation number
            herbivores[i].resize(herb_pop);

            for(j=0; j<herb_pop; j++){

                line = (*in).readLine();
                fields = line.split(" ");


                herbivores[i][j].plant_const = fields[1].toInt();
                herbivores[i][j].plant_weight = fields[2].toInt();
                herbivores[i][j].herb_const = fields[3].toInt();
                herbivores[i][j].herb_weight = fields[4].toInt();
                herbivores[i][j].carn_const = fields[5].toInt();
                herbivores[i][j].carn_weight = fields[6].toInt();
                herbivores[i][j].search_height_limit = fields[7].toInt();
                herbivores[i][j].search_height = fields[8].toInt();
                herbivores[i][j].speed = fields[9].toInt();
                herbivores[i][j].health = fields[10].toInt();
                herbivores[i][j].hurt = fields[11].toInt();
                herbivores[i][j].energy = fields[13].toInt();
            }
            line = (*in).readLine();    // empty line
        }
    }
}

void SimulationManager::readCarnivores(QTextStream* in){
    QString line;
    QStringList fields;
    int i,j;

    line = (*in).readLine();    // empty line
    line = (*in).readLine();    // description
    line = (*in).readLine();    // empty line

    carnivores.resize(gen);

    for(i=0; i<gen; i++){

        if((*in).atEnd()==true){
            gen = i;
            ui->editGen->setText(QString::number(gen));
        }else{

            line = (*in).readLine();    // generation number
            carnivores[i].resize(carn_pop);

            for(j=0; j<carn_pop; j++){

                line = (*in).readLine();
                fields = line.split(" ");

                carnivores[i][j].plant_const = fields[1].toInt();
                carnivores[i][j].plant_weight = fields[2].toInt();
                carnivores[i][j].herb_const = fields[3].toInt();
                carnivores[i][j].herb_weight = fields[4].toInt();
                carnivores[i][j].carn_const = fields[5].toInt();
                carnivores[i][j].carn_weight = fields[6].toInt();
                carnivores[i][j].search_height_limit = fields[7].toInt();
                carnivores[i][j].search_height = fields[8].toInt();
                carnivores[i][j].speed = fields[9].toInt();
                carnivores[i][j].energy = fields[11].toInt();
            }
            line = (*in).readLine();    // empty line
        }
    }
}

void SimulationManager::openCarnivores(){

    //----- Get file -----//
    int i;
    QStringList dir = fileName.split("/");
    QStringList txt = dir.back().split("_");
    QString newFileName;
    newFileName.clear();

    for(i=0;i<dir.length()-1;i++){ // .txt file ignored
        newFileName+=dir.value(i);
        newFileName+="/";
    }
    newFileName+="carnivores";
    for(i=1;i<txt.length(); i++){  // wanderers ignored
        newFileName+="_";
        newFileName+=txt.value(i);
    }

    //printf("FILE: %s\n",newFileName.toStdString().c_str());

    QFile file(newFileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }


    //----- Read file header -----//
    QTextStream in(&file);

    QString line;
    QStringList fields;

    QString textFileName;

    qDebug()<<"...";


    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHerb->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editCarn->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editPlants->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editGen->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHealth->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHurt->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editFrames->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHerHerb->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHerCarn->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editEvaluate->setText(fields.back());

    readCarnivores(&in);

    file.close();
}

void SimulationManager::openWanderers(){

    //----- Get file -----//
    int i;
    QStringList dir = fileName.split("/");
    QStringList txt = dir.back().split("_");
    QString newFileName;
    newFileName.clear();

    for(i=0;i<dir.length()-1;i++){ // .txt file ignored
        newFileName+=dir.value(i);
        newFileName+="/";
    }
    newFileName+="wanderers";
    for(i=1;i<txt.length(); i++){  // wanderers ignored
        newFileName+="_";
        newFileName+=txt.value(i);
    }

    //printf("FILE: %s\n",newFileName.toStdString().c_str());

    QFile file(newFileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }


    //----- Read file header -----//
    QTextStream in(&file);

    QString line;
    QStringList fields;

    QString textFileName;

    qDebug()<<"...";


    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHerb->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editCarn->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editPlants->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editGen->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHealth->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHurt->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editFrames->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHerHerb->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editHerCarn->setText(fields.back());
    line = in.readLine();
    //fields = line.split(" ");
    //ui->editEvaluate->setText(fields.back());

    readWanderers(&in);

    file.close();
}

void SimulationManager::on_chooseHerb_valueChanged(int i)
{
    int g = ui->chooseGen->text().toInt();

    if(g >= 0){
        ui->herbPlantConst->setText(QString::number(herbivores[g][i].plant_const));
        ui->herbHerbConst->setText(QString::number(herbivores[g][i].herb_const));
        ui->herbCarnConst->setText(QString::number(herbivores[g][i].carn_const));

        ui->herbPlantWeight->setText(QString::number(herbivores[g][i].plant_weight));
        ui->herbHerbWeight->setText(QString::number(herbivores[g][i].herb_weight));
        ui->herbCarnWeight->setText(QString::number(herbivores[g][i].carn_weight));

        if(herbivores[g][i].search_height_limit == 1)
            ui->herbHeight->setText(QString::number(herbivores[g][i].search_height));
        else
            ui->herbHeight->setText("None");

        ui->herbSpeed->setText(QString::number(herbivores[g][i].speed));

        ui->herbHealth->setText(QString::number(herbivores[g][i].health));
        ui->herbHurt->setText(QString::number(herbivores[g][i].hurt));
        ui->herbEnergy->setText(QString::number(herbivores[g][i].energy));
    }

}

void SimulationManager::on_chooseCarn_valueChanged(int i)
{
    int g = ui->chooseGen->text().toInt();

    if(g >= 0){
        ui->carnPlantConst->setText(QString::number(carnivores[g][i].plant_const));
        ui->carnHerbConst->setText(QString::number(carnivores[g][i].herb_const));
        ui->carnCarnConst->setText(QString::number(carnivores[g][i].carn_const));

        ui->carnPlantWeight->setText(QString::number(carnivores[g][i].plant_weight));
        ui->carnHerbWeight->setText(QString::number(carnivores[g][i].herb_weight));
        ui->carnCarnWeight->setText(QString::number(carnivores[g][i].carn_weight));

        if(carnivores[g][i].search_height_limit == 1)
            ui->carnHeight->setText(QString::number(carnivores[g][i].search_height));
        else
            ui->carnHeight->setText("None");

        ui->carnSpeed->setText(QString::number(carnivores[g][i].speed));

        ui->carnEnergy->setText(QString::number(carnivores[g][i].energy));
    }
}



void SimulationManager::on_chooseGen_valueChanged(int arg1)
{
    int h = ui->chooseHerb->value();
    int c = ui->chooseCarn->value();

    if(h != 0)
        ui->chooseHerb->setValue(0);
    else
        on_chooseHerb_valueChanged(0);

    if(c != 0)
        ui->chooseCarn->setValue(0);
    else
        on_chooseCarn_valueChanged(0);

    if(do_simulate == true){
        initialize_populations();
    }
}



void SimulationManager::on_progress_clicked(bool checked)
{
    if(checked == true){
        loop = false;
        ui->loop->setChecked(false);
    }else{
        loop = true;
        ui->loop->setChecked(true);
    }
}

void SimulationManager::on_loop_clicked(bool checked)
{
    if(checked == true){
        loop = true;
        ui->progress->setChecked(false);
    }else{
        loop = false;
        ui->progress->setChecked(true);
    }
}

void SimulationManager::timeOutSlot(){

    if(do_simulate == true){
        timeOutCount++;
        //printf("%d frames/gen: %d\n",timeOutCount,gen_interval);

        if(timeOutCount >= gen_interval){
            if(loop == false){
                if((sim_gen+1)<gen){
                    ui->chooseGen->setValue(sim_gen+1);
                }
                else{
                    simulate();
                }
            }
            else{   // loop == true
                // reposition individuals
                initialize_populations();
            }
            timeOutCount = 0;
        }
        else{
            simulate();
        }
    }
}

void SimulationManager::on_simulate_clicked(bool checked)
{
    if(checked == true){
        do_simulate = true;
        namedWindow(environment, WINDOW_AUTOSIZE );
        moveWindow(environment, 800, 0);

        initialize_populations();

    }else{
        do_simulate = false;
        destroyWindow(environment);
    }
}

Mat SimulationManager::print_img(){

    //Vec3b red = Vec3b(0,0,255);
    Vec3b green = Vec3b(0,255,0);
    Vec3b blue = Vec3b(255,0,0);
    Vec3b pink = Vec3b(77,0,230);
    //Vec3b black = Vec3b(0,0,0);
    //Vec3b orange = Vec3b(0,108,238);
    //Vec3b violet = Vec3b(200,0,119);
    //Vec3b yellow = Vec3b(0,184,196);

    Mat image(Y, X, CV_8UC3, Scalar(0,0,0));
    memset(image.data, 255, X*Y*3*sizeof(char)); // white

    //char label[30];
    //sprintf(label, "%d", sim_gen); // generation
    //putText(image, label, Point(15,20), FONT_HERSHEY_SIMPLEX, 0.6, CV_RGB(0,0,0), 1);

    //char label[10];

    int i, x, y;
    for(i=0; i<herb_sim.size(); i++){
        x = herb_sim[i].x;
        y = herb_sim[i].y;
        if(x >= 0 && x < X && y >= 0 && y < Y){
            circle(image, Point(x,y), RADIUS, blue, -1,  LINE_8 );
            //sprintf(label,"%d",i);
            //putText(image, label, Point(x,y), FONT_HERSHEY_SIMPLEX, 0.6, CV_RGB(0,0,0), 1);
            line (image, Point(x+(qCos(herb_sim[i].angle)*RADIUS),y+(qSin(herb_sim[i].angle)*RADIUS)), Point(x+(qCos(herb_sim[i].angle)*3*RADIUS),y+(qSin(herb_sim[i].angle)*3*RADIUS)), Scalar(0,0,0), 1, LINE_8);
        }
    }
    for(i=0; i<carn_sim.size(); i++){
        x = carn_sim[i].x;
        y = carn_sim[i].y;
        if(x >= 0 && x < X && y >= 0 && y < Y){
            circle(image, Point(x,y), RADIUS, pink, -1,  LINE_8 );
            //sprintf(label,"%d",i);
            //putText(image, label, Point(x,y), FONT_HERSHEY_SIMPLEX, 0.6, CV_RGB(0,0,0), 1);
            line (image, Point(x+(qCos(carn_sim[i].angle)*RADIUS),y+(qSin(carn_sim[i].angle)*RADIUS)), Point(x+(qCos(carn_sim[i].angle)*3*RADIUS),y+(qSin(carn_sim[i].angle)*3*RADIUS)), Scalar(0,0,0), 1, LINE_8);
        }
    }
    for(i=0; i<plant_sim.size(); i++){
        x = plant_sim[i].x;
        y = plant_sim[i].y;
        if(x >= 0 && x < X && y >= 0 && y < Y){
            circle(image, Point(x,y), RADIUS, green, -1,  LINE_8 );
            line (image, Point(x+(qCos(plant_sim[i].angle)*RADIUS),y+(qSin(plant_sim[i].angle)*RADIUS)), Point(x+(qCos(plant_sim[i].angle)*3*RADIUS),y+(qSin(plant_sim[i].angle)*3*RADIUS)), Scalar(0,0,0), 1, LINE_8);
        }
    }

    //int j;
    //for(i=0;i<X;i++){
    //    for(j=0;j<Y;j++){
    //        if(matrix[j][i] == 1){
    //            circle(image, Point(i,j), 2, blue, -1,  LINE_8 );
    //        }
    //        else if(matrix[j][i] == 2){
    //            circle(image, Point(i,j), 2, pink, -1,  LINE_8 );
    //        }
    //        else if(matrix[j][i] == 3){
    //            circle(image, Point(i,j), 2, green, -1,  LINE_8 );
    //        }
    //    }
    //}
    return image;
}

void SimulationManager::on_frameRate_valueChanged(int arg1)
{
    gen_interval = arg1;
}
