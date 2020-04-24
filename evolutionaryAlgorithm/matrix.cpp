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


void initialize_wanderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i, prob;
    for(i=0; i<POP_WANDER; i++){

        srand(time(0)+i);

        population ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        ind.speed = rand()%MAX_SPEED;
        //if(i == 0)ind.speed = 20;
        ind.angle = (float)(rand()%628)/100;  // 628 = 2*PI*100
        //printf("%f",ind.angle);
        ind.energy = 0;
        ind.health = 0;
        ind.hurt = 0;
        
        int j;
        for(j=0; j<HERITAGE_WANDER; j++){
            ind.heritage.push_front(0);
        }
        //////////////////////////////////////////////////
        /*
        printf("(%d) ",i);
        for(j=0; j<HERITAGE_WANDER; j++){
            printf("%d ",ind.heritage[j]);
        }
        printf("\n");
        */
        //////////////////////////////////////////////////
        ind.average_energy = 0;
        ind.h_count = 0;

        ind.plant_const = rand()%MAX_CONST; // up to 100
        //if(i == 0)ind.plant_const = 0;

        ind.wond_const = rand()%MAX_CONST;
        //if(i == 0) ind.wond_const = 30;

        ind.carn_const = rand()%MAX_CONST; 
        //if(i == 0)ind.carn_const = 30;

        ind.plant_weight = rand()%MAX_WEIGHT;
        //if(i == 0) ind.plant_weight = 10;

        ind.wond_weight = rand()%MAX_WEIGHT;
        //if(i == 0) ind.wond_weight = 0;

        ind.carn_weight = rand()%MAX_WEIGHT;
        //if(i == 0) ind.carn_weight = 0;

        ind.height_limit = rand()%2; // 0(false) or 1(true)
        ind.height = rand()%BIG_SIZE;

        //printf("(%d) %d %d %d %d %d %d\n",i,ind.plant_const,ind.wond_const,ind.carn_const,ind.plant_weight,ind.wond_weight,ind.carn_weight);
        
        ind.best = false;
        //ind.color = pink;
        ind.color = blue;

        matrix[ind.y][ind.x] = W;

        pop.push_back(ind);
        //////////////////////////////////////////////////
        /*
        printf("(%d) ",i);
        for(j=0; j<HERITAGE_WANDER; j++){
            printf("%d ",pop[i].heritage[j]);
        }
        printf("\n");
        */
        //////////////////////////////////////////////////
    }
}

void initialize_fixed_wanderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    // FILE: "variable_mutation_on_deterioration/wanderers_10000gen_100int_5carn_10herb_10plan_5heritHerb_5heritCarn_20health_10ev(1).txt
    // GENERATION: 6615
    // INDIVIDUAL: 0
    // CHARACTERISTICS: 
    //      plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed health hurt energy
    //      0 30 -7  5 12  0  0 20 24 16  4 Energy:316

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i, prob;
    for(i=0; i<POP_WANDER; i++){

        srand(time(0)+i);

        population ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        ind.angle = (float)(rand()%628)/100;  // 628 = 2*PI*100
        ind.energy = 0;
        ind.health = 0;
        ind.hurt = 0;
        ind.average_energy = 0;
        ind.h_count = 0;
        
        int j;
        for(j=0; j<HERITAGE_WANDER; j++){
            ind.heritage.push_front(0);
        }

        ind.speed = 24;
        ind.plant_const = 0;
        ind.wond_const = -7;
        ind.carn_const = 12;; 

        ind.plant_weight = 30;
        ind.wond_weight = 5;
        ind.carn_weight = 0;

        ind.height_limit = 0;
        ind.height = 20;

        ind.best = false;
        ind.color = blue;

        matrix[ind.y][ind.x] = W;

        pop.push_back(ind);
    }
}

void reposition_wanderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i, prob;
    for(i=0; i<POP_WANDER; i++){

        srand(time(0)+i);

        retry:    
        pop[i].x = rand()%XRESTRAINT;
        pop[i].y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, pop[i].x, pop[i].y) == ERROR){
            goto retry;
        }

        pop[i].angle = (float)(rand()%628)/100;  // 628 = 2*PI*100
        pop[i].energy = 0;
        pop[i].health = 0;
        pop[i].hurt = 0;
        pop[i].average_energy = 0;
        pop[i].h_count = 0;
        
        int j;
        for(j=0; j<HERITAGE_WANDER; j++){
            pop[i].heritage.push_front(0);
        }

        pop[i].color = blue;

        matrix[pop[i].y][pop[i].x] = W;
    }
}

