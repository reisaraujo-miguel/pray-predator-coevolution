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


void initialize_carnivores(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int i, prob;
    for(i=0; i<POP_CARN; i++){

        srand(time(0)+i);

        population ind;

        retry:    
        ind.x = rand()%XRESTRAINT;
        ind.y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, ind.x, ind.y) == ERROR){
            goto retry;
        }

        ind.speed = rand()%MAX_SPEED;
        ind.angle = (float)(rand()%200*PI)/100;
        ind.energy = 0;

        int j;
        for(j=0; j<HERITAGE_CARN; j++){
            ind.heritage.push_front(0);
        }
        //////////////////////////////////////////////////
        /*
        printf("(%d) ",i);
        for(j=0; j<HERITAGE_CARN; j++){
            printf("%d ",ind.heritage[j]);
        }
        printf("\n");
        */
        //////////////////////////////////////////////////
        ind.average_energy = 0;
        ind.h_count = 0;

        ind.plant_const = rand()%101;
        if(i == 0) ind.plant_const = 30;
        ind.wond_const = rand()%101;
        if(i == 0) ind.wond_const = 0;
        ind.carn_const = rand()%101;
        if(i == 0) ind.carn_const = 30;

        ind.plant_weight = rand()%11;
        if(i == 0) ind.plant_weight = 0;
        ind.wond_weight = rand()%11;
        if(i == 0) ind.wond_weight = 10;
        ind.carn_weight = rand()%11;
        if(i == 0) ind.carn_weight = 0;

        ind.height_limit = rand()%2; // 0(false) or 1(true)
        ind.height = rand()%BIG_SIZE;

        //printf("(%d) %d %d %d %d %d %d\n",i,ind.plant_const,ind.wond_const,ind.carn_const,ind.plant_weight,ind.wond_weight,ind.carn_weight);
        
        ind.best = false;
        //ind.color = orange;
        ind.color = pink;

        matrix[ind.y][ind.x] = C;

        pop.push_back(ind);
        //////////////////////////////////////////////////
        /*
        printf("(%d) ",i);
        for(j=0; j<HERITAGE_CARN; j++){
            printf("%d ",pop[i].heritage[j]);
        }
        printf("\n");
        */
        //////////////////////////////////////////////////
    }
}

void carnivores_elitism(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    vector<population> NewPop;

    int size = pop.size();

    // CLONE BEST
    best_carnivore(pop);

    pop[0].energy = 0;

    NewPop.push_back(pop[0]);

    // CHOOSE PARENTS
    int i;
    for(i=1; i<(size-1); i++){ // last individual is the worst (eliminated)
        int p1 = 0;
        int p2 = i;
        // CROSS OVER
        population child = carnivores_cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%101; // up to 100
        foreigner.wond_const = rand()%101;
        foreigner.carn_const = rand()%101;
        foreigner.plant_weight = rand()%11;
        foreigner.wond_weight = rand()%11;
        foreigner.carn_weight = rand()%11;
        foreigner.speed = rand()%MAX_SPEED;
        foreigner.height_limit = rand()%2; // 0(false) or 1(true)
        foreigner.height = rand()%BIG_SIZE;
        //foreigner.speed = 20;
        if(foreigner.speed < 5)
            foreigner.speed = 5;
        NewPop.push_back(foreigner);
    }
    else{
        int p1 = 0;
        int p2 = (size-1);
        // CROSS OVER
        population child = carnivores_cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }

    // CLEAR SPOTS
    for(i=0; i<size; i++){
        matrix[pop[i].y][pop[i].x] = N;
    }

    pop = NewPop;
    NewPop.clear();

    // POSITION AND INITIALIZE NEW POPULATION
    // only the genes have been defined up to now
    
    size = pop.size();
    for(i=0; i<size; i++){
        
        retry:    
        pop[i].x = rand()%XRESTRAINT;
        pop[i].y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, pop[i].x, pop[i].y) == ERROR){
            goto retry;
        }

        pop[i].angle = (float)(rand()%200*PI)/100;
        pop[i].energy = 0;
        pop[i].best = false;
        //pop[i].color = orange;
        pop[i].color = pink;

        matrix[pop[i].y][pop[i].x] = C;
    }
}

