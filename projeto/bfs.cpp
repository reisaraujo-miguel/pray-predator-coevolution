#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <deque>

#include "game.h"

using namespace std;


#include <iostream> 
#include <queue>
#include <utility>  // pair
#include <time.h>
using namespace std;

/* PAIR

The pair container is a simple container consisting of two data elements or objects.

The first element is referenced as ‘first’ and the second element as ‘second’ 
and the order is fixed (first, second).

*/ 
const int dir[4][2] = {{1,0},
                       {-1,0},
                       {0,1},
                       {0,-1}}; //desce, sobe, direita, esquerda (0,0 sup esquerdo)

void first_obstacle_bfs(int startx, int starty, int* xobs, int* yobs, int* type_obs){

    extern Type matrix[YSIZE][XSIZE];

    queue <pair<int,int>> fila;

    bool visited[YSIZE][XSIZE];   // stores whether the poition has been visited or not
    //int altura[YSIZE][XSIZE];     // stores the search height of position
    int nextX, nextY;

    fila.push(make_pair(startx, starty));

    // THIS WAS THE PROBLEM!!! visited matrix was adultered
    int i,j;
    for(i=0; i<YSIZE; i++){
        for(j=0; j<XSIZE; j++){
            visited[i][j] = false;
        }
    }


    visited[starty][startx] = true;
    //altura[starty][startx] = 0;


    while(!fila.empty()){
        // Pega a frente da fila
        pair <int, int> curr = fila.front();    // curr -> current
        fila.pop();

        // Vai para as 4 direções
        for(int i=0;i<4;i++){
            // Próximo Y
            nextY = dir[i][0] + curr.second;
            // Próximo X
            nextX = dir[i][1] + curr.first;
            
            // Se não estiver na matrix, pula pro próximo
            if(nextX < 0 || nextY < 0 || nextX >= XSIZE || nextY >= YSIZE)
                continue;   // forces execution of next iteration
   
            // Se não foi visitado, coloca na fila
            if(!visited[nextY][nextX]){
                if(matrix[nextY][nextX] != N){   // changed from <!= NULL> to <==P>
                    *xobs = nextX;
                    *yobs = nextY;
                    *type_obs = matrix[nextY][nextX];
                    return;
                }
                fila.push(make_pair(nextX, nextY));
                // Marca como visitado
                visited[nextY][nextX] = true;
                //altura[nextY][nextX] = altura[curr.second][curr.first] + 1;
            }
        }
    }
    *xobs = 0;
    *yobs = 0;
    *type_obs = 0;



}

void first_plant_bfs(int startx, int starty, int* xobs, int* yobs){

    extern Type matrix[YSIZE][XSIZE];

    queue <pair<int,int>> fila;

    bool visited[YSIZE][XSIZE];   // stores whether the poition has been visited or not
    //int altura[YSIZE][XSIZE];     // stores the search height of position
    int nextX, nextY;

    fila.push(make_pair(startx, starty));

    // THIS WAS THE PROBLEM!!! visited matrix was adultered
    int i,j;
    for(i=0; i<YSIZE; i++){
        for(j=0; j<XSIZE; j++){
            visited[i][j] = false;
        }
    }


    visited[starty][startx] = true;
    //altura[starty][startx] = 0;


    while(!fila.empty()){
        // Pega a frente da fila
        pair <int, int> curr = fila.front();    // curr -> current
        fila.pop();

        // Vai para as 4 direções
        for(int i=0;i<4;i++){
            // Próximo Y
            nextY = dir[i][0] + curr.second;
            // Próximo X
            nextX = dir[i][1] + curr.first;
            
            // Se não estiver na matrix, pula pro próximo
            if(nextX < 0 || nextY < 0 || nextX >= XSIZE || nextY >= YSIZE)
                continue;   // forces execution of next iteration
   
            // Se não foi visitado, coloca na fila
            if(!visited[nextY][nextX]){
                if(matrix[nextY][nextX] == P){   // changed from <!= NULL> to <==P>
                    *xobs = nextX;
                    *yobs = nextY;
                    return;
                }
                fila.push(make_pair(nextX, nextY));
                // Marca como visitado
                visited[nextY][nextX] = true;
                //altura[nextY][nextX] = altura[curr.second][curr.first] + 1;
            }
        }
    }
    *xobs = 0;
    *yobs = 0;
}

