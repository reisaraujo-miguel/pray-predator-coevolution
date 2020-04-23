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


// FOR NEXT VERSION: eliminate K in read wanderers and carnivores!!
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
    DataTimer->start(400); // timeout() at 5 milisseconds interval
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
    int i,j,k;

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
                k = 0;

                line = (*in).readLine();
                fields = line.split(" ");

                if(fields[1].toInt()==0 && fields[2].toInt()<10){
                    k++;
                }
                herbivores[i][j].plant_const = fields[1+k].toInt();

                if(fields[2+k].toInt()==0 && fields[3+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].plant_weight = fields[2+k].toInt();

                if(fields[3+k].toInt()==0 && fields[4+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].herb_const = fields[3+k].toInt();

                if(fields[4+k].toInt()==0 && fields[5+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].herb_weight = fields[4+k].toInt();

                if(fields[5+k].toInt()==0 && fields[6+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].carn_const = fields[5+k].toInt();

                if(fields[6+k].toInt()==0 && fields[7+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].carn_weight = fields[6+k].toInt();

                if(fields[7+k].toInt()==0 && fields[8+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].search_height_limit = fields[7+k].toInt();

                if(fields[8+k].toInt()==0 && fields[9+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].search_height = fields[8+k].toInt();

                herbivores[i][j].speed = fields[9+k].toInt();
                herbivores[i][j].health = fields[10+k].toInt();

                if(fields[11+k].toInt()==0 && fields[12+k].toInt()<10){
                    k++;
                }
                herbivores[i][j].hurt = fields[11+k].toInt();
                herbivores[i][j].energy = fields[13+k].toInt();
            }
            line = (*in).readLine();    // empty line
        }
    }
}

void SimulationManager::readCarnivores(QTextStream* in){
    QString line;
    QStringList fields;
    int i,j,k;

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
                k = 0;

                line = (*in).readLine();
                fields = line.split(" ");

                if(fields[1].toInt()==0 && fields[2].toInt()<10){
                    k++;
                }
                carnivores[i][j].plant_const = fields[1+k].toInt();

                if(fields[2+k].toInt()==0 && fields[3+k].toInt()<10){
                    k++;
                }
                carnivores[i][j].plant_weight = fields[2+k].toInt();

                if(fields[3+k].toInt()==0 && fields[4+k].toInt()<10){
                    k++;
                }
                carnivores[i][j].herb_const = fields[3+k].toInt();

                if(fields[4+k].toInt()==0 && fields[5+k].toInt()<10){
                    k++;
                }
                carnivores[i][j].herb_weight = fields[4+k].toInt();

                if(fields[5+k].toInt()==0 && fields[6+k].toInt()<10){
                    k++;
                }
                carnivores[i][j].carn_const = fields[5+k].toInt();

                if(fields[6+k].toInt()==0 && fields[7+k].toInt()<10){
                    k++;
                }
                carnivores[i][j].carn_weight = fields[6+k].toInt();

                carnivores[i][j].search_height_limit = fields[7+k].toInt();
                carnivores[i][j].search_height = fields[8+k].toInt();

                if(fields[9+k].toInt()==0 && fields[10+k].toInt()<10){
                    k++;
                }
                carnivores[i][j].speed = fields[9+k].toInt();
                carnivores[i][j].energy = fields[11+k].toInt();
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
        printf("%d frames/gen: %d\n",timeOutCount,gen_interval);

        if(timeOutCount >= gen_interval){
            if(loop == false){
                if((sim_gen+1)<gen){
                    ui->chooseGen->setValue(sim_gen+1);
                }
                else{
                    simulate();
                }
            }
            else{
                //reposition individuals?
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

void SimulationManager::initialize_populations(){

    int i;

    for(i=0; i<herb_sim.size(); i++){
        matrix[herb_sim[i].y][herb_sim[i].x] = 0;
    }
    for(i=0; i<carn_sim.size(); i++){
        matrix[carn_sim[i].y][carn_sim[i].x] = 0;
    }
    for(i=0; i<plant_sim.size(); i++){
        matrix[plant_sim[i].y][plant_sim[i].x] = 0;
    }

    herb_sim.clear();
    carn_sim.clear();
    plant_sim.clear();

    herb_sim.resize(herb_pop);
    carn_sim.resize(carn_pop);
    plant_sim.resize(plants_pop);

    sim_gen = ui->chooseGen->value();


    for(i=0; i<herb_pop; i++){

        srand(time(0)+i);

        herb_sim[i].x = rand()%X;
        herb_sim[i].y = rand()%Y;

        while(check_disponibility(herb_sim[i].x, herb_sim[i].y) == (-1)){
            herb_sim[i].x = rand()%X;
            herb_sim[i].y = rand()%Y;
        }

        herb_sim[i].angle = (float)(rand()%628)/100;

        matrix[herb_sim[i].y][herb_sim[i].x] = 1;
    }

    for(i=0; i<carn_pop; i++){

        srand(time(0)+i);

        carn_sim[i].x = rand()%X;
        carn_sim[i].y = rand()%Y;

        while(check_disponibility(carn_sim[i].x, carn_sim[i].y) == (-1)){
            carn_sim[i].x = rand()%X;
            carn_sim[i].y = rand()%Y;
        }

        carn_sim[i].angle = (float)(rand()%628)/100;

        matrix[carn_sim[i].y][carn_sim[i].x] = 2;
    }

    for(i=0; i<plants_pop; i++){

        srand(time(0)+i);

        plant_sim[i].x = rand()%X;
        plant_sim[i].y = rand()%Y;

        while(check_disponibility(plant_sim[i].x, plant_sim[i].y) == (-1)){
            plant_sim[i].x = rand()%X;
            plant_sim[i].y = rand()%Y;
        }

        matrix[plant_sim[i].y][plant_sim[i].x] = 3;
    }

    Mat frame = print_img();
    imshow(environment, frame);

}

int SimulationManager::check_disponibility(int x, int y){
    if(matrix[y][x] != 0){
        return -1;
    }
    return 0;
}

void SimulationManager::simulate(){

    new_plants();

    /////////////////////////////// GENETICALLY DETERMINED ROTATION /////////////////////////////////////////
    // TIME IN SECONDS
    //time_t start, end;
    //start = time(NULL);

    // TIME IN MILISSECONDS
    // Taking too long! Around 0.35 seconds!
    // One call to BFS takes around 0.02 seconds! 0.02 * 15 = 0.3 (15 calls for 15 entities)
    // BFS is taking up most of the time!

    // struct timespec tstart={0,0}, tend={0,0};
    // clock_gettime(CLOCK_MONOTONIC, &tstart);



    int i, size;
    size = herb_sim.size();
    for(i=0; i<size; i++){
        genetic_rotation(herb_sim,herbivores,i);
    }

    size = carn_sim.size();
    for(i=0; i<size; i++){
        genetic_rotation(carn_sim,carnivores,i);
    }



    //end = time(NULL);
    //printf("%f\n",difftime(end,start));
    // clock_gettime(CLOCK_MONOTONIC, &tend);
    // printf("took %.5f seconds\n",
    //       ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
    //       ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));


    ///////////////////////////////////////// MOVE //////////////////////////////////////////////////////

    move_wanderers(herb_sim,herbivores);
    move_carnivores(carn_sim,carnivores);

    Mat frame = print_img();
    imshow(environment, frame);
}

void SimulationManager::new_plants(){


    int i;

    int size = plant_sim.size();
    //for(i=0; i<size; i++){
    //    matrix[pop[i].y][pop[i].x] = N;
    //}
    //pop.clear();

    for(i=size; i<plants_pop; i++){
        entity ind;

        ind.x = rand()%X;
        ind.y = rand()%Y;

        while(check_disponibility(ind.x, ind.y) == -1){
            ind.x = rand()%X;
            ind.y = rand()%Y;
        }

        matrix[ind.y][ind.x] = 3;

        plant_sim.push_back(ind);
    }
}

void SimulationManager::move_carnivores(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop){


    int i, move_x, move_y, x, y;
    bool obstacles = false;
    int size = pop.size();

    float Cos, Sin;

    for(i=0; i<size; i++){

        matrix[pop[i].y][pop[i].x] = 0;

        //if(isnan(pop[i].angle) != 0)
        //printf("%f\n",pop[i].angle);

        Cos = qCos(pop[i].angle);
        Sin = qSin(pop[i].angle);

        move_x = Cos*primary_pop[sim_gen][i].speed;
        move_y = Sin*primary_pop[sim_gen][i].speed;
        x = pop[i].x + move_x;
        y = pop[i].y + move_y;

        //if(isnan(pop[i].angle) != 0)
        //printf("%f\n",pop[i].angle);


        int type;

        /////////////////////////// ANY OBSTACLES IN MY WAY??? /////////////////////////////////////////

        obstacles = carnivores_check_for_obstacles(pop[i].x, pop[i].y, Cos, Sin, primary_pop[sim_gen][i].speed, &type);
        // are there any obstacles in the way?
        // analyse line from (pop.x)(pop.y) to (x)(y)
        // if there is an obstacle, stay still

        if(obstacles == false){ // move
            if(x < 0){
                x = X + x;
            }
            else if(x >= X){
                x = x%X;
            }
            if(y < 0){
                y = Y + y;
            }
            else if(y >= Y){
                y = y%Y;
            }
            if( x>=0 && x<X && y>=0 && y<Y){
                pop[i].x = x;
                pop[i].y = y;
            }
            else{
                printf("ERRO (%d) Angle: %f Coordinates: (%d,%d) Should be coordinates: (%d,%d)\n",i,pop[i].angle,pop[i].x,pop[i].y,x,y);
                //getchar();
            }
        }
        //printf("%d %d\n",pop[i].y,pop[i].x);

        matrix[pop[i].y][pop[i].x] = 1;
     }
}

void SimulationManager::move_wanderers(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop){

    int i, move_x, move_y, x, y;
    bool obstacles = false;
    int size = pop.size();

    float Cos, Sin;

    for(i=0; i<size; i++){

        matrix[pop[i].y][pop[i].x] = 0;

        //if(isnan(pop[i].angle) != 0)
        //printf("%f\n",pop[i].angle);

        Cos = qCos(pop[i].angle);
        Sin = qSin(pop[i].angle);

        move_x = Cos*primary_pop[sim_gen][i].speed;
        move_y = Sin*primary_pop[sim_gen][i].speed;
        x = pop[i].x + move_x;
        y = pop[i].y + move_y;

        //if(isnan(pop[i].angle) != 0)
        //printf("%f\n",pop[i].angle);


        int type;

        /////////////////////////// ANY OBSTACLES IN MY WAY??? /////////////////////////////////////////

        obstacles = check_for_obstacles(pop[i].x, pop[i].y, Cos, Sin, primary_pop[sim_gen][i].speed, &type);
        // are there any obstacles in the way?
        // analyse line from (pop.x)(pop.y) to (x)(y)
        // if there is an obstacle, stay still

        if(obstacles == false){ // move
            if(x < 0){
                x = X + x;
            }
            else if(x >= X){
                x = x%X;
            }
            if(y < 0){
                y = Y + y;
            }
            else if(y >= Y){
                y = y%Y;
            }
            if( x>=0 && x<X && y>=0 && y<Y){
                pop[i].x = x;
                pop[i].y = y;
            }
            else{
                printf("ERRO (%d) Angle: %f Coordinates: (%d,%d) Should be coordinates: (%d,%d)\n",i,pop[i].angle,pop[i].x,pop[i].y,x,y);
                //getchar();
            }
        }
        else if(obstacles == true){ // don't move, and (DON'T)rotate  // THIS ROTATION CAN ALSO EVOLVE!!
            //pop[i].angle = pop[i].angle + PI/6;

            if(type == 2){ // DIE?
                pop[i].angle = pop[i].angle + REFLEX_ARC;
                //printf("%f\n",pop[i].angle);
                //printf("(%d) Hurt: %d Atacked...\n",i,pop[i].hurt);
            }
        }
        //printf("%d %d\n",pop[i].y,pop[i].x);

        matrix[pop[i].y][pop[i].x] = 1;
     }
}

bool SimulationManager::carnivores_check_for_obstacles(int x0, int y0, float Cos, float Sin, int speed, int *type){

    bool obstacles = false;

    float distance;

    // start point and bottom limit
    int x1, y1;
    float distance1;
    // OBS: if change bellow, change ALSO distance1 and 2 parameters to (speed) intead of (speed+2*RADIUS_WANDER)

    //x1 = x0 + Cos*2*RADIUS_WANDER;
    //y1 = y0 + Sin*2*RADIUS_WANDER;
    x1 = x0 + Cos*RADIUS;
    y1 = y0 + Sin*RADIUS;

    // end point and top limit
    int x2, y2;
    float distance2;
    x2 = x0 + Cos*(speed+2*RADIUS);
    y2 = y0 + Sin*(speed+2*RADIUS);

    // for the perpendicular line, its perp_angle is given by <angle-90>
    // cos(perp_angle) = sin(angle)
    // sin(perp_angle) = -cos(angle)
    // so that the director vector is (sin(angle), -cos(angle))

    // MAYBE change order? First search between plants, and afterwards in the wanderers population?

    int i;
    for(i=0; i<herb_pop; i++){
        if((herb_sim[i].x != x0) && (herb_sim[i].y != y0)){ // if I'm not myself

            distance = Cos*(herb_sim[i].y - y0) - Sin*(herb_sim[i].x - x0);
            if(distance < 0)
                distance = -distance;
            if(distance <= 2*RADIUS){

                distance1 = Sin*(herb_sim[i].y - y1) + Cos*(herb_sim[i].x - x1);
                distance2 = Sin*(herb_sim[i].y - y2) + Cos*(herb_sim[i].x - x2);

                if(distance1 < 0)
                    distance1 = -distance1;
                if(distance2 < 0)
                    distance2 = -distance2;

                // distance to both restrictive perpendicular lines must be less than or equal to speed
                if(distance1 <= (speed+2*RADIUS) && distance2 <= (speed+2*RADIUS)){
                    obstacles = true;
                    *type = 1;
                    return obstacles;
                }
            }
        }
    }

    for(i=0; i<carn_pop; i++){
        distance = Cos*(carn_sim[i].y - y0) - Sin*(carn_sim[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= (RADIUS+RADIUS)){

            distance1 = Sin*(carn_sim[i].y - y1) + Cos*(carn_sim[i].x - x1);
            distance2 = Sin*(carn_sim[i].y - y2) + Cos*(carn_sim[i].x - x2);

            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS+RADIUS)) && distance2 <= (speed+(RADIUS+RADIUS))){
                obstacles = true;
                *type = 2;
                return obstacles;
            }
        }
    }

    int size = plant_sim.size();

    for(i=0; i<size; i++){
        distance = Cos*(plant_sim[i].y - y0) - Sin*(plant_sim[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= (RADIUS+RADIUS)){

            distance1 = Sin*(plant_sim[i].y - y1) + Cos*(plant_sim[i].x - x1);
            distance2 = Sin*(plant_sim[i].y - y2) + Cos*(plant_sim[i].x - x2);

            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS+RADIUS)) && distance2 <= (speed+(RADIUS+RADIUS))){
                obstacles = true;
                *type = 3;
                return obstacles;
            }
        }
    }

    return obstacles;
}

bool SimulationManager::check_for_obstacles(int x0, int y0, float Cos, float Sin, int speed, int *type){
    bool obstacles = false;

    float distance;

    // start point and bottom limit
    int x1, y1;
    float distance1;
    // OBS: if change bellow, change ALSO distance1 and 2 parameters to (speed) intead of (speed+2*RADIUS_WANDER)

    //x1 = x0 + Cos*2*RADIUS_WANDER;
    //y1 = y0 + Sin*2*RADIUS_WANDER;
    x1 = x0 + Cos*RADIUS;
    y1 = y0 + Sin*RADIUS;

    // end point and top limit
    int x2, y2;
    float distance2;
    x2 = x0 + Cos*(speed+2*RADIUS);
    y2 = y0 + Sin*(speed+2*RADIUS);

    // for the perpendicular line, its perp_angle is given by <angle-90>
    // cos(perp_angle) = sin(angle)
    // sin(perp_angle) = -cos(angle)
    // so that the director vector is (sin(angle), -cos(angle))

    // MAYBE change order? First search between plants, and afterwards in the wanderers population?

    int i;
    for(i=0; i<herb_pop; i++){
        if((herb_sim[i].x != x0) && (herb_sim[i].y != y0)){ // if I'm not myself

            distance = Cos*(herb_sim[i].y - y0) - Sin*(herb_sim[i].x - x0);
            if(distance < 0)
                distance = -distance;
            if(distance <= 2*RADIUS){

                distance1 = Sin*(herb_sim[i].y - y1) + Cos*(herb_sim[i].x - x1);
                distance2 = Sin*(herb_sim[i].y - y2) + Cos*(herb_sim[i].x - x2);

                if(distance1 < 0)
                    distance1 = -distance1;
                if(distance2 < 0)
                    distance2 = -distance2;

                // distance to both restrictive perpendicular lines must be less than or equal to speed
                if(distance1 <= (speed+2*RADIUS) && distance2 <= (speed+2*RADIUS)){
                    obstacles = true;
                    *type = 1;
                    return obstacles;
                }
            }
        }
    }

    for(i=0; i<carn_pop; i++){
        distance = Cos*(carn_sim[i].y - y0) - Sin*(carn_sim[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= (RADIUS+RADIUS)){

            distance1 = Sin*(carn_sim[i].y - y1) + Cos*(carn_sim[i].x - x1);
            distance2 = Sin*(carn_sim[i].y - y2) + Cos*(carn_sim[i].x - x2);

            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS+RADIUS)) && distance2 <= (speed+(RADIUS+RADIUS))){
                obstacles = true;
                *type = 2;
                return obstacles;
            }
        }
    }

    int size = plant_sim.size();

    for(i=0; i<size; i++){
        distance = Cos*(plant_sim[i].y - y0) - Sin*(plant_sim[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= (RADIUS+RADIUS)){

            distance1 = Sin*(plant_sim[i].y - y1) + Cos*(plant_sim[i].x - x1);
            distance2 = Sin*(plant_sim[i].y - y2) + Cos*(plant_sim[i].x - x2);

            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS+RADIUS)) && distance2 <= (speed+(RADIUS+RADIUS))){
                obstacles = true;
                *type = 3;

                matrix[plant_sim[i].y][plant_sim[i].x] = 0;

                plant_sim.erase(plant_sim.begin() + i);
                return obstacles;
            }
        }
    }

    return obstacles;
}

