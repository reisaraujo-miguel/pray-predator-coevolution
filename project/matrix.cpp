#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <utility> // pair

#include <iostream>
#include <vector>
#include <deque>

#include "game.h"

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;


void initialize_matrix(Type matrix[][XSIZE]){
    int i, j;

    for(i=0; i<YSIZE; i++){
        for(j=0; j<XSIZE; j++){
            matrix[i][j] = N;
        }
    }
}

int check_disponibility(Type matrix[][XSIZE], int x, int y){
    if(matrix[y][x] != N){
        return ERROR;
    }
    return OK;
}

bool check_for_obstacles(int x0, int y0, float angle, int speed, int *type){
    bool obstacles = false;

    extern vector<population> wonderers;
    extern vector<plants> plants_pop;
    extern vector<population> carnivores; 

    // moving line function
    // (y-y0) = (x-x0)tan(angle)
    // points of interest:
    // start ( x0+cos(angle)*2R, y0+sin(angle)*2R ) - closed
    // end ( x0+cos(angle)*(speed+2R), y0+sin(angle)*(speed+2R) ) - open

    // distance from point to line must be less then 2*RADIUS
    // ||r ^ AP|| / ||r||
    // where r is the director vector of the line (cos(angle), sin(angle))
    // ||r|| = 1
    // P is the evaluated point
    // A is a random point in the line
    // AP = (xp-x0, yp-y0)
    // ||r ^ AP|| = mod[ cos(angle)*(yp-y0) - sin(angle)*(xp-x0) ]

    // distance to perpendicular lines through points of interest must be less than or equal to speed

    double Cos, Sin, Tan_perp;
    double distance;
    Cos = cos(angle);
    Sin = sin(angle);

    // start point and bottom limit
    float x1, y1, distance1;
    // OBS: if change bellow, change ALSO distance1 and 2 parameters to (speed) intead of (speed+2*RADIUS_WONDER)

    //x1 = x0 + Cos*2*RADIUS_WONDER;
    //y1 = y0 + Sin*2*RADIUS_WONDER;
    x1 = x0 + Cos*RADIUS_WONDER;
    y1 = y0 + Sin*RADIUS_WONDER;

    // end point and top limit
    float x2, y2, distance2;
    x2 = x0 + Cos*(speed+2*RADIUS_WONDER);
    y2 = y0 + Sin*(speed+2*RADIUS_WONDER);

    // for the perpendicular line, its perp_angle is given by <angle-90>
    // cos(perp_angle) = sin(angle)
    // sin(perp_angle) = -cos(angle)
    // so that the director vector is (sin(angle), -cos(angle))

    int size = wonderers.size();
    int i;
    for(i=0; i<size; i++){
        if((wonderers[i].x != x0) && (wonderers[i].y != y0)){ // if I'm not myself

            distance = Cos*(wonderers[i].y - y0) - Sin*(wonderers[i].x - x0);
            if(distance < 0)
                distance = -distance;
            if(distance <= 2*RADIUS_WONDER){

                distance1 = Sin*(wonderers[i].y - y1) + Cos*(wonderers[i].x - x1);
                distance2 = Sin*(wonderers[i].y - y2) + Cos*(wonderers[i].x - x2);
                
                if(distance1 < 0)
                    distance1 = -distance1;
                if(distance2 < 0)
                    distance2 = -distance2;

                // distance to both restrictive perpendicular lines must be less than or equal to speed
                if(distance1 <= (speed+2*RADIUS_WONDER) && distance2 <= (speed+2*RADIUS_WONDER)){
                    obstacles = true;
                    *type = W;
                    return obstacles;
                }
            }
        }
    }

    size = carnivores.size();
    for(i=0; i<size; i++){
        distance = Cos*(carnivores[i].y - y0) - Sin*(carnivores[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= 2*RADIUS_WONDER){

            distance1 = Sin*(carnivores[i].y - y1) + Cos*(carnivores[i].x - x1);
            distance2 = Sin*(carnivores[i].y - y2) + Cos*(carnivores[i].x - x2);
            
            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+2*RADIUS_WONDER) && distance2 <= (speed+2*RADIUS_WONDER)){
                obstacles = true;
                *type = C;
                return obstacles;
            }
        }   
    }

    size = plants_pop.size();
    for(i=0; i<size; i++){
        distance = Cos*(plants_pop[i].y - y0) - Sin*(plants_pop[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= 2*RADIUS_WONDER){

            distance1 = Sin*(plants_pop[i].y - y1) + Cos*(plants_pop[i].x - x1);
            distance2 = Sin*(plants_pop[i].y - y2) + Cos*(plants_pop[i].x - x2);
            
            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+2*RADIUS_WONDER) && distance2 <= (speed+2*RADIUS_WONDER)){
                obstacles = true;
                *type = P;

                extern Type matrix[YSIZE][XSIZE];
                matrix[plants_pop[i].y][plants_pop[i].x] = N;
                
                plants_pop.erase(plants_pop.begin() + i);
                return obstacles;
            }
        }
    }

    return obstacles;
}

