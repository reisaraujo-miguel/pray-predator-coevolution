#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <vector>
#include "global.h"
#include <deque>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

void elitism(std::vector<population> &pop, Type matrix[][XSIZE]){

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
    best_wanderer(pop);

    pop[0].energy = 0;
    pop[0].health = 0;
    pop[0].hurt = 0;

    NewPop.push_back(pop[0]);

    // CHOOSE PARENTS
    int i;
    for(i=1; i<(size-1); i++){ // last individual is the worst (eliminated)
        int p1 = 0;
        //int p2 = rand()%size; ???
        int p2 = i;
        // CROSS OVER
        population child = cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%101; // up to 100
        foreigner.wand_const = rand()%101;
        foreigner.carn_const = rand()%101;
        foreigner.plant_weight = rand()%11;
        foreigner.wand_weight = rand()%11;
        foreigner.carn_weight = rand()%11;
        foreigner.speed = rand()%MAX_SPEED;
        //foreigner.speed = 20;
        if(foreigner.speed < 5)
            foreigner.speed = 5;
        NewPop.push_back(foreigner);
    }
    else{
        int p1 = 0;
        int p2 = (size-1);
        // CROSS OVER
        population child = cross_over(pop,p1,p2);
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

        pop[i].angle = (float)(rand()%628)/100;
        pop[i].energy = 0;
        pop[i].health = 0;
        pop[i].hurt = 0;
        pop[i].best = false;
        //pop[i].color = pink;
        pop[i].color = blue;

        matrix[pop[i].y][pop[i].x] = W;
    }
}

void tournament(std::vector<population> &pop, Type matrix[][XSIZE]){

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
    best_wanderer(pop);

    pop[0].energy = 0;
    pop[0].health = 0;
    pop[0].hurt = 0;

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
        population child = cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%101; // up to 100
        foreigner.wand_const = rand()%101;
        foreigner.carn_const = rand()%101;
        foreigner.plant_weight = rand()%11;
        foreigner.wand_weight = rand()%11;
        foreigner.carn_weight = rand()%11;
        foreigner.speed = rand()%MAX_SPEED;
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
        population child = cross_over(pop,p1,p2);
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
        pop[i].health = 0;
        pop[i].hurt = 0;
        pop[i].best = false;
        //pop[i].color = pink;
        pop[i].color = blue;

        matrix[pop[i].y][pop[i].x] = W;
    }

}

population cross_over(std::vector<population> &pop, int p1, int p2){

    srand(time(0)+(p1+p2));
    
    population ind;

    ind.plant_const = (pop[p1].plant_const + pop[p2].plant_const)/2;
    ind.wand_const = (pop[p1].wand_const + pop[p2].wand_const)/2;
    ind.carn_const = (pop[p1].carn_const + pop[p2].carn_const)/2;

    ind.plant_weight = (pop[p1].plant_weight + pop[p2].plant_weight)/2;
    ind.wand_weight = (pop[p1].wand_weight + pop[p2].wand_weight)/2;
    ind.carn_weight = (pop[p1].carn_weight + pop[p2].carn_weight)/2;

    ind.speed = (pop[p1].speed + pop[p2].speed)/2;

    int prob;
    prob = rand()%100;

    if(prob < CHILD_MUTATION_PROB){
        mutation(&ind);
    }

    if(ind.speed < 5){
        ind.speed = 5;
    }

    return ind;
}

void mutation(population* ind){

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
        (*ind).wand_const = (*ind).wand_const + ANGLE_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (CONST_UP+CONST_DOWN)){
        (*ind).wand_const = (*ind).wand_const - ANGLE_MUTATION;
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
        (*ind).wand_weight = (*ind).wand_weight + WEIGHT_MUTATION;
        //printf("Mutated constant\n");
    }
    else if(prob < (WEIGHT_UP+WEIGHT_DOWN)){
        (*ind).wand_weight = (*ind).wand_weight - WEIGHT_MUTATION;
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
}