void SimulationManager::genetic_rotation(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop, int index){

    float plant_rotation;
    float wond_rotation;
    float carn_rotation;

    bool b_plant, b_wond, b_carn;

    int xplant, yplant;
    float plant_angle;

    int xwond, ywond;
    float wond_angle;

    int xcarn, ycarn;
    float carn_angle;

    float angle;

    float p=0, c=0, w=0;

    if(primary_pop[sim_gen][index].search_height_limit == 0){
        //struct timespec tstart={0,0}, tend={0,0};
        //clock_gettime(CLOCK_MONOTONIC, &tstart);

        obstacles_bfs(pop[index].x, pop[index].y, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn);

        //clock_gettime(CLOCK_MONOTONIC, &tend);
        //printf("BFS took %.5f seconds\n",
        //       ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
        //       ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));


        // AQUI SURGE NAN
        //printf("(%d)\t",index);
        // angular deviation between wonderer orientation and obstacle position
        plant_angle = calculate_angle(pop[index].x, pop[index].y, xplant, yplant, pop[index].angle);
        //printf("%f\t",plant_angle);
        wond_angle = calculate_angle(pop[index].x, pop[index].y, xwond, ywond, pop[index].angle);
        //printf("%f\t",wond_angle);
        carn_angle = calculate_angle(pop[index].x, pop[index].y, xcarn, ycarn, pop[index].angle);
        //printf("%f\n",carn_angle);
        if(isnan(plant_angle) == 0){ // not NAN
            plant_rotation = ((float)primary_pop[sim_gen][index].plant_const)*2*PI/100; // rotate this in relation to plant_angle
            plant_rotation = primary_pop[sim_gen][index].plant_weight*(plant_rotation + plant_angle);
            p = 1;
        }
        else{
            plant_rotation = 0;
        }

        if(isnan(wond_angle) == 0){
            wond_rotation = ((float)primary_pop[sim_gen][index].herb_const)*2*PI/100;
            wond_rotation = primary_pop[sim_gen][index].herb_weight*(wond_rotation + wond_angle);
            w = 1;
        }
        else{
            wond_rotation = 0;
        }

        if(isnan(carn_angle) == 0){
            carn_rotation = ((float)primary_pop[sim_gen][index].carn_const)*2*PI/100;
            carn_rotation = primary_pop[sim_gen][index].carn_weight*(carn_rotation + carn_angle);
            c = 1;
        }
        else{
            carn_rotation = 0;
        }
    }
    else{   // if there is a height limit
        //struct timespec tstart={0,0}, tend={0,0};
        //clock_gettime(CLOCK_MONOTONIC, &tstart);

        obstacles_bfs_restricted(pop[index].x, pop[index].y, &b_plant, &b_wond, &b_carn, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn, primary_pop[sim_gen][index].search_height);

        //clock_gettime(CLOCK_MONOTONIC, &tend);
        //printf("BFS took %.5f seconds\n",
        //       ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
        //       ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

        if(b_plant == true){
            plant_angle = calculate_angle(pop[index].x, pop[index].y, xplant, yplant, pop[index].angle);
            if(isnan(plant_angle) == 0){ // not NAN
                plant_rotation = ((float)primary_pop[sim_gen][index].plant_const)*2*PI/100; // rotate this in relation to plant_angle
                plant_rotation = primary_pop[sim_gen][index].plant_weight*(plant_rotation + plant_angle);
                p = 1;
            }
            else{
                plant_rotation = 0;
            }
        }else{
            plant_rotation = 0;
        }

        if(b_wond == true){
            wond_angle = calculate_angle(pop[index].x, pop[index].y, xwond, ywond, pop[index].angle);
            if(isnan(wond_angle) == 0){
                wond_rotation = ((float)primary_pop[sim_gen][index].herb_const)*2*PI/100;
                wond_rotation = primary_pop[sim_gen][index].herb_weight*(wond_rotation + wond_angle);
                w = 1;
            }
            else{
                wond_rotation = 0;
            }
        }else{
            wond_rotation = 0;
        }

        if(b_carn == true){
            carn_angle = calculate_angle(pop[index].x, pop[index].y, xcarn, ycarn, pop[index].angle);
            if(isnan(carn_angle) == 0){
                carn_rotation = ((float)primary_pop[sim_gen][index].carn_const)*2*PI/100;
                carn_rotation = primary_pop[sim_gen][index].carn_weight*(carn_rotation + carn_angle);
                c = 1;
            }
            else{
                carn_rotation = 0;
            }
        }else{
            carn_rotation = 0;
        }
    }



    angle = (plant_rotation + wond_rotation + carn_rotation)/(w*primary_pop[sim_gen][index].herb_weight + p*primary_pop[sim_gen][index].plant_weight + c*primary_pop[sim_gen][index].carn_weight);
    angle = pop[index].angle + angle;

    if((isnan(angle) == 0) && (isfinite(angle) != 0)){ // not NAN and FINITE
        //printf("ok\n");
        pop[index].angle = angle;
    }
    //end = time(NULL);
    //printf("%lf\n",difftime(end,start));
    // caso contrario o angulo nao é modificado, verificar onde o err pe gerado e corrigir!!
}