float calculate_angle(int x, int y, int xobs, int yobs, float dir_angle){
    float angle;

    float aCos, aSin;

    // idealy the angle variation must vary betwen -PI and PI

    float dir_vec_x, dir_vec_y;
    float obs_vec_x, obs_vec_y;

    // NORM = 1
    dir_vec_x = cos(dir_angle);
    dir_vec_y = sin(dir_angle);

    obs_vec_x = xobs - x;
    obs_vec_y = yobs - y;

    float Sin;
    Sin = ((dir_vec_x * obs_vec_y)-(obs_vec_x * dir_vec_y))/sqrt(obs_vec_x*obs_vec_x + obs_vec_y*obs_vec_y);

    float Cos;
    Cos = ((dir_vec_x * obs_vec_x) + (dir_vec_y * obs_vec_y))/sqrt(obs_vec_x*obs_vec_x + obs_vec_y*obs_vec_y);

    aCos = acos(Cos);
    aSin = asin(Sin);
    
    if(Cos >= 0){
        angle = aSin;
    }
    else{
        if(Sin >= 0){
            angle = aCos;
        }
        else{
            angle = -aCos;
        }
    }


    return angle;
}

void rotation_equation(std::vector<population> &pop, int index, int obs_type, float deviation){

    // subdividir o circulo de 0 a 100, 0 esta no angulo/posicao do obstaculo, e o 100 novamente
    // a partir da direcao do obstáculo, mover
    // (2*PI/100)*plant_const + deviation

    // now, for a plant, the ideal constant is 0, or 100

    float rotation;

    rotation = ((float)pop[index].plant_const)*2*PI/100;

    pop[index].angle = pop[index].angle + deviation + rotation;

    //printf("(%d) Angle to obstacle: %f Multiplicative constant: %d\n", index,deviation,pop[index].plant_const);
}

void genetic_rotation(std::vector<population> &pop, int index){

    float plant_rotation;
    float wond_rotation;
    float carn_rotation;

    int xplant, yplant;
    float plant_angle;

    int xwond, ywond;
    float wond_angle;

    int xcarn, ycarn;
    float carn_angle;

    float angle;

    float p=0, c=0, w=0;


    obstacles_bfs(pop[index].x, pop[index].y, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn);

    plant_angle = calculate_angle(pop[index].x, pop[index].y, xplant, yplant, pop[index].angle);
    wond_angle = calculate_angle(pop[index].x, pop[index].y, xwond, ywond, pop[index].angle);
    carn_angle = calculate_angle(pop[index].x, pop[index].y, xcarn, ycarn, pop[index].angle);

    if(isnan(plant_angle) == 0){ // not NAN
        plant_rotation = ((float)pop[index].plant_const)*2*PI/100; // rotate this in relation to plant_angle
        plant_rotation = pop[index].plant_weight*(plant_rotation + plant_angle);
        p = 1;
    }
    else{
        plant_rotation = 0;
    }

    if(isnan(wond_angle) == 0){
        wond_rotation = ((float)pop[index].wond_const)*2*PI/100;
        wond_rotation = pop[index].wond_weight*(wond_rotation + wond_angle);
        w = 1;
    }
    else{
        wond_rotation = 0;
    }

    if(isnan(wond_angle) == 0){
        carn_rotation = ((float)pop[index].carn_const)*2*PI/100;
        carn_rotation = pop[index].carn_weight*(carn_rotation + carn_angle);
        c = 1;
    }
    else{
        carn_rotation = 0;
    }

    angle = (plant_rotation + wond_rotation + carn_rotation)/(w*pop[index].wond_weight + p*pop[index].plant_weight + c*pop[index].carn_weight);
    angle = pop[index].angle + angle;

    if((isnan(angle) == 0) && (isfinite(angle) != 0)){ // not NAN and FINITE
        //printf("ok\n");
        pop[index].angle = angle;
    }  
    // otherwise the individual's angle isn't changed
}



void initialize_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i, prob;
    for(i=0; i<POP_WONDER; i++){

        srand(time(0)+i);

        population ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        ind.speed = rand()%MAX_SPEED;
        if(i == 0)ind.speed = 20;
        ind.angle = (float)(rand()%628)/100;  // 628 = 2*PI*100
        //printf("%f",ind.angle);
        ind.energy = 0;
        ind.health = 0;
        ind.hurt = 0;
        
        int j;
        for(j=0; j<HERITAGE; j++){
            ind.heritage.push_front(0);
        }
        //////////////////////////////////////////////////
        /*
        printf("(%d) ",i);
        for(j=0; j<HERITAGE; j++){
            printf("%d ",ind.heritage[j]);
        }
        printf("\n");
        */
        //////////////////////////////////////////////////
        ind.average_energy = 0;
        ind.h_count = 0;

        ind.plant_const = rand()%MAX_CONST; // up to 100
        if(i == 0 || i == 1)ind.plant_const = 0;

        ind.wond_const = rand()%MAX_CONST;
        if(i == 0 || i == 1) ind.wond_const = 30;

        ind.carn_const = rand()%MAX_CONST; 
        if(i == 0 || i == 1)ind.carn_const = 30;

        ind.plant_weight = rand()%MAX_WEIGHT;
        if(i == 0 || i == 1) ind.plant_weight = 10;

        ind.wond_weight = rand()%MAX_WEIGHT;
        if(i == 0 || i == 1) ind.wond_weight = 0;

        ind.carn_weight = rand()%MAX_WEIGHT;
        if(i == 0 || i == 1) ind.carn_weight = 0;

        //printf("(%d) %d %d %d %d %d %d\n",i,ind.plant_const,ind.wond_const,ind.carn_const,ind.plant_weight,ind.wond_weight,ind.carn_weight);
        
        ind.best = false;
        ind.color = pink;

        matrix[ind.y][ind.x] = W;

        pop.push_back(ind);
        //////////////////////////////////////////////////
        /*
        printf("(%d) ",i);
        for(j=0; j<HERITAGE; j++){
            printf("%d ",pop[i].heritage[j]);
        }
        printf("\n");
        */
        //////////////////////////////////////////////////
    }
}