void first_wonderer_bfs(int startx, int starty, int* xobs, int* yobs){

    extern Type matrix[YSIZE][XSIZE];

    queue <pair<int,int>> fila;

    bool visited[YSIZE][XSIZE];   // stores whether the poition has been visited or not
    //int altura[YSIZE][XSIZE];     // stores the search height of position
    int nextX, nextY;

    fila.push(make_pair(startx, starty));

    // THIS WAS THE PROBLEM!!! visited matrix was adultered
    int i,j;
    for(i=0; i<YSIZE; i++){
        for(j=0; j<XSIZE; j++){
            visited[i][j] = false;
        }
    }


    visited[starty][startx] = true;
    //altura[starty][startx] = 0;


    while(!fila.empty()){
        // Pega a frente da fila
        pair <int, int> curr = fila.front();    // curr -> current
        fila.pop();

        // Vai para as 4 direções
        for(int i=0;i<4;i++){
            // Próximo Y
            nextY = dir[i][0] + curr.second;
            // Próximo X
            nextX = dir[i][1] + curr.first;
            
            // Se não estiver na matrix, pula pro próximo
            if(nextX < 0 || nextY < 0 || nextX >= XSIZE || nextY >= YSIZE)
                continue;   // forces execution of next iteration
   
            // Se não foi visitado, coloca na fila
            if(!visited[nextY][nextX]){
                if(matrix[nextY][nextX] == W){   // changed from <!= NULL> to <==P>
                    *xobs = nextX;
                    *yobs = nextY;
                    return;
                }
                fila.push(make_pair(nextX, nextY));
                // Marca como visitado
                visited[nextY][nextX] = true;
                //altura[nextY][nextX] = altura[curr.second][curr.first] + 1;
            }
        }
    }
    *xobs = 0;
    *yobs = 0;
}


void obstacles_bfs(int startx, int starty, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn){

    // stores whether obstacle was already found or not
    bool plant = false;
    bool wond = false;
    bool carn = false;

    extern Type matrix[YSIZE][XSIZE];

    queue <pair<int,int>> fila;

    bool visited[YSIZE][XSIZE];   // stores whether the position has been visited or not
    //int altura[YSIZE][XSIZE];     // stores the search height of position
    int nextX, nextY;

    fila.push(make_pair(startx, starty));

    int i,j;
    for(i=0; i<YSIZE; i++){
        for(j=0; j<XSIZE; j++){
            visited[i][j] = false;
        }
    }

    visited[starty][startx] = true;
    //altura[starty][startx] = 0;


    while(!fila.empty()){
        // pop off the queue's front
        pair <int, int> curr = fila.front();    // curr -> current
        fila.pop();

        // 4 direction
        for(int i=0;i<4;i++){
            // next Y
            nextY = dir[i][0] + curr.second;
            // next X
            nextX = dir[i][1] + curr.first;
            
            // if it isn't on the matrix...
            if(nextX < 0 || nextY < 0 || nextX >= XSIZE || nextY >= YSIZE)
                continue;   // forces execution of next iteration
   
            // if it wasn't visited, puts on the matrix
            if(!visited[nextY][nextX]){
                if(matrix[nextY][nextX] != N){
                    if((matrix[nextY][nextX] == P) && (plant == false)){
                        *xplant = nextX;
                        *yplant = nextY;
                        plant = true;

                        if(wond == true && carn == true){
                            return;
                        }
                    }
                    if((matrix[nextY][nextX] == W) && (wond == false)){   
                        *xwond = nextX;
                        *ywond = nextY;
                        wond = true;
                        
                        if(plant == true && carn == true){
                            return;
                        }
                    }
                    if((matrix[nextY][nextX] == C) && (carn == false)){   
                        *xcarn = nextX;
                        *ycarn = nextY;
                        carn = true;
                        
                        if(plant == true && wond == true){
                            return;
                        }
                    }
                }
                fila.push(make_pair(nextX, nextY));
                // marks as visited
                visited[nextY][nextX] = true;
                //altura[nextY][nextX] = altura[curr.second][curr.first] + 1;
            }
        }
    }
    
    *xwond = *ywond = *xplant = *yplant = *xcarn = *ycarn = 0;
}