float SimulationManager::calculate_angle(int x, int y, int xobs, int yobs, float dir_angle){
    float angle;

    // idealy the angle variation must vary betwen -PI and PI

    float dir_vec_x, dir_vec_y;
    float obs_vec_x, obs_vec_y;

    // NORM = 1
    dir_vec_x = qCos(dir_angle);
    dir_vec_y = qSin(dir_angle);

    obs_vec_x = xobs - x;
    obs_vec_y = yobs - y;

    float Sin;
    Sin = ((dir_vec_x * obs_vec_y)-(obs_vec_x * dir_vec_y))/sqrt(obs_vec_x*obs_vec_x + obs_vec_y*obs_vec_y);

    float Cos;
    Cos = ((dir_vec_x * obs_vec_x) + (dir_vec_y * obs_vec_y))/sqrt(obs_vec_x*obs_vec_x + obs_vec_y*obs_vec_y);

    //printf("acos(%f)=%f asin(%f)=%f\n",Cos,aCos,Sin,aSin);

    if(Cos >= 0){
        angle = qAsin(Sin);
    }
    else{
        if(Sin >= 0){
            angle = qAcos(Cos);
        }
        else{
            angle = -qAcos(Cos);
        }
    }


    return angle;
}

void SimulationManager::obstacles_bfs(int startx, int starty, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn){

    const int dir[4][2] = {{1,0},
                           {-1,0},
                           {0,1},
                           {0,-1}};

    //time_t start, end;
    //start = time(NULL);
    // stores whether obstacle was already found or not
    bool plant = false;
    bool wond = false;
    bool carn = false;

    *xplant = *yplant = *xwond = *ywond = *xcarn = *ycarn = 0;

    queue <pair<int,int>> fila;

    bool visited[Y][X];   // stores whether the position has been visited or not
    //int altura[Y][X];     // stores the search height of position
    int nextX, nextY;

    fila.push(make_pair(startx, starty));

    int i,j;
    for(i=0; i<Y; i++){
        for(j=0; j<X; j++){
            visited[i][j] = false;
        }
    }

    visited[starty][startx] = true;
    //altura[starty][startx] = 0;


    while(!fila.empty()){
        // pop off the queue's front
        pair <int, int> curr = fila.front();    // curr -> current
        fila.pop();

        // 4 direction
        for(int i=0;i<4;i++){
            // next Y
            nextY = dir[i][0] + curr.second;
            // next X
            nextX = dir[i][1] + curr.first;

            // if it isn't on the matrix...
            if(nextX < 0 || nextY < 0 || nextX >= X || nextY >= Y)
                continue;   // forces execution of next iteration

            // if it wasn't visited, puts on the matrix
            if(!visited[nextY][nextX]){
                if(matrix[nextY][nextX] != 0){
                    if((matrix[nextY][nextX] == 3) && (plant == false)){
                        *xplant = nextX;
                        *yplant = nextY;
                        plant = true;

                        if(wond == true && carn == true){
                            return;
                        }
                    }
                    if((matrix[nextY][nextX] == 1) && (wond == false)){
                        *xwond = nextX;
                        *ywond = nextY;
                        wond = true;

                        if(plant == true && carn == true){
                            return;
                        }
                    }
                    if((matrix[nextY][nextX] == 2) && (carn == false)){
                        *xcarn = nextX;
                        *ycarn = nextY;
                        carn = true;

                        if(plant == true && wond == true){
                            return;
                        }
                    }
                }
                fila.push(make_pair(nextX, nextY));
                // marks as visited
                visited[nextY][nextX] = true;
                //altura[nextY][nextX] = altura[curr.second][curr.first] + 1;
            }
        }
    }
    return;
}

