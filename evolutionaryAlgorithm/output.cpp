#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "game.h"

FILE *PlotterArq;
FILE* Arq1;
FILE* Arq2;


void plotter_header(){

    char plotterFileName[100];
    sprintf(plotterFileName, "./plotterData/%dgen_%dint_%dcarn_%dherb_%dplan_%dheritHerb_%dheritCarn_%dhealth_%dev(%d).txt",GENERATION,MATING_INTERVAL,POP_CARN,POP_WANDER,POP_PLANTS,HERITAGE_WANDER,HERITAGE_CARN,HEALTH_CONST,AVERAGE_INTERVAL,FILE_NUMBER);
    const char *plotterData = plotterFileName;

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
    if(DYNAMIC_PROPORTION != 1)
        fprintf(PlotterArq,"EvaluationInterval: %d\n",AVERAGE_INTERVAL);
    if(DYNAMIC_PROPORTION == 1)
        fprintf(PlotterArq,"EvaluationInterval: -1\n");
    fprintf(PlotterArq,"\n");

    fflush(PlotterArq);
}

void simulation_data_header(vector<population> wanderers, vector<population> carnivores, int COUNT){

    int size, s;

    char arq1FileName[100];
    char arq2FileName[100];
    sprintf(arq1FileName,"./data/wanderers_%dgen_%dint_%dcarn_%dherb_%dplan_%dheritHerb_%dheritCarn_%dhealth_%dev(%d).txt",GENERATION,MATING_INTERVAL,POP_CARN,POP_WANDER,POP_PLANTS,HERITAGE_WANDER,HERITAGE_CARN,HEALTH_CONST,AVERAGE_INTERVAL,FILE_NUMBER);
    sprintf(arq2FileName,"./data/carnivores_%dgen_%dint_%dcarn_%dherb_%dplan_%dheritHerb_%dheritCarn_%dhealth_%dev(%d).txt",GENERATION,MATING_INTERVAL,POP_CARN,POP_WANDER,POP_PLANTS,HERITAGE_WANDER,HERITAGE_CARN,HEALTH_CONST,AVERAGE_INTERVAL,FILE_NUMBER);
    const char *arq1 = arq1FileName;
    const char *arq2 = arq2FileName;


    printf("%d\n",COUNT);

    Arq1 = fopen(arq1,"w+");
    fprintf(Arq1,"QtdHerbivores: %d\n",POP_WANDER);
    fprintf(Arq1,"QtdCarnivores: %d\n",POP_CARN);
    fprintf(Arq1,"QtdPlants: %d\n",POP_PLANTS);
    fprintf(Arq1,"QtdGenerations: %d\n",GENERATION);
    fprintf(Arq1,"HealthWeight: %d\n",HEALTH_CONST);
    fprintf(Arq1,"HurtWeight: %d\n",HURT_CONST);
    fprintf(Arq1,"FramesPerGeneration: %d\n",MATING_INTERVAL);
    fprintf(Arq1,"HerbivoresHeritage: %d\n",HERITAGE_WANDER);
    fprintf(Arq1,"CarnivoresHeritage: %d\n",HERITAGE_WANDER);
    if(DYNAMIC_PROPORTION != 1)
        fprintf(Arq1,"EvaluationInterval: %d\n",AVERAGE_INTERVAL);
    if(DYNAMIC_PROPORTION == 1)
        fprintf(Arq1,"EvaluationInterval: -1\n");    
    fprintf(Arq1,"\n");
    fprintf(Arq1,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed health hurt energy\n");
    fflush(Arq1);
    
    Arq2 = fopen(arq2,"w+");
    fprintf(Arq2,"QtdHerbivores: %d\n",POP_WANDER);
    fprintf(Arq2,"QtdCarnivores: %d\n",POP_CARN);
    fprintf(Arq2,"QtdPlants: %d\n",POP_PLANTS);
    fprintf(Arq2,"QtdGenerations: %d\n",GENERATION);
    fprintf(Arq2,"HealthWeight: %d\n",HEALTH_CONST);
    fprintf(Arq2,"HurtWeight: %d\n",HURT_CONST);
    fprintf(Arq2,"FramesPerGeneration: %d\n",MATING_INTERVAL);
    fprintf(Arq2,"HerbivoresHeritage: %d\n",HERITAGE_WANDER);
    fprintf(Arq2,"CarnivoresHeritage: %d\n",HERITAGE_WANDER);
    if(DYNAMIC_PROPORTION != 1)
        fprintf(Arq2,"EvaluationInterval: %d\n",AVERAGE_INTERVAL);
    if(DYNAMIC_PROPORTION == 1)
        fprintf(Arq2,"EvaluationInterval: -1\n"); 
    fprintf(Arq2,"\n");
    fprintf(Arq2,"(index) plant_const plant_weight wond_const wond_weight carn_const carn_weight height_bool height_limit speed energy\n");
    fflush(Arq2);

}

void update_simulation_data(vector<population> wanderers, vector<population> carnivores, int COUNT){
    
    int size, s;

    size = wanderers.size();
    fprintf(Arq1,"\n%d\n",(COUNT/MATING_INTERVAL)-1);
    for(s=0; s<size; s++){
        fprintf(Arq1,"(%d) %d %d %d %d %d %d %d %d %d %d %d Energy: %d\n",s,wanderers[s].plant_const, wanderers[s].plant_weight, wanderers[s].wond_const, wanderers[s].wond_weight, wanderers[s].carn_const, wanderers[s].carn_weight, wanderers[s].height_limit, wanderers[s].height, wanderers[s].speed, wanderers[s].health, wanderers[s].hurt, ((HEALTH_CONST*wanderers[s].health)-(HURT_CONST*wanderers[s].hurt)));
    }
    fflush(Arq1);

    size = carnivores.size();
    fprintf(Arq2,"\n%d\n",(COUNT/MATING_INTERVAL)-1);
    for(s=0; s<size; s++){
        fprintf(Arq2,"(%d) %d %d %d %d %d %d %d %d %d Energy: %d\n",s,carnivores[s].plant_const, carnivores[s].plant_weight, carnivores[s].wond_const, carnivores[s].wond_weight, carnivores[s].carn_const, carnivores[s].carn_weight, carnivores[s].height_limit, carnivores[s].height, carnivores[s].speed, carnivores[s].energy);
    }
    fflush(Arq2);
}

void update_plotter_data(vector<population> wanderers, vector<population> carnivores, int COUNT){
    int size, s;

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

}

void close_files(){
    fclose(PlotterArq);
    fclose(Arq1);
    fclose(Arq2);
}