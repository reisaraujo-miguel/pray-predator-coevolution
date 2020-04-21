
#define GUI_ON 1

/**************************************************************************************************************
PROBLEMS:

* SEARCH HEIGHT GENE
    * do not allow it to be negative, set restrictions

* SLOW PROCESSING PROBLEM
    The problem was mainly on the screen size, what to do:
    * keep matrix small and decrease the individual's size instead o increasing matrix
    * dissociate processing and GUI matrix, then just expand the former when passing it to the later
    * PARALLELIZE the program (TO DO!!!)
    Will taking the rest of the division of the angle by 2*PI slow down the process? Or
    is it worthwhile compared to the cost of computing the Sin and Cos of very large angles?:
    * not possible to compute the rest of division by floating point number;

* AVERAGE PROCESS
    The weight variables were constantly decreasing because of cross over's average process, what to do:
    * when taking the average define a threshold to determine rounding up or down (TO DO!!!)
    * define mutating up probability as greater then mutating down probability

* HURT AND HEALTH SCORES
    When an herbivore eats the plant dies out, so it only gets one point at a time, but when it bumps
    into a carnivore, the carnivore stays there, and it looses one point per frame, as long as the carnivore
    is on its path, the same applies to when the herbivore is under a carnivore's chase/atack. Therefore
    hurt scores were much greater the health scores. What to do:
    * define an instinctive reaction of turning away from the predator, similarly to a REFLEX ARC
    * work with a PARETO CURVE varying the values of the multiplicative constants HEALTH_CONST and HURT_CONST
    * slowly fading plants that don't die out imediatly, they could have a life variable that diminishes
      at each attack but when the plant isn't under attack anymore slowly increases per frame (TO DO!!!)

* NEGATIVE WEIGHTS
    Negative weights disrupt the weighted average process, what to do:
    * set an inferior limit that can't be extrapolated through mutation OR
    * take the weights module at average process (TO DO!!!) 

* ARQUIVE MANAGING
    * stop opening and closing files all the time, use fflush instead to save and update file (TO DO!!!)

* NAN ANGLES
    * look for causes instead of handling the consequences (TO DO!!!)

IDEAS:

* height dependent weights when determining rotation, will them prioritize what is closer to them?

* set a limit height for bfs, look at everything inside those limits or keep looking only
  at the first obstacle of each type?

* pheromones

* energy x speed balance, high speeds consume energy

* VARIABLE MUTATION
    * analyse fitness average over different number of generations, and evaluate discrepancies,
      this might be a way of reducing noise influence over the fitness scores, allowing the definition
      of a stagnation point and consequently permiting the employemnt of variable mutation rates 

* MUTATION CURVE
    *

* develop the possibility of inserting a desired individual whenever I want

* REFLEX ARC
    * evolving reflex arc

OBSERVATIONS:

* by setting HEALTH_CONST to 0 the individuals learn quickly to deviate and not get hurt

* THE PROBLEM OF PREDATORS KILLING PLANTS (altough whithout getting any points): the plants weren't
  obstacles, they simply got out of the way, I imagine this shall influence significativelly predator's evolution

****************************************************************************************************************/

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