void carnivores_tournament(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    vector<population> NewPop;

    int size = pop.size();

    // CLONE BEST
    best_carnivore(pop);

    pop[0].energy = 0;

    NewPop.push_back(pop[0]);

    // CHOOSE PARENTS
    int i;
    for(i=1; i<(size-1); i++){ // last individual is the worst (eliminated)
        
        // 2 candidates for each parent, choose best
        int p11, p12, p21, p22;
        int p1, p2;

        p11 = rand()%size;
        p12 = rand()%size;
        p21 = rand()%size;
        p22 = rand()%size;

        if(pop[p11].energy > pop[p12].energy)
            p1 = p11;
        else
            p1 = p12;

        if(pop[p21].energy > pop[p22].energy)
            p2 = p21;
        else
            p2 = p22;
        
        // CROSS OVER
        population child = carnivores_cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%101; // up to 100
        foreigner.wond_const = rand()%101;
        foreigner.carn_const = rand()%101;
        foreigner.plant_weight = rand()%11;
        foreigner.wond_weight = rand()%11;
        foreigner.carn_weight = rand()%11;
        foreigner.speed = rand()%MAX_SPEED;
        foreigner.height_limit = rand()%2; // 0(false) or 1(true)
        foreigner.height = rand()%BIG_SIZE;
        //foreigner.speed = 20;
        if(foreigner.speed < 5){
            foreigner.speed = 5;
        }
        NewPop.push_back(foreigner);
    }
    else{ 
        int p11, p12, p21, p22;
        int p1, p2;

        p11 = rand()%size;
        p12 = rand()%size;
        p21 = rand()%size;
        p22 = rand()%size;

        if(pop[p11].energy > pop[p12].energy)
            p1 = p11;
        else
            p1 = p12;

        if(pop[p21].energy > pop[p22].energy)
            p2 = p21;
        else
            p2 = p22;
        
        // CROSS OVER
        population child = carnivores_cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }

    // CLEAR SPOTS
    for(i=0; i<size; i++){
        matrix[pop[i].y][pop[i].x] = N;
    }

    pop = NewPop;
    NewPop.clear();

    // POSITION AND INITIALIZE NEW POPULATION
    // only the genes have been defined up to now
    
    size = pop.size();
    for(i=0; i<size; i++){
        
        retry:    
        pop[i].x = rand()%XRESTRAINT;
        pop[i].y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, pop[i].x, pop[i].y) == ERROR){
            goto retry;
        }

        //pop[i].speed = rand()%MAX_SPEED;
        //pop[i].speed = 10;
        pop[i].angle = (float)(rand()%200*PI)/100;
        pop[i].energy = 0;
        pop[i].best = false;
        //pop[i].color = orange;
        pop[i].color = pink;

        matrix[pop[i].y][pop[i].x] = C;
    }

}

population carnivores_cross_over(std::vector<population> &pop, int p1, int p2){

    srand(time(0)+(p1+p2));
    
    population ind;

    ind.plant_const = (pop[p1].plant_const + pop[p2].plant_const)/2;
    ind.wond_const = (pop[p1].wond_const + pop[p2].wond_const)/2;
    ind.carn_const = (pop[p1].carn_const + pop[p2].carn_const)/2;

    ind.plant_weight = (pop[p1].plant_weight + pop[p2].plant_weight)/2;
    ind.wond_weight = (pop[p1].wond_weight + pop[p2].wond_weight)/2;
    ind.carn_weight = (pop[p1].carn_weight + pop[p2].carn_weight)/2;

    ind.speed = (pop[p1].speed + pop[p2].speed)/2;

    int prob;
    prob = rand()%100;
    if(prob<50){
        ind.height_limit = pop[p1].height_limit;
    }
    else{
        ind.height_limit = pop[p2].height_limit;
    }
    ind.height = (pop[p1].height + pop[p2].height)/2;

    srand(time(0)+(p1+p2+1));
    prob = rand()%100;

    if(prob < CARN_CHILD_MUTATION_PROB){
        carnivores_mutation(&ind);
    }

    if(ind.speed < 5){
        ind.speed = 5;
    }
    if(ind.height < 0){
        ind.height = -ind.height;
    }

    return ind;
}

