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
    //printf("HERBIVORES\n");
    for(i=0; i<size; i++){
        //printf("(%d) ",i);
        genetic_rotation(herb_sim,herbivores,i);
        //printf("Angle: %f\n",herb_sim[i].angle);
    }

    size = carn_sim.size();
    //printf("CARNIVORES\n");
    for(i=0; i<size; i++){
        //printf("(%d) ",i);
        genetic_rotation(carn_sim,carnivores,i);
        //printf("Angle: %f\n",carn_sim[i].angle);
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

    //printf("CARNIVORES\n");

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

        matrix[pop[i].y][pop[i].x] = 2;

        //printf("(%d) obstacle:%d\n",i,obstacles);
     }
}

void SimulationManager::move_wanderers(QVector<entity>& pop, QVector<QVector<individual>>& primary_pop){

    int i, move_x, move_y, x, y;
    bool obstacles = false;
    int size = pop.size();

    float Cos, Sin;

    //printf("HERBIVORES\n");

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

        //printf("(%d) obstacle:%d\n",i,obstacles);
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

    for(i=0; i<carn_pop; i++){
        if((carn_sim[i].x != x0) && (carn_sim[i].y != y0)){ // if I'm not myself
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

        closest_obstacles(index, pop[index].x, pop[index].y, &b_plant, &b_wond, &b_carn, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn, primary_pop[sim_gen][index].search_height_limit, primary_pop[sim_gen][index].search_height);

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

        closest_obstacles(index, pop[index].x, pop[index].y, &b_plant, &b_wond, &b_carn, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn, primary_pop[sim_gen][index].search_height_limit, primary_pop[sim_gen][index].search_height);

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

void SimulationManager::closest_obstacles(int index, int startx, int starty, bool* b_plant, bool* b_wond, bool* b_carn, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn, bool limit, int height){


    *b_plant = *b_wond = *b_carn = true;


    int i,size;

    float distance, closest, ref;
    float wand_dist, carn_dist, plant_dist, dist_lim;
    int index_closest;
    int x_diff, y_diff;

    ref = X*X + Y*Y + 1;
    // find closest obstacle of each kind

    size = herb_sim.size();
    if(size == 0){
        (*b_wond) = false;
    }
    closest = ref;
    for(i=0; i<size; i++){
        x_diff = herb_sim[i].x - startx;
        y_diff = herb_sim[i].y - starty;
        distance = x_diff*x_diff + y_diff*y_diff;   // no need to take the square root

        if(distance != 0 && distance < closest){
            closest = distance;
            index_closest = i;
        }
    }
    wand_dist = closest;
    *xwond = herb_sim[index_closest].x;
    *ywond = herb_sim[index_closest].y;

    size = carn_sim.size();
    if(size == 0){
        (*b_carn) = false;
    }
    closest = ref;
    for(i=0; i<size; i++){
        x_diff = carn_sim[i].x - startx;
        y_diff = carn_sim[i].y - starty;
        distance = x_diff*x_diff + y_diff*y_diff;   // no need to take the square root

        if(distance != 0 && distance < closest){
            closest = distance;
            index_closest = i;
        }
    }
    carn_dist = closest;
    *xcarn = carn_sim[index_closest].x;
    *ycarn = carn_sim[index_closest].y;

    size = plant_sim.size();
    if(size == 0){
        (*b_plant) = false;
    }
    closest = ref;
    for(i=0; i<size; i++){
        x_diff = plant_sim[i].x - startx;
        y_diff = plant_sim[i].y - starty;
        distance = x_diff*x_diff + y_diff*y_diff;   // no need to take the square root

        if(distance < closest){
            closest = distance;
            index_closest = i;
        }
    }
    plant_dist = closest;
    *xplant = plant_sim[index_closest].x;
    *yplant = plant_sim[index_closest].y;

    // check search height limit
    if(limit == true){
        dist_lim = height*height;

        if(wand_dist > dist_lim)
            *b_wond = false;

        if(carn_dist > dist_lim)
            *b_carn = false;

        if(plant_dist > dist_lim)
            *b_plant = false;

    }

    //printf("herb:%d-(%d,%d), carn:%d-(%d,%d), plant%d-(%d,%d), ",(*b_wond),(*xwond),(*ywond),(*b_carn),(*xcarn),(*ycarn),(*b_plant),(*xplant),(*yplant));

}