void import_wanderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int temp_bool;

    printf("WANDERERS\n");
    printf("plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed\n");
    int i, prob;
    for(i=0; i<POP_WANDER; i++){

        srand(time(0)+i);

        population ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        scanf("%d %d %d %d %d %d %d %d %d",&ind.plant_const,&ind.plant_weight,&ind.wond_const,&ind.wond_weight,&ind.carn_const,&ind.carn_weight,&temp_bool,&ind.height,&ind.speed);
        ind.height_limit = temp_bool;
        
        ind.angle = (float)(rand()%200*PI)/100;
        ind.energy = 0;
        ind.health = 0;
        ind.hurt = 0;
        int j;
        for(j=0; j<HERITAGE_WANDER; j++){
            ind.heritage.push_front(0);
        }
        ind.average_energy = 0;
        ind.h_count = 0;

        printf("(%d) %d %d %d %d %d %d %d %d %d\n",i,ind.plant_const,ind.wond_const,ind.carn_const,ind.plant_weight,ind.wond_weight,ind.carn_weight,ind.height_limit,ind.height,ind.speed);
        
        ind.best = false;
        //ind.color = pink;
        ind.color = blue;

        matrix[ind.y][ind.x] = W;

        pop.push_back(ind);
    }
}

void move_wanderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);
    Vec3b cyan = Vec3b(255,238,0);

    int i, move_x, move_y, x, y;
    bool obstacles = false;
    int size = pop.size();

    for(i=0; i<size; i++){

        matrix[pop[i].y][pop[i].x] = N;

        //if(isnan(pop[i].angle) != 0)
        //printf("%f\n",pop[i].angle);

        float Cos, Sin;

        Cos = cos(pop[i].angle);
        Sin = sin(pop[i].angle);

        move_x = Cos*pop[i].speed;
        move_y = Sin*pop[i].speed;
        x = pop[i].x + move_x;
        y = pop[i].y + move_y;

        //if(isnan(pop[i].angle) != 0)
        //printf("%f\n",pop[i].angle);
        

        int type;

        /////////////////////////// ANY OBSTACLES IN MY WAY??? /////////////////////////////////////////

        obstacles = check_for_obstacles(pop[i].x, pop[i].y, Cos, Sin, pop[i].speed, &type);
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
                //getchar();
            }
            //pop[i].color = pink;
            pop[i].color = blue;  
        }
        else if(obstacles == true){ // don't move, and (DON'T)rotate  // THIS ROTATION CAN ALSO EVOLVE!!
            //pop[i].angle = pop[i].angle + PI/6;

            if(type == P){ // EAT
                pop[i].health++;
                //pop[i].color = blue;
                pop[i].color = cyan; 
                //printf("(%d) Health: %d Eating...\n",i,pop[i].health);
            }
            else if(type == C){ // DIE?
                pop[i].hurt++;
                //pop[i].color = violet; 
                pop[i].color = blue; 
                /////////////////////////////// ARCO REFLEXO ////////////////////////////////
                //printf("(%d) %f\t",i,pop[i].angle);
                pop[i].angle = pop[i].angle + REFLEX_ARC;
                //printf("%f\n",pop[i].angle);
                //printf("(%d) Hurt: %d Atacked...\n",i,pop[i].hurt);
            }
            else if(type == W){
                //pop[i].color = red;
            }
        }
        //printf("%d %d\n",pop[i].y,pop[i].x);
    
        matrix[pop[i].y][pop[i].x] = W;
        
        ///////////////////////////// WHAT IT THE CLOSEST OBSTACLE TO ME?? //////////////////////////
        /*
        int xobs, yobs, type_obs;
        obstacle_bfs(pop[i].x, pop[i].y, &xobs, &yobs, &type_obs);

        float angle = calculate_angle(pop[i].x, pop[i].y, xobs, yobs, pop[i].angle);

        rotation_equation(pop,i,type_obs,angle);

        float degrees = angle*180/PI;
        */
        // PRINT INFORMATION
        //printf("(%2d) My coordinates: (%d,%d) Obstacle's coordinates(%d): (%d,%d) Angle: %f\n",i, pop[i].x, pop[i].y, type_obs, xobs, yobs, degrees);    
    }
}