void carnivores_mutation(population* ind){

    // distribuicao das mutacoes
    srand(time(0));

    int prob;
    
    prob = rand()%100;
    if(prob < CONST_UP){
        (*ind).plant_const = (*ind).plant_const + ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (CONST_UP+CONST_DOWN)){
        (*ind).plant_const = (*ind).plant_const - ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }

    prob = rand()%100;
    if(prob < CONST_UP){
        (*ind).wond_const = (*ind).wond_const + ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (CONST_UP+CONST_DOWN)){
        (*ind).wond_const = (*ind).wond_const - ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }

    prob = rand()%100;
    if(prob < CONST_UP){
        (*ind).carn_const = (*ind).carn_const + ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (CONST_UP+CONST_DOWN)){
        (*ind).carn_const = (*ind).carn_const - ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }

    // for the weights, there will be a greater probability of  mutating
    // upwards, since taking the medium value rounds the numbers down

    prob = rand()%100;
    if(prob < WEIGHT_UP){
        (*ind).plant_weight = (*ind).plant_weight + WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (WEIGHT_UP+WEIGHT_DOWN)){
        (*ind).plant_weight = (*ind).plant_weight - WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }

    prob = rand()%100;
    if(prob < WEIGHT_UP){
        (*ind).wond_weight = (*ind).wond_weight + WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (WEIGHT_UP+WEIGHT_DOWN)){
        (*ind).wond_weight = (*ind).wond_weight - WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }

    prob = rand()%100;
    if(prob < WEIGHT_UP){
        (*ind).carn_weight = (*ind).carn_weight + WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (WEIGHT_UP+WEIGHT_DOWN)){
        (*ind).carn_weight = (*ind).carn_weight - WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }


    prob = rand()%100;
    if(prob < SPEED_UP){
        (*ind).speed = (*ind).speed + SPEED_MUTATION;
        //printf("Mutated speed\n");
    }
    else if(prob < (SPEED_UP+SPEED_DOWN)){
        (*ind).speed = (*ind).speed - SPEED_MUTATION;
        //printf("Mutated speed\n");
    }

    prob = rand()%100;
    if(prob < BOOL_HEIGHT){
        (*ind).height_limit = !(*ind).height_limit;
    }

    prob = rand()%100;
    if(prob < HEIGHT){
        (*ind).height = (*ind).height + HEIGHT_MUTATION;
    }
    else if(prob < 2*HEIGHT){
        (*ind).height = (*ind).height - HEIGHT_MUTATION;
    }

}

void best_carnivore(std::vector<population> &pop){
    
    // puts best carnivore on the 0th position and worst carnivore on the last position

    int size = pop.size();
    population temp;

    int i;

    for(i=0; i<size; i++){
        pop[i].best = false;
    }

    for(i=0; i<size; i++){
        if(pop[0].energy < pop[i].energy){
            temp = pop[0];
            pop[0] = pop[i];
            pop[i] = temp;
        }
        if(pop[size-1].energy > pop[i].energy){
            temp = pop[size-1];
            pop[size-1] = pop[i];
            pop[i] = temp;
        }
    }

    pop[0].best = true;
}

