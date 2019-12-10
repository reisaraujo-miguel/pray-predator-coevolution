#define GUI_ON 1

int WAIT = 1;

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <deque>

#include <omp.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "game.h"

using namespace std;
using namespace cv;

const char *environment = "Predator-Prey Coevolution";
const char *arq1 = "./data/wonderers.txt";
const char *arq2 = "./data/carnivores.txt";

Type matrix[YSIZE][XSIZE]; 

vector<plants> plants_pop;
vector<population> wonderers;
vector<population> carnivores; 

int COUNT = 0;

bool set_opencv = false;


int main(int argc, char** argv){
    srand(time(0));

    initialize_matrix(matrix);
    initialize_wonderers(wonderers,matrix);
    //import_wonderers(wonderers,matrix);
    initialize_plants(plants_pop,matrix);
    initialize_carnivores(carnivores,matrix);
    //import_carnivores(carnivores,matrix);

    int size = wonderers.size();

    Mat frame;

    switch (GUI_ON)
    {
    case 1:
        
        set_opencv = true;
        namedWindow(environment, WINDOW_AUTOSIZE );
        moveWindow(environment, 0, 0);
        frame = print_img(wonderers,plants_pop,carnivores);
        imshow(environment, frame);

        while(true){
            int k = waitKey(1);
            if(k == 10) // if ENTER
                break;
            else if(k == 27) // if ESC
                goto end;
        }

    default:
        break;
    }
    
    printf("%d\n",COUNT);
    FILE* Arq1;
    Arq1 = fopen(arq1,"a+");
    int s;
    fprintf(Arq1,"\n%d\n",COUNT);
    fprintf(Arq1,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight speed health hurt energy\n");
    for(s=0; s<size; s++){
        fprintf(Arq1,"(%2d) %2d %2d %2d %2d %2d %2d %2d\n",s,wonderers[s].plant_const, wonderers[s].plant_weight, wonderers[s].wond_const, wonderers[s].wond_weight, wonderers[s].carn_const, wonderers[s].carn_weight, wonderers[s].speed);
    }
    FILE* Arq2;
    Arq2 = fopen(arq2,"a+");
    fprintf(Arq2,"\n%d\n",COUNT);
    fprintf(Arq2,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight speed energy\n");
    for(s=0; s<size; s++){
        fprintf(Arq2,"(%2d) %2d %2d %2d %2d %2d %2d %2d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].speed);
    }
    COUNT++;

    while(1){

        new_plants(plants_pop,matrix);

        /////////////////////////////// GENETICALLY DETERMINED ROTATION /////////////////////////////////////////
        
        int i;
        size = wonderers.size();
        //#pragma omp parallel for private(i) 
        for(i=0; i<size; i++){
            genetic_rotation(wonderers, i);
        }

        size = carnivores.size();
        //#pragma omp parallel for private(i) 
        for(i=0; i<size; i++){
            genetic_rotation(carnivores, i);
        }
        
        ///////////////////////////////////////// MATE //////////////////////////////////////////////////////
        
        if(COUNT%MATING_INTERVAL == 0){
            
                printf("%d\n",COUNT/MATING_INTERVAL);

                fclose(Arq1);
                Arq1 = fopen(arq1,"a+");
                fclose(Arq2);
                Arq2 = fopen(arq2,"a+");
                int s;
                s = wonderers.size();
                fprintf(Arq1,"\n%d\n",COUNT/MATING_INTERVAL);
                for(s=0; s<size; s++){
                    fprintf(Arq1,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d %2d Energy:%d\n",s,wonderers[s].plant_const, wonderers[s].plant_weight, wonderers[s].wond_const, wonderers[s].wond_weight, wonderers[s].carn_const, wonderers[s].carn_weight, wonderers[s].speed, wonderers[s].health, wonderers[s].hurt, ((HEALTH_CONST*wonderers[s].health)-(HURT_CONST*wonderers[s].hurt)));
                }

            

                s = carnivores.size();
                fprintf(Arq2,"\n%d\n",COUNT/MATING_INTERVAL);
                for(s=0; s<size; s++){
                    fprintf(Arq2,"(%2d) %2d %2d %2d %2d %2d %2d %2d Energy:%d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].speed, carnivores[s].energy);
                }

            elitism_heritage(wonderers,matrix);
            //tournament(wonderers,matrix);
            carnivores_elitism_heritage(carnivores,matrix);
            //carnivores_tournament(carnivores,matrix);
            new_plants(plants_pop,matrix);
        }

        ///////////////////////////////////////// MOVE //////////////////////////////////////////////////////
        
        move_wonderers(wonderers,matrix);
        move_carnivores(carnivores,matrix);

        switch (GUI_ON)
        {
        case 1:

            if(COUNT >= 0*MATING_INTERVAL){

                if(set_opencv == false){
                    namedWindow(environment, WINDOW_AUTOSIZE );
                    moveWindow(environment, 0, 0);
                    set_opencv = true;
                }

                frame = print_img(wonderers,plants_pop,carnivores);
                imshow(environment, frame);

                int k = waitKey(WAIT);
                if(k == 27) // if ESC
                    goto end;
                if(k == 32){ // if SPACE    
                    FILE* Arq3;
                    Arq3 = fopen("./data/real_time_data_wonderes.txt","a+");
                    int s;
                    s = wonderers.size();
                    fprintf(Arq3,"\n%d\n",COUNT/MATING_INTERVAL);
                    fprintf(Arq3,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight speed health hurt energy\n");
                    for(s=0; s<size; s++){
                        wonderers[s].energy = (HEALTH_CONST*wonderers[s].health) - (HURT_CONST*wonderers[s].hurt);
                        fprintf(Arq3,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n",s,wonderers[s].plant_const, wonderers[s].plant_weight, wonderers[s].wond_const, wonderers[s].wond_weight, wonderers[s].carn_const, wonderers[s].carn_weight, wonderers[s].speed, wonderers[s].health, wonderers[s].hurt, wonderers[s].energy);
                    }
                    fclose(Arq3);

                    Arq3 = fopen("./data/real_time_data_carnivores.txt","a+");
                    s = carnivores.size();
                    fprintf(Arq3,"\n%d\n",COUNT/MATING_INTERVAL);
                    fprintf(Arq3,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight speed energy\n");
                    for(s=0; s<size; s++){
                        fprintf(Arq3,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].speed, carnivores[s].energy);
                    }
                    fclose(Arq3);
                }
                if(k == 82){ // if ARROW UP (speed up)
                    if(WAIT > 1)
                        WAIT--;
                    printf("%d miliseconds\n",WAIT);
                }
                if(k == 84){ // IF ARROW DOWN (slow down)
                    WAIT++;
                    printf("%d miliseconds\n",WAIT);
                }
            }
        default:
            break;
        }
        
        COUNT++;
    }

    end:
    destroyWindow(environment);


    return 0;
}

