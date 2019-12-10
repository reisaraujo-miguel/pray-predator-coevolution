#define GUI_ON 1

int WAIT = 1;   // how many seconds each frame lasts, in case the GUI is turned on

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

#include "global.h"

using namespace std;
using namespace cv;

const char *environment = "Predator-Prey Coevolution";
const char *arq1 = "./data/wanderers.txt";
const char *arq2 = "./data/carnivores.txt";

Type matrix[YSIZE][XSIZE]; 

vector<plants> plants_pop;
vector<population> wanderers;
vector<population> carnivores; 

int COUNT = 0;

bool set_opencv = false;


int main(int argc, char** argv){
    srand(time(0));

    initialize_matrix(matrix);
    initialize_wanderers(wanderers,matrix);
    //import_wanderers(wanderers,matrix);
    initialize_plants(plants_pop,matrix);
    initialize_carnivores(carnivores,matrix);
    //import_carnivores(carnivores,matrix);

    int size = wanderers.size();

    Mat frame;

    switch (GUI_ON)
    {
    case 1:
        
        set_opencv = true;
        namedWindow(environment, WINDOW_AUTOSIZE );
        moveWindow(environment, 0, 0);
        frame = print_img(wanderers,plants_pop,carnivores);
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
        fprintf(Arq1,"(%2d) %2d %2d %2d %2d %2d %2d %2d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].speed);
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
        size = wanderers.size();
        //#pragma omp parallel for private(i) 
        for(i=0; i<size; i++){
            genetic_rotation(wanderers, i);
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
                s = wanderers.size();
                fprintf(Arq1,"\n%d\n",COUNT/MATING_INTERVAL);
                for(s=0; s<size; s++){
                    fprintf(Arq1,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d %2d Energy:%d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].speed, wanderers[s].health, wanderers[s].hurt, ((HEALTH_CONST*wanderers[s].health)-(HURT_CONST*wanderers[s].hurt)));
                }

            

                s = carnivores.size();
                fprintf(Arq2,"\n%d\n",COUNT/MATING_INTERVAL);
                for(s=0; s<size; s++){
                    fprintf(Arq2,"(%2d) %2d %2d %2d %2d %2d %2d %2d Energy:%d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].speed, carnivores[s].energy);
                }

            elitism_heritage(wanderers,matrix);
            //tournament(wanderers,matrix);
            carnivores_elitism_heritage(carnivores,matrix);
            //carnivores_tournament(carnivores,matrix);
            new_plants(plants_pop,matrix);
        }

        ///////////////////////////////////////// MOVE //////////////////////////////////////////////////////
        
        move_wanderers(wanderers,matrix);
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

                frame = print_img(wanderers,plants_pop,carnivores);
                imshow(environment, frame);

                int k = waitKey(WAIT);
                if(k == 27) // if ESC
                    goto end;
                if(k == 32){ // if SPACE    
                    FILE* Arq3;
                    Arq3 = fopen("./data/real_time_data_wonderes.txt","a+");
                    int s;
                    s = wanderers.size();
                    fprintf(Arq3,"\n%d\n",COUNT/MATING_INTERVAL);
                    fprintf(Arq3,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight speed health hurt energy\n");
                    for(s=0; s<size; s++){
                        wanderers[s].energy = (HEALTH_CONST*wanderers[s].health) - (HURT_CONST*wanderers[s].hurt);
                        fprintf(Arq3,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].speed, wanderers[s].health, wanderers[s].hurt, wanderers[s].energy);
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