void move_carnivores(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);
    Vec3b brown = Vec3b(73,135,187);

    int i, move_x, move_y, x, y;
    float Cos, Sin;
    bool obstacles = false;
    int size = pop.size();

    for(i=0; i<size; i++){

        matrix[pop[i].y][pop[i].x] = N;

        Cos = cos(pop[i].angle);
        Sin = sin(pop[i].angle);

        move_x = Cos*pop[i].speed;
        move_y = Sin*pop[i].speed;
        x = pop[i].x + move_x;
        y = pop[i].y + move_y;

        int type;

        /////////////////////////// ANY OBSTACLES IN MY WAY??? /////////////////////////////////////////

        obstacles = carnivores_check_for_obstacles(pop[i].x, pop[i].y, Cos, Sin, pop[i].speed, &type);
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
            //pop[i].color = orange;  
            pop[i].color = pink;
        }
        else if(obstacles == true){ // don't move, and (DON'T)rotate  // THIS ROTATION CAN ALSO EVOLVE!!
            //pop[i].angle = pop[i].angle + PI/6;

            if(type == W){ // EAT and HURT PRAY (on check for obstacles)
                pop[i].energy++;
                pop[i].color = red; 
                //printf("(%d) Energy: %d Eating...\n",i,pop[i].energy);
            }
        }
        //printf("%d %d\n",pop[i].y,pop[i].x);
    
        matrix[pop[i].y][pop[i].x] = C;
        
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

bool carnivores_check_for_obstacles(int x0, int y0, float Cos, float Sin, int speed, int *type){
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
    // OBS: if change bellow, change ALSO distance1 and 2 parameters to (speed) intead of (speed+2*RADIUS_CARN)

    //x1 = x0 + Cos*2*RADIUS_CARN;
    //y1 = y0 + Sin*2*RADIUS_CARN;
    x1 = x0 + Cos*RADIUS_CARN;
    y1 = y0 + Sin*RADIUS_CARN;


    // end point and top limit
    int x2, y2;
    float distance2;
    x2 = x0 + Cos*(speed+2*RADIUS_CARN);
    y2 = y0 + Sin*(speed+2*RADIUS_CARN);

    // for the perpendicular line, its perp_angle is given by <angle-90>
    // cos(perp_angle) = sin(angle)
    // sin(perp_angle) = -cos(angle)
    // so that the director vector is (sin(angle), -cos(angle))

    // MAYBE change order? First search between plants, and afterwards in the wanderers population?

    int size = wanderers.size();
    int i;
    for(i=0; i<size; i++){

            distance = Cos*(wanderers[i].y - y0) - Sin*(wanderers[i].x - x0);
            if(distance < 0)
                distance = -distance;
            if(distance <= (RADIUS_CARN+RADIUS_WANDER)){

                distance1 = Sin*(wanderers[i].y - y1) + Cos*(wanderers[i].x - x1);
                distance2 = Sin*(wanderers[i].y - y2) + Cos*(wanderers[i].x - x2);
                
                if(distance1 < 0)
                    distance1 = -distance1;
                if(distance2 < 0)
                    distance2 = -distance2;

                // distance to both restrictive perpendicular lines must be less than or equal to speed
                if(distance1 <= (speed+(RADIUS_CARN+RADIUS_WANDER)) && distance2 <= (speed+(RADIUS_CARN+RADIUS_WANDER))){
                    obstacles = true;
                    wanderers[i].hurt++;
                    *type = W;
                    return obstacles;
                }
            }
    }

    size = carnivores.size();
    for(i=0; i<size; i++){

        if((carnivores[i].x != x0) && (carnivores[i].y != y0)){ // if I'm not myself
            distance = Cos*(carnivores[i].y - y0) - Sin*(carnivores[i].x - x0);
            if(distance < 0)
                distance = -distance;
            if(distance <= 2*RADIUS_CARN){

                distance1 = Sin*(carnivores[i].y - y1) + Cos*(carnivores[i].x - x1);
                distance2 = Sin*(carnivores[i].y - y2) + Cos*(carnivores[i].x - x2);
                
                if(distance1 < 0)
                    distance1 = -distance1;
                if(distance2 < 0)
                    distance2 = -distance2;

                // distance to both restrictive perpendicular lines must be less than or equal to speed
                if(distance1 <= (speed+2*RADIUS_CARN) && distance2 <= (speed+2*RADIUS_CARN)){
                    obstacles = true;
                    *type = C;
                    return obstacles;
                }
            } 
        }  
    }

    size = plants_pop.size();
    for(i=0; i<size; i++){
        distance = Cos*(plants_pop[i].y - y0) - Sin*(plants_pop[i].x - x0);
        if(distance < 0)
            distance = -distance;
        if(distance <= (RADIUS_CARN+RADIUS_PLANTS)){

            distance1 = Sin*(plants_pop[i].y - y1) + Cos*(plants_pop[i].x - x1);
            distance2 = Sin*(plants_pop[i].y - y2) + Cos*(plants_pop[i].x - x2);
            
            if(distance1 < 0)
                distance1 = -distance1;
            if(distance2 < 0)
                distance2 = -distance2;

            // distance to both restrictive perpendicular lines must be less than or equal to speed
            if(distance1 <= (speed+(RADIUS_CARN+RADIUS_PLANTS)) && distance2 <= (speed+(RADIUS_CARN+RADIUS_PLANTS))){
                obstacles = true;
                *type = P;

                //extern Type matrix[YSIZE][XSIZE];
                //matrix[plants_pop[i].y][plants_pop[i].x] = N;
                
                //plants_pop.erase(plants_pop.begin() + i);
                return obstacles;
            }
        }
    }

    return obstacles;
}