void random_wanderers(std::vector<population> &pop, Type matrix[][XSIZE]){

    int i, prob;
    int size = pop.size();

    for(i=0; i<size; i++){
        prob = rand()%100;
        if(prob > 50){
            //printf("(%d) speed %d angle %f ",i,pop[i].speed, pop[i].angle);
            if(prob < 60)
                pop[i].speed = pop[i].speed + PI/6;
            else if(prob < 70)
                pop[i].speed = pop[i].speed - PI/6;
            else if(prob < 80)
                pop[i].angle = pop[i].angle + PI/3;
            else if(prob < 90)
                pop[i].angle = pop[i].angle - PI/3;
            else
                pop[i].angle = pop[i].angle + PI/4;
            //printf("speed %d angle %f\n",pop[i].speed, pop[i].angle);
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
    //for(i=0; i<size; i++){
    //    matrix[pop[i].y][pop[i].x] = N;
    //}
    //pop.clear();

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

bool check_for_obstacles(int x0, int y0, float Cos, float Sin, int speed, int *type){
    bool obstacles = false;

    extern vector<population> wanderers;
    extern vector<plants> plants_pop;
    extern vector<population> carnivores; 

    // WHAT IF ANGLE == 0 or 180 !!!

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

    float Tan_perp;
    float distance;

    // start point and bottom limit
    int x1, y1;
    float distance1;
    // OBS: if change bellow, change ALSO distance1 and 2 parameters to (speed) intead of (speed+2*RADIUS_WANDER)

    //x1 = x0 + Cos*2*RADIUS_WANDER;
    //y1 = y0 + Sin*2*RADIUS_WANDER;
    x1 = x0 + Cos*RADIUS_WANDER;
    y1 = y0 + Sin*RADIUS_WANDER;

    // end point and top limit
    int x2, y2;
    float distance2;
    x2 = x0 + Cos*(speed+2*RADIUS_WANDER);
    y2 = y0 + Sin*(speed+2*RADIUS_WANDER);

    // for the perpendicular line, its perp_angle is given by <angle-90>
    // cos(perp_angle) = sin(angle)
    // sin(perp_angle) = -cos(angle)
    // so that the director vector is (sin(angle), -cos(angle))

    // MAYBE change order? First search between plants, and afterwards in the wanderers population?

    int size = wanderers.size();
    int i;
    for(i=0; i<size; i++){
        if((wanderers[i].x != x0) && (wanderers[i].y != y0)){ // if I'm not myself

            distance = Cos*(wanderers[i].y - y0) - Sin*(wanderers[i].x - x0);
            if(distance < 0)
                distance = -distance;
            if(distance <= 2*RADIUS_WANDER){

                distance1 = Sin*(wanderers[i].y - y1) + Cos*(wanderers[i].x - x1);
                distance2 = Sin*(wanderers[i].y - y2) + Cos*(wanderers[i].x - x2);
                
                if(distance1 < 0)
                    distance1 = -distance1;
                if(distance2 < 0)
                    distance2 = -distance2;

                // distance to both restrictive perpendicular lines must be less than or equal to speed
                if(distance1 <= (speed+2*RADIUS_WANDER) && distance2 <= (speed+2*RADIUS_WANDER)){
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
        if(distance <= (RADIUS_WANDER+RADIUS_CARN)){

            distance1 = Sin*(carnivores[i].y - y1) + Cos*(carnivores[i].x - x1);
            distance2 = Sin*(carnivores[i].y - y2) + Cos*(carnivores[i].x - x2);
            
            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS_WANDER+RADIUS_CARN)) && distance2 <= (speed+(RADIUS_WANDER+RADIUS_CARN))){
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
        if(distance <= (RADIUS_WANDER+RADIUS_PLANTS)){

            distance1 = Sin*(plants_pop[i].y - y1) + Cos*(plants_pop[i].x - x1);
            distance2 = Sin*(plants_pop[i].y - y2) + Cos*(plants_pop[i].x - x2);
            
            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS_WANDER+RADIUS_PLANTS)) && distance2 <= (speed+(RADIUS_WANDER+RADIUS_PLANTS))){
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

    //printf("acos(%f)=%f asin(%f)=%f\n",Cos,aCos,Sin,aSin);
    
    if(Cos >= 0){
        angle = asin(Sin);
    }
    else{
        if(Sin >= 0){
            angle = acos(Cos);
        }
        else{
            angle = -acos(Cos);
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

    //extern double BFS;

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
    /*
    int xobs, yobs, type_obs;


    first_obstacle_bfs(pop[index].x, pop[index].y, &xobs, &yobs, &type_obs);

    if(type_obs == P){
        plant_angle = calculate_angle(pop[index].x, pop[index].y, xplant, yplant, pop[index].angle);
        plant_rotation = ((float)pop[index].plant_const)*2*PI/100; // rotate this in relation to plant_angle
        plant_rotation = plant_rotation + plant_angle;
        pop[index].angle = pop[index].angle + plant_rotation;
    }
    else if(type_obs == C){
        carn_angle = calculate_angle(pop[index].x, pop[index].y, xcarn, ycarn, pop[index].angle); 
        carn_rotation = ((float)pop[index].carn_const)*2*PI/100;
        carn_rotation = carn_rotation + carn_angle;
        pop[index].angle = pop[index].angle + carn_rotation;
    }
    else if(type_obs == W){
        wond_angle = calculate_angle(pop[index].x, pop[index].y, xwond, ywond, pop[index].angle);
        wond_rotation = ((float)pop[index].wond_const)*2*PI/100;
        wond_rotation = wond_rotation + wond_angle;
        pop[index].angle = pop[index].angle + wond_rotation;
    }
    */
    //time_t start,end;
    //start = time(NULL);
    if(pop[index].height_limit == false){

        //struct timespec tstart={0,0}, tend={0,0};
        //clock_gettime(CLOCK_MONOTONIC, &tstart);

        //obstacles_bfs(pop[index].x, pop[index].y, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn);
        closest_obstacles(index, pop[index].x, pop[index].y, &b_plant, &b_wond, &b_carn, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn, pop[index].height_limit, pop[index].height);

        //clock_gettime(CLOCK_MONOTONIC, &tend);
        //printf("BFS took %.5f seconds\n",
        //      ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
        //      ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
    
        //BFS += ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
        

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

        if(isnan(carn_angle) == 0){
            carn_rotation = ((float)pop[index].carn_const)*2*PI/100;
            carn_rotation = pop[index].carn_weight*(carn_rotation + carn_angle);
            c = 1;
        }
        else{
            carn_rotation = 0;
        }
    }
    else{   // if there is a height limit
        
        //struct timespec tstart={0,0}, tend={0,0};
        //clock_gettime(CLOCK_MONOTONIC, &tstart);

        //obstacles_bfs_restricted(pop[index].x, pop[index].y, &b_plant, &b_wond, &b_carn, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn, pop[index].height);
        closest_obstacles(index, pop[index].x, pop[index].y, &b_plant, &b_wond, &b_carn, &xplant, &yplant, &xwond, &ywond, &xcarn, &ycarn, pop[index].height_limit, pop[index].height);

        //clock_gettime(CLOCK_MONOTONIC, &tend);
        //printf("BFS took %.5f seconds\n",
        //      ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
        //      ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
        //BFS += ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
        

        if(b_plant == true){
            plant_angle = calculate_angle(pop[index].x, pop[index].y, xplant, yplant, pop[index].angle);
            if(isnan(plant_angle) == 0){ // not NAN
                plant_rotation = ((float)pop[index].plant_const)*2*PI/100; // rotate this in relation to plant_angle
                plant_rotation = pop[index].plant_weight*(plant_rotation + plant_angle);
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
                wond_rotation = ((float)pop[index].wond_const)*2*PI/100;
                wond_rotation = pop[index].wond_weight*(wond_rotation + wond_angle);
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
                carn_rotation = ((float)pop[index].carn_const)*2*PI/100;
                carn_rotation = pop[index].carn_weight*(carn_rotation + carn_angle);
                c = 1;
            }
            else{
                carn_rotation = 0;
            }
        }else{
            carn_rotation = 0;
        }
    }

    

    angle = (plant_rotation + wond_rotation + carn_rotation)/(w*pop[index].wond_weight + p*pop[index].plant_weight + c*pop[index].carn_weight);
    angle = pop[index].angle + angle;

    if((isnan(angle) == 0) && (isfinite(angle) != 0)){ // not NAN and FINITE
        //printf("ok\n");
        pop[index].angle = angle;
    }  
    //end = time(NULL);
    //printf("%lf\n",difftime(end,start));
    // caso contrario o angulo nao é modificado, verificar onde o err pe gerado e corrigir!!
}