void import_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    printf("WONDERERS\n");
    printf("plant_const plant_weight wond_const wond_weight carn_const carn_weight speed\n");
    int i, prob;
    for(i=0; i<POP_WONDER; i++){

        srand(time(0)+i);

        population ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        scanf("%d %d %d %d %d %d %d",&ind.plant_const,&ind.plant_weight,&ind.wond_const,&ind.wond_weight,&ind.carn_const,&ind.carn_weight,&ind.speed);

        ind.angle = (float)(rand()%200*PI)/100;
        ind.energy = 0;
        ind.health = 0;
        ind.hurt = 0;
        int j;
        for(j=0; j<HERITAGE; j++){
            ind.heritage.push_front(0);
        }
        ind.average_energy = 0;
        ind.h_count = 0;

        printf("(%d) %d %d %d %d %d %d\n",i,ind.plant_const,ind.wond_const,ind.carn_const,ind.plant_weight,ind.wond_weight,ind.carn_weight);
        
        ind.best = false;
        ind.color = pink;

        matrix[ind.y][ind.x] = W;

        pop.push_back(ind);
    }
}

void move_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i, move_x, move_y, x, y;
    bool obstacles = false;
    int size = pop.size();

    for(i=0; i<size; i++){

        matrix[pop[i].y][pop[i].x] = N;

        move_x = cos(pop[i].angle)*pop[i].speed;
        move_y = sin(pop[i].angle)*pop[i].speed;
        x = pop[i].x + move_x;
        y = pop[i].y + move_y;

        int type;

        /////////////////////////// CHECK FOR OBSTACLES ON PATH /////////////////////////////////////////

        obstacles = check_for_obstacles(pop[i].x, pop[i].y, pop[i].angle, pop[i].speed, &type);
        // are there any obstacles in the way?
        // analyse line from (pop.x)(pop.y) to (x)(y)
        // if there is an obstacle, stay still

        if(obstacles == false){ // move
            if(x < 0){
                x = XSIZE + x;
            }
            else if(x >= XSIZE){
                x = x%XSIZE;
            }
            if(y < 0){
                y = YSIZE + y;
            }
            else if(y >= YSIZE){
                y = y%YSIZE;
            }
            if( x>=0 && x<XSIZE && y>=0 && y<YSIZE){
                pop[i].x = x; 
                pop[i].y = y;
            }
            else{
                printf("ERRO (%d) Angle: %f Coordinates: (%d,%d) Should be coordinates: (%d,%d)\n",i,pop[i].angle,pop[i].x,pop[i].y,x,y);
            }
            pop[i].color = pink;  
        }
        else if(obstacles == true){ // don't move

            if(type == P){ // EAT
                pop[i].health++;
                pop[i].color = blue; 
            }
            else if(type == C){ // DIE?
                pop[i].hurt++;
                pop[i].color = violet; 
                /////////////////////////////// REFLEX ARC ////////////////////////////////
                pop[i].angle = pop[i].angle + PI;
            }
            else if(type == W){
            }
        }
    
        matrix[pop[i].y][pop[i].x] = W;
    }
}

void random_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    int i, prob;
    int size = pop.size();

    for(i=0; i<size; i++){
        prob = rand()%100;
        if(prob > 50){
            if(prob < 60)
                pop[i].speed = pop[i].speed + 3;
            else if(prob < 70)
                pop[i].speed = pop[i].speed - 3;
            else if(prob < 80)
                pop[i].angle = pop[i].angle + PI/3;
            else if(prob < 90)
                pop[i].angle = pop[i].angle - PI/3;
            else
                pop[i].angle = pop[i].angle + PI/4;
        }
    }
}



void initialize_plants(std::vector<plants> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i;

    for(i=0; i<POP_PLANTS; i++){
        plants ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        ind.color = green;

        matrix[ind.y][ind.x] = P;

        pop.push_back(ind);
    }
}

void new_plants(std::vector<plants> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i; 

    int size = pop.size();

    for(i=size; i<POP_PLANTS; i++){
        plants ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        ind.color = green;

        matrix[ind.y][ind.x] = P;

        pop.push_back(ind);
    }
}