void import_carnivores(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int temp_bool;

    printf("CARNIVORES\n");
    printf("plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed\n");
    int i, prob;
    for(i=0; i<POP_CARN; i++){

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
        int j;
        for(j=0; j<HERITAGE_CARN; j++){
            ind.heritage.push_front(0);
        }
        ind.average_energy = 0;
        ind.h_count = 0;

        printf("(%d) %d %d %d %d %d %d %d %d %d\n",i,ind.plant_const,ind.wond_const,ind.carn_const,ind.plant_weight,ind.wond_weight,ind.carn_weight,ind.height_limit,ind.height,ind.speed);
        
        ind.best = false;
        //ind.color = orange;
        ind.color = pink;

        matrix[ind.y][ind.x] = C;

        pop.push_back(ind);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void carnivores_elitism_heritage(std::vector<population> &pop, Type matrix[][XSIZE]){

    int j;

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    vector<population> NewPop;

    int size = pop.size();


    // CLONE BEST
    //best_carnivore_heritage(pop);
    NewPop.push_back(pop[0]);

    // CHOOSE PARENTS
    int i;
    for(i=1; i<(size-1); i++){ // last individual is the worst (eliminated in <MIGRATION> generations)
        int p1 = 0;
        int p2 = i;

        // CROSS OVER only if p2's last performance is worse then p1's last performance
        population child;
        if(pop[p2].energy < pop[p1].energy){
            child = carnivores_cross_over_heritage(pop,p1,p2);
        }
        else{ // otherwise, clone p2
            child = pop[p2];
        }
        NewPop.push_back(child);

        // WHY?
        // The heritage method, lessen the noise, perpetuating parents performance
        // to the offspring, therefore, a good individual's bad luck is mitigated,
        // as is a bad individual's good luck.
        // But, sometimes a good individual might result from the crossing
        // over of bad parents, and it's good performance might be deserved,
        // instead of pure luck, therefore, this individual is given another
        // chance to check whether ir is truly good or just lucky.
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%MAX_CONST; // up to 100
        foreigner.wond_const = rand()%MAX_CONST;
        foreigner.carn_const = rand()%MAX_CONST;
        foreigner.plant_weight = rand()%MAX_WEIGHT;
        foreigner.wond_weight = rand()%MAX_WEIGHT;
        foreigner.carn_weight = rand()%MAX_WEIGHT;
        foreigner.speed = rand()%MAX_SPEED;
        foreigner.height_limit = rand()%2; // 0(false) or 1(true)
        foreigner.height = rand()%BIG_SIZE;
        //foreigner.speed = 20;
        if(foreigner.speed < 5)
            foreigner.speed = 5;

        for(j=0; j<HERITAGE_CARN; j++){
            foreigner.heritage.push_front(0);
        }
        foreigner.average_energy = 0;
        foreigner.h_count = 0;
        NewPop.push_back(foreigner);
    }
    else{
        int p1 = 0;
        int p2 = (size-1);
        // CROSS OVER only if p2's last performance is worse then p1's last performance
        population child;
        if(pop[p2].energy < pop[p1].energy){
            child = carnivores_cross_over_heritage(pop,p1,p2);
        }
        else{ // otherwise, clone p2
            child = pop[p2];
        }
        NewPop.push_back(child);
    }

    // CLEAR SPOTS
    for(i=0; i<size; i++){
        matrix[pop[i].y][pop[i].x] = N;
    }

    pop = NewPop;
    NewPop.clear();

    // POSITION AND INITIALIZE NEW POPULATION
    // only the genes have been defined up to now
    
    size = pop.size();
    for(i=0; i<size; i++){

        /*
        printf("(%d) ",i);
        for(int k=0; k<HERITAGE_CARN; k++){
            printf("%d ", pop[i].heritage[k]);
        }
        printf("\n");
        */

        retry:    
        pop[i].x = rand()%XRESTRAINT;
        pop[i].y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, pop[i].x, pop[i].y) == ERROR){
            goto retry;
        }

        pop[i].angle = (float)(rand()%200*PI)/100;
        pop[i].energy = 0;
        pop[i].average_energy = 0;
        pop[i].best = false;
        //pop[i].color = orange;
        pop[i].color = pink;

        matrix[pop[i].y][pop[i].x] = C;
    }
}