void best_wanderer(std::vector<population> &pop){
    
    // puts best wanderer on the 0th position and worst wanderer on the last position

    int size = pop.size();
    population temp;

    int i;

    for(i=0; i<size; i++){
        pop[i].best = false;
        pop[i].energy = (HEALTH_CONST*pop[i].health) - (HURT_CONST*pop[i].hurt);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void elitism_heritage(std::vector<population> &pop, Type matrix[][XSIZE]){

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
    best_wanderer_heritage(pop); // considering average energy
    NewPop.push_back(pop[0]);

    // CHOOSE PARENTS
    int i;
    for(i=1; i<(size-1); i++){ // last individual is the worst (eliminated)
        int p1 = 0;
        int p2 = i;

        // CROSS OVER only if p2's last performance is worse then p1's last performance
        population child;
        if(pop[p2].energy < pop[p1].energy){
            child = cross_over_heritage(pop,p1,p2); 
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
        foreigner.wand_const = rand()%MAX_CONST;
        foreigner.carn_const = rand()%MAX_CONST;
        foreigner.plant_weight = rand()%MAX_WEIGHT;
        foreigner.wand_weight = rand()%MAX_WEIGHT;
        foreigner.carn_weight = rand()%MAX_WEIGHT;
        foreigner.speed = rand()%MAX_SPEED;
        if(foreigner.speed < 5)
            foreigner.speed = 5;

        for(j=0; j<HERITAGE; j++){
            foreigner.heritage.push_front(0);
        }
        foreigner.average_energy = 0;
        foreigner.h_count = 0;

        NewPop.push_back(foreigner);
    }
    else{
        int p1 = 0;
        int p2 = (size-1);
        // CROSS OVER
        population child;
        if(pop[p2].energy < pop[p1].energy){
            child = cross_over_heritage(pop,p1,p2);
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
    size = pop.size();

    NewPop.clear();

    // POSITION AND INITIALIZE NEW POPULATION
    // only the genes have been defined up to now
    
    for(i=0; i<size; i++){

        /*
        printf("(%d) ",i);
        for(int k=0; k<HERITAGE; k++){
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

        pop[i].angle = (float)(rand()%628)/100;
        pop[i].energy = 0;
        pop[i].average_energy = 0;
        pop[i].health = 0;
        pop[i].hurt = 0;
        pop[i].best = false;
        //pop[i].color = pink;
        pop[i].color = blue;

        matrix[pop[i].y][pop[i].x] = W;
    }
}

void tournament_heritage(std::vector<population> &pop, Type matrix[][XSIZE]){

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
    best_wanderer(pop);

    pop[0].energy = 0;
    pop[0].health = 0;
    pop[0].hurt = 0;

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
        population child = cross_over(pop,p1,p2);
        NewPop.push_back(child);
    }


    // MIGRATION (in an interval of 5 generations)
    population foreigner;
    extern int COUNT;
    if(COUNT%(MIGRATION*MATING_INTERVAL) == 0){
        foreigner.plant_const = rand()%101; // up to 100
        foreigner.wand_const = rand()%101;
        foreigner.carn_const = rand()%101;
        foreigner.plant_weight = rand()%11;
        foreigner.wand_weight = rand()%11;
        foreigner.carn_weight = rand()%11;
        foreigner.speed = rand()%MAX_SPEED;
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
        population child = cross_over(pop,p1,p2);
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
        pop[i].health = 0;
        pop[i].hurt = 0;
        pop[i].best = false;
        //pop[i].color = pink;
        pop[i].color = blue;

        matrix[pop[i].y][pop[i].x] = W;
    }

} // NOT YET

population cross_over_heritage(std::vector<population> &pop, int p1, int p2){

    srand(time(0)+(p1+p2));
    
    population ind;

    ind.plant_const = (pop[p1].plant_const + pop[p2].plant_const)/2;
    ind.wand_const = (pop[p1].wand_const + pop[p2].wand_const)/2;
    ind.carn_const = (pop[p1].carn_const + pop[p2].carn_const)/2;

    ind.plant_weight = (pop[p1].plant_weight + pop[p2].plant_weight)/2;
    ind.wand_weight = (pop[p1].wand_weight + pop[p2].wand_weight)/2;
    ind.carn_weight = (pop[p1].carn_weight + pop[p2].carn_weight)/2;

    ind.speed = (pop[p1].speed + pop[p2].speed)/2;

    // INICIALIZE CHILD'S DECK
    int j;
    for(j=0; j<HERITAGE; j++){
        ind.heritage.push_back((pop[p1].heritage[j] + pop[p2].heritage[j])/2);
    }
    if(pop[p1].h_count > pop[p2].h_count){
        ind.h_count = pop[p1].h_count;
    }
    else{
        ind.h_count = pop[p2].h_count;
    }
    
    ///////////////////////////////////////////////////////////////////////////////////
    extern int COUNT;
    FILE* ArqHeritage;
    ArqHeritage = fopen("./data/heritage_wanderers.txt","a+");
    fprintf(ArqHeritage,"NEW INDIVIDUAL - Generation:%d\n",COUNT/MATING_INTERVAL);
    fprintf(ArqHeritage,"Parent1(%d) Energy:%d Average energy:%d Heritage:%d %d %d %d %d\n",p1,pop[p1].energy,pop[p1].average_energy,pop[p1].heritage[0],pop[p1].heritage[1],pop[p1].heritage[2],pop[p1].heritage[3],pop[p1].heritage[4]);
    fprintf(ArqHeritage,"Parent2(%d) Energy:%d Average energy:%d Heritage:%d %d %d %d %d\n",p2,pop[p2].energy,pop[p2].average_energy,pop[p2].heritage[0],pop[p2].heritage[1],pop[p2].heritage[2],pop[p2].heritage[3],pop[p2].heritage[4]);
    fprintf(ArqHeritage,"Child heritage:%d %d %d %d %d\n",ind.heritage[0],ind.heritage[1],ind.heritage[2],ind.heritage[3],ind.heritage[4]);
    fclose(ArqHeritage);
    ///////////////////////////////////////////////////////////////////////////////////
    
    int prob;
    prob = rand()%100;

    if(prob < CHILD_MUTATION_PROB){
        mutation(&ind);
    }

    if(ind.speed < 5){
        ind.speed = 5;
    }

    return ind;
}

void best_wanderer_heritage(std::vector<population> &pop){
    
    // puts best wanderer on the 0th position and worst wanderer on the last position

    int size = pop.size();
    population temp;

    int i,j;

    for(i=0; i<size; i++){
        pop[i].best = false;
        pop[i].energy = (HEALTH_CONST*pop[i].health) - (HURT_CONST*pop[i].hurt);
        pop[i].heritage.push_front(pop[i].energy); 
        pop[i].h_count++; // "indica a proxima posicao"

        pop[i].heritage.pop_back();

        pop[i].average_energy = 0;
        for(j=0; j<HERITAGE; j++){
            pop[i].average_energy = pop[i].average_energy + pop[i].heritage[j];
        }
        pop[i].average_energy = pop[i].average_energy/HERITAGE;
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
