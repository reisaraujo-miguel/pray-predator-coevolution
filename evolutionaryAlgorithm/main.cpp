
#define GUI_ON 1

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

//--------------- DYNAMIC MUTATION ---------------//

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

//-----------------------------------------------//



int COUNT = 0;

int main(int argc, char** argv){

    /*
    WARNING:
    The updating and sorting of the individual's heritage, is happening outside mating block (function callings
    commented out) for plotting purposes!
    */

    plotter_header();

    srand(time(0));

    initialize_matrix(matrix);
    initialize_wanderers(wanderers,matrix);
    //import_wanderers(wanderers,matrix);
    initialize_plants(plants_pop,matrix);
    initialize_carnivores(carnivores,matrix);
    initialize_historic(wanderers_historic, carnivores_historic);
    //import_carnivores(carnivores,matrix);

    int size = wanderers.size();

    if(initialize_GUI(wanderers,carnivores,plants_pop) == 0){
        return 0;
    }

    simulation_data_header(wanderers,carnivores,COUNT);

    COUNT++;

    while(1){

        //time_t start,end;
        //start = time(NULL);

        new_plants(plants_pop,matrix);

        
        // size = plants_pop.size();
        // if(size == 0)
        //     initialize_plants(plants_pop,matrix);
        
        ///////////////////////////////////////// MATE //////////////////////////////////////////////////////
        
        if(COUNT%MATING_INTERVAL == 0){

            // ------------------------------------------ //
            // The best individual considering the heritage
            // is put on the 0th position, and the worst on 
            // the last position

            best_wonderer_heritage(wanderers);
            best_carnivore_heritage(carnivores);

            // ------------------------------------------ //
            update_simulation_data(wanderers, carnivores, COUNT);
            update_plotter_data(wanderers, carnivores, COUNT);

                        

            if(COUNT/MATING_INTERVAL > GENERATION){
                close_files();
                close_GUI();
                return 0;
            }
                

            elitism_heritage(wanderers,matrix);
            //tournament(wanderers,matrix);
            carnivores_elitism_heritage(carnivores,matrix);
            //carnivores_tournament(carnivores,matrix);

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

        if(refresh_GUI(wanderers, carnivores, plants_pop, COUNT) == 0){
            return 0;
        }

        
        COUNT++;
        //end = time(NULL);
        //printf("%lf\n",difftime(end,start));
    }

    return 0;
}