void SimulationManager::obstacles_bfs_restricted(int startx, int starty, bool* b_plant, bool* b_wond, bool* b_carn, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn, int height){

    const int dir[4][2] = {{1,0},
                           {-1,0},
                           {0,1},
                           {0,-1}};
    //time_t start, end;
    //start = time(NULL);
    // stores whether obstacle was already found or not
    bool plant = false;
    bool wond = false;
    bool carn = false;

    *xplant = *yplant = *xwond = *ywond = *xcarn = *ycarn = 0;
    *b_plant = *b_wond = *b_carn = false;

    queue <pair<int,int>> fila;

    bool visited[Y][X];   // stores whether the position has been visited or not
    int heightMatrix[Y][X];     // stores the search height of position
    int nextX, nextY;

    fila.push(make_pair(startx, starty));

    int i,j;
    for(i=0; i<Y; i++){
        for(j=0; j<X; j++){
            visited[i][j] = false;
        }
    }

    visited[starty][startx] = true;
    heightMatrix[starty][startx] = 0;


    while(!fila.empty()){
        // pop off the queue's front
        pair <int, int> curr = fila.front();    // curr -> current
        fila.pop();

        if(heightMatrix[curr.second][curr.first] > height){
            return;
        }

        // 4 direction
        for(int i=0;i<4;i++){
            // next Y
            nextY = dir[i][0] + curr.second;
            // next X
            nextX = dir[i][1] + curr.first;

            // if it isn't on the matrix...
            if(nextX < 0 || nextY < 0 || nextX >= X || nextY >= Y)
                continue;   // forces execution of next iteration

            // if it wasn't visited, puts on the matrix
            if(!visited[nextY][nextX]){
                if(matrix[nextY][nextX] != 0){
                    if((matrix[nextY][nextX] == 3) && (plant == false)){
                        *xplant = nextX;
                        *yplant = nextY;
                        plant = true;
                        *b_plant = true;

                        if(wond == true && carn == true){
                            return;
                        }
                    }
                    if((matrix[nextY][nextX] == 1) && (wond == false)){
                        *xwond = nextX;
                        *ywond = nextY;
                        wond = true;
                        *b_wond = true;

                        if(plant == true && carn == true){
                            return;
                        }
                    }
                    if((matrix[nextY][nextX] == 2) && (carn == false)){
                        *xcarn = nextX;
                        *ycarn = nextY;
                        carn = true;
                        *b_carn = true;

                        if(plant == true && wond == true){
                            return;
                        }
                    }
                }
                fila.push(make_pair(nextX, nextY));
                // marks as visited
                visited[nextY][nextX] = true;
                heightMatrix[nextY][nextX] = heightMatrix[curr.second][curr.first] + 1;
            }
        }
    }
    return;
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


    int i, x, y;
    for(i=0; i<herb_sim.size(); i++){
        x = herb_sim[i].x;
        y = herb_sim[i].y;
        if(x >= 0 && x < X && y >= 0 && y < Y){
            circle(image, Point(x,y), RADIUS, blue, -1,  LINE_8 );
            line (image, Point(x+(qCos(herb_sim[i].angle)*RADIUS),y+(qSin(herb_sim[i].angle)*RADIUS)), Point(x+(qCos(herb_sim[i].angle)*3*RADIUS),y+(qSin(herb_sim[i].angle)*3*RADIUS)), Scalar(0,0,0), 1, LINE_8);
        }
    }
    for(i=0; i<carn_sim.size(); i++){
        x = carn_sim[i].x;
        y = carn_sim[i].y;
        if(x >= 0 && x < X && y >= 0 && y < Y){
            circle(image, Point(x,y), RADIUS, pink, -1,  LINE_8 );
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

    return image;
}

void SimulationManager::on_frameRate_valueChanged(int arg1)
{
    gen_interval = arg1;
}