void carnivores_tournament_heritage(std::vector<population> &pop, Type matrix[][XSIZE]){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    vector<population> NewPop;

    int size = pop.size();

    // CLONE BEST
    best_carnivore(pop);

    pop[0].energy = 0;

    NewPop.push_back(pop[0]);

    // CHOOSE PARENTS
    int i;
    for(i=1; i<(size-1); i++){ // last individual is the worst (eliminated)
        
        // 2 candidates for each parent, choose best
        int p11, p12, p21, p22;
        int p1, p2;

        p11 = rand()%size;
        p12 = rand()%size;
        p21 = rand()%size;
        p22 = rand()%size;

        if(pop[p11].energy > pop[p12].energy)
            p1 = p11;
        else
            p1 = p12;

        if(pop[p21].energy > pop[p22].energy)
            p2 = p21;
        else
            p2 = p22;
        
        // CROSS OVER
        population child = carnivores_cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%101; // up to 100
        foreigner.wond_const = rand()%101;
        foreigner.carn_const = rand()%101;
        foreigner.plant_weight = rand()%11;
        foreigner.wond_weight = rand()%11;
        foreigner.carn_weight = rand()%11;
        foreigner.speed = rand()%MAX_SPEED;
        foreigner.height_limit = rand()%2; // 0(false) or 1(true)
        foreigner.height = rand()%BIG_SIZE;
        //foreigner.speed = 20;
        if(foreigner.speed < 5){
            foreigner.speed = 5;
        }
        NewPop.push_back(foreigner);
    }
    else{ 
        int p11, p12, p21, p22;
        int p1, p2;

        p11 = rand()%size;
        p12 = rand()%size;
        p21 = rand()%size;
        p22 = rand()%size;

        if(pop[p11].energy > pop[p12].energy)
            p1 = p11;
        else
            p1 = p12;

        if(pop[p21].energy > pop[p22].energy)
            p2 = p21;
        else
            p2 = p22;
        
        // CROSS OVER
        population child = carnivores_cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }

    // CLEAR SPOTS
    for(i=0; i<size; i++){
        matrix[pop[i].y][pop[i].x] = N;
    }

    pop = NewPop;
    NewPop.clear();

    // POSITION AND INITIALIZE NEW POPULATION
    // only the genes have been defined up to now
    
    size = pop.size();
    for(i=0; i<size; i++){
        
        retry:    
        pop[i].x = rand()%XRESTRAINT;
        pop[i].y = rand()%YRESTRAINT;

        if(check_disponibility(matrix, pop[i].x, pop[i].y) == ERROR){
            goto retry;
        }

        //pop[i].speed = rand()%MAX_SPEED;
        //pop[i].speed = 10;
        pop[i].angle = (float)(rand()%200*PI)/100;
        pop[i].energy = 0;
        pop[i].best = false;
        //pop[i].color = orange;
        pop[i].color = pink;

        matrix[pop[i].y][pop[i].x] = C;
    }

} // NOT YET

