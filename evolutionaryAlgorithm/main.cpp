// TURN SIMULATION INTERFACE ON-1 AND OFF-0
#define GUI_ON 0

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

Type matrix[YSIZE][XSIZE]; 

vector<plants> plants_pop;
vector<population> wanderers;
vector<population> carnivores;

// PUSH FRONT and POP BACK only:
deque<int> wanderers_historic;
deque<int> carnivores_historic; 

int average_wand_historic = 0;
int prev_average_wand_historic = 0;
int wand_deteriorate_count = 0;
bool dynamic_mute_wand = false;
int dynamic_wand_count = 0;

int average_carn_historic = 0;
int prev_average_carn_historic = 0;
int carn_deteriorate_count = 0;
bool dynamic_mute_carn = false;
int dynamic_carn_count = 0;

const char *environment = "Prey-Predator Coevolution";

int COUNT = 0;

int WAIT = 1;

bool set_opencv = false;


int main(int argc, char** argv){


                //------------PLOTTER DATA--------------//

                char plotterFileName[100];
                sprintf(plotterFileName, "./plotterData/%dgen_%dint_%dcarn_%dherb_%dplan_%dheritHerb_%dheritCarn_%dhealth_%dev.txt",GENERATION,MATING_INTERVAL,POP_CARN,POP_WANDER,POP_PLANTS,HERITAGE_WANDER,HERITAGE_CARN,HEALTH_CONST,AVERAGE_INTERVAL);
                const char *plotterData = plotterFileName;

                FILE *PlotterArq;
                PlotterArq = fopen(plotterData,"w+");
                fprintf(PlotterArq,"QtdHerbivores: %d\n",POP_WANDER);
                fprintf(PlotterArq,"QtdCarnivores: %d\n",POP_CARN);
                fprintf(PlotterArq,"QtdPlants: %d\n",POP_PLANTS);
                fprintf(PlotterArq,"QtdGenerations: %d\n",GENERATION);
                fprintf(PlotterArq,"HealthWeight: %d\n",HEALTH_CONST);
                fprintf(PlotterArq,"HurtWeight: %d\n",HURT_CONST);
                fprintf(PlotterArq,"FramesPerGeneration: %d\n",MATING_INTERVAL);
                fprintf(PlotterArq,"HerbivoresHeritage: %d\n",HERITAGE_WANDER);
                fprintf(PlotterArq,"CarnivoresHeritage: %d\n",HERITAGE_WANDER);
                fprintf(PlotterArq,"EvaluationInterval: %d\n",AVERAGE_INTERVAL);
                fprintf(PlotterArq,"\n");

                //--------------------------------------//

    srand(time(0));

    initialize_matrix(matrix);
    initialize_wanderers(wanderers,matrix);
    //import_wanderers(wanderers,matrix);
    initialize_plants(plants_pop,matrix);
    initialize_carnivores(carnivores,matrix);
    initialize_historic(wanderers_historic, carnivores_historic);
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
            else if(k == 27){ // if ESC
                destroyWindow(environment);
                return 0;
                //goto end;
            }
        }

    default:
        break;
    }
                
                //----------------SIMULATION DATA---------------//

                char arq1FileName[100];
                char arq2FileName[100];
                sprintf(arq1FileName,"./data/wanderers_%dgen_%dint_%dcarn_%dherb_%dplan_%dheritHerb_%dheritCarn_%dhealth_%dev.txt",GENERATION,MATING_INTERVAL,POP_CARN,POP_WANDER,POP_PLANTS,HERITAGE_WANDER,HERITAGE_CARN,HEALTH_CONST,AVERAGE_INTERVAL);
                sprintf(arq2FileName,"./data/carnivores_%dgen_%dint_%dcarn_%dherb_%dplan_%dheritHerb_%dheritCarn_%dhealth_%devt.txt",GENERATION,MATING_INTERVAL,POP_CARN,POP_WANDER,POP_PLANTS,HERITAGE_WANDER,HERITAGE_CARN,HEALTH_CONST,AVERAGE_INTERVAL);
                const char *arq1 = arq1FileName;
                const char *arq2 = arq2FileName;


                printf("%d\n",COUNT);
                FILE* Arq1;
                Arq1 = fopen(arq1,"a+");
                int s;
                fprintf(Arq1,"\n%d\n",COUNT);
                fprintf(Arq1,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed health hurt energy\n");
                for(s=0; s<size; s++){
                    fprintf(Arq1,"(%2d) %2d %2d %2d %2d %2d %2d %d %d %2d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].height_limit, wanderers[s].height, wanderers[s].speed);
                }
                fflush(Arq1);
                FILE* Arq2;
                Arq2 = fopen(arq2,"a+");
                fprintf(Arq2,"\n%d\n",COUNT);
                fprintf(Arq2,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed energy\n");
                for(s=0; s<size; s++){
                    fprintf(Arq2,"(%2d) %2d %2d %2d %2d %2d %2d %d %d %2d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].height_limit, carnivores[s].height, carnivores[s].speed);
                }
                fflush(Arq2);
                //-----------------------------------------------//

    COUNT++;

    while(1){

        //time_t start,end;
        //start = time(NULL);

        new_plants(plants_pop,matrix);

/*
        size = plants_pop.size();
        if(size == 0)
            initialize_plants(plants_pop,matrix);
*/
        ///////////////////////////////////////// MATE //////////////////////////////////////////////////////
        
        if(COUNT%MATING_INTERVAL == 0){
            
                        size = wanderers.size();
                        fprintf(Arq1,"\n%d\n",(COUNT/MATING_INTERVAL)-1);
                        for(s=0; s<size; s++){
                            fprintf(Arq1,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d %d %d %2d Energy:%d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].height_limit, wanderers[s].height, wanderers[s].speed, wanderers[s].health, wanderers[s].hurt, ((HEALTH_CONST*wanderers[s].health)-(HURT_CONST*wanderers[s].hurt)));
                        }
                        fflush(Arq1);

                        size = carnivores.size();
                        fprintf(Arq2,"\n%d\n",(COUNT/MATING_INTERVAL)-1);
                        for(s=0; s<size; s++){
                            fprintf(Arq2,"(%2d) %2d %2d %2d %2d %2d %2d %d %d %2d Energy:%d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].height_limit, carnivores[s].height, carnivores[s].speed, carnivores[s].energy);
                        }
                        fflush(Arq2);

            // ------------------------------------------ //
            // The best individual considering the heritage
            // is put on the 0th position

            best_wonderer_heritage(wanderers);
            best_carnivore_heritage(carnivores);

            // ------------------------------------------ //

                        // ------------- PLOTTER DATA --------------- //
                        fprintf(PlotterArq,"GENERATION %d\n", ((COUNT/MATING_INTERVAL)-1));

                        fprintf(PlotterArq,"Herbivores:");
                        size = wanderers.size();
                        for(s=0; s<size; s++){
                            fprintf(PlotterArq," %d",((HEALTH_CONST*wanderers[s].health)-(HURT_CONST*wanderers[s].hurt)));
                        }
                        fprintf(PlotterArq,"\n");
                        fprintf(PlotterArq,"Health:");
                        size = wanderers.size();
                        for(s=0; s<size; s++){
                            fprintf(PlotterArq," %d",wanderers[s].health);
                        }
                        fprintf(PlotterArq,"\n");
                        fprintf(PlotterArq,"Hurt:");
                        size = wanderers.size();
                        for(s=0; s<size; s++){
                            fprintf(PlotterArq," %d",wanderers[s].hurt);
                        }
                        fprintf(PlotterArq,"\n");

                        fprintf(PlotterArq,"Carnivores:");
                        size = carnivores.size();
                        for(s=0; s<size; s++){
                            fprintf(PlotterArq," %d",carnivores[s].energy);
                        }
                        fprintf(PlotterArq,"\n");
                        fflush(PlotterArq);
                        // ------------------------------------------ //

            if(COUNT/MATING_INTERVAL > GENERATION){
                fclose(PlotterArq);
                fclose(Arq1);
                fclose(Arq2);
                destroyWindow(environment);
                return 0;
                //goto end;
            }
                

            elitism_heritage(wanderers,matrix);
            //tournament(wanderers,matrix);

            carnivores_elitism_heritage(carnivores,matrix);
            //carnivores_tournament(carnivores,matrix);

                        // ---------------- DYNAMIC MUTATION ------------- //
                        printf("Generation:%d\n",COUNT/MATING_INTERVAL);
                        printf("Wanderers => prev_average:%d average:%d deterioration:%d dynamic_mutation:%d regressive_count:%d\n",prev_average_wand_historic,average_wand_historic,wand_deteriorate_count,dynamic_mute_wand,dynamic_wand_count);
                        printf("Carnivores => prev_average:%d average:%d deterioration:%d dynamic_mutation:%d regressive_count:%d\n\n",prev_average_carn_historic,average_carn_historic,carn_deteriorate_count,dynamic_mute_carn,dynamic_carn_count);
                        // ----------------------------------------------- //

            new_plants(plants_pop,matrix);

            printf("%d\n",COUNT/MATING_INTERVAL);
        }

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
                    if(k == 27){ // if ESC
                        fclose(PlotterArq);
                        fclose(Arq1);
                        fclose(Arq2);
                        destroyWindow(environment);
                        return 0;
                        //goto end;
                    }
                    if(k == 32){ // if SPACE    /// SALVAR em um arquivo diferente, para poder acessar em tempo de execução
                        FILE* Arq5;
                        Arq5 = fopen("./data/real_time_data_wonderes.txt","a+");
                        int s;
                        s = wanderers.size();
                        fprintf(Arq5,"\n%d\n",COUNT/MATING_INTERVAL);
                        fprintf(Arq5,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed health hurt energy\n");
                        for(s=0; s<size; s++){
                            wanderers[s].energy = (HEALTH_CONST*wanderers[s].health) - (HURT_CONST*wanderers[s].hurt);
                            fprintf(Arq5,"(%2d) %2d %2d %2d %2d %2d %2d %2d %2d %d %d %2d Energy:%d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].height_limit, wanderers[s].height, wanderers[s].speed, wanderers[s].health, wanderers[s].hurt, ((HEALTH_CONST*wanderers[s].health)-(HURT_CONST*wanderers[s].hurt)));
                        }
                        fclose(Arq5);

                        Arq5 = fopen("./data/real_time_data_carnivores.txt","a+");
                        s = carnivores.size();
                        fprintf(Arq5,"\n%d\n",COUNT/MATING_INTERVAL);
                        fprintf(Arq5,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed energy\n");
                        for(s=0; s<size; s++){
                            fprintf(Arq5,"(%2d) %2d %2d %2d %2d %2d %2d %d %d %2d Energy:%d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].height_limit, carnivores[s].height, carnivores[s].speed, carnivores[s].energy);
                        }
                        fclose(Arq5);
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

    return 0;
}