population carnivores_cross_over_heritage(std::vector<population> &pop, int p1, int p2){

    srand(time(0)+(p1+p2));
    
    population ind;

    ind.plant_const = (pop[p1].plant_const + pop[p2].plant_const)/2;
    ind.wond_const = (pop[p1].wond_const + pop[p2].wond_const)/2;
    ind.carn_const = (pop[p1].carn_const + pop[p2].carn_const)/2;

    ind.plant_weight = (pop[p1].plant_weight + pop[p2].plant_weight)/2;
    ind.wond_weight = (pop[p1].wond_weight + pop[p2].wond_weight)/2;
    ind.carn_weight = (pop[p1].carn_weight + pop[p2].carn_weight)/2;

    ind.speed = (pop[p1].speed + pop[p2].speed)/2;

    int prob;
    prob = rand()%100;
    if(prob<50){
        ind.height_limit = pop[p1].height_limit;
    }
    else{
        ind.height_limit = pop[p2].height_limit;
    }
    ind.height = (pop[p1].height + pop[p2].height)/2;

    int j;
    for(j=0; j<HERITAGE_CARN; j++){
        // INITIALIZE DECK
        ind.heritage.push_back((pop[p1].heritage[j] + pop[p2].heritage[j])/2);
    }
    if(pop[p1].h_count > pop[p2].h_count){
        ind.h_count = pop[p1].h_count;
    }
    else{
        ind.h_count = pop[p2].h_count;
    }

    prob = rand()%100;

    if(prob < CARN_CHILD_MUTATION_PROB){
        carnivores_mutation(&ind);
    }

    if(ind.speed < 5){
        ind.speed = 5;
    }

    return ind;
}

void best_carnivore_heritage(std::vector<population> &pop){
    
    // puts best carnivore on the 0th position and worst carnivore on the last position

    int size = pop.size();
    population temp;

    int i,j;

    for(i=0; i<size; i++){
        pop[i].best = false;
        pop[i].heritage.push_front(pop[i].energy); 
        pop[i].h_count++; // "indica a proxima posicao"

        pop[i].heritage.pop_back();
        
        pop[i].average_energy = 0;
        for(j=0; j<HERITAGE_CARN; j++){
            pop[i].average_energy = pop[i].average_energy + pop[i].heritage[j];
        }
        pop[i].average_energy = pop[i].average_energy/HERITAGE_CARN;
    }

    for(i=0; i<size; i++){
        if(pop[0].average_energy < pop[i].average_energy){
            temp = pop[0];
            pop[0] = pop[i];
            pop[i] = temp;
        }
        if(pop[size-1].average_energy > pop[i].average_energy){
            temp = pop[size-1];
            pop[size-1] = pop[i];
            pop[i] = temp;
        }
    }

    pop[0].best = true;
}