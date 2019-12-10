#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <deque>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "global.h"

using namespace std;
using namespace cv;


Mat print_wanderers(std::vector<population> &pop){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int x_pixel, y_pixel, x, y;
    extern int COUNT;

    Mat image(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0,0,0));
    memset(image.data, 255, IMG_WIDTH*IMG_HEIGHT*3*sizeof(char));

    char label[30];
    sprintf(label, "%d", COUNT);

    putText(image, label, Point(15,20), FONT_HERSHEY_SIMPLEX, 0.6, CV_RGB(0,0,0), 1);
    // font size = *10 pixels

    float x_to_pixel = (float)IMG_WIDTH/(float)(XSIZE);
    float y_to_pixel = (float)IMG_HEIGHT/(float)(YSIZE);
    
    int i, size;
    size = pop.size();
    for(i=0; i<size; i++){
        x_pixel =  (int)((pop[i].x)*(x_to_pixel));
        y_pixel =  (int)((pop[i].y)*(y_to_pixel));
        if(x_pixel >= 0 && x_pixel <= IMG_WIDTH && y_pixel >= 0 && y_pixel <= IMG_HEIGHT){
            if(i == 0)
                circle(image, Point(x_pixel,y_pixel), 10, blue, -1,  LINE_8 );
            else
                circle(image, Point(x_pixel,y_pixel), 10, pink, -1,  LINE_8 );
            

            line (image, Point(x_pixel+(cos(pop[i].angle)*10),y_pixel+(sin(pop[i].angle)*10)), Point(x_pixel+(cos(pop[i].angle)*30),y_pixel+(sin(pop[i].angle)*30)), Scalar(0,0,0), 1, LINE_8);
            
        }
 
    }

    return image;
}

Mat print_img(std::vector<population> &wand_pop, std::vector<plants> &plants_pop, std::vector<population> &carn_pop){

    Vec3b red = Vec3b(0,0,255); 
    Vec3b green = Vec3b(0,255,0); 
    Vec3b blue = Vec3b(255,0,0); 
    Vec3b pink = Vec3b(77,0,230);
    Vec3b black = Vec3b(0,0,0);
    Vec3b orange = Vec3b(0,108,238);
    Vec3b violet = Vec3b(200,0,119);
    Vec3b yellow = Vec3b(0,184,196);

    int x_pixel, y_pixel, x, y;
    extern int COUNT;

    Mat image(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0,0,0));
    memset(image.data, 255, IMG_WIDTH*IMG_HEIGHT*3*sizeof(char)); // white

    char label[30];
    sprintf(label, "%d", COUNT/MATING_INTERVAL); // number of generations

    putText(image, label, Point(15,20), FONT_HERSHEY_SIMPLEX, 0.6, CV_RGB(0,0,0), 1);

    float x_to_pixel = (float)IMG_WIDTH/(float)(XSIZE);
    float y_to_pixel = (float)IMG_HEIGHT/(float)(YSIZE);
    
    int i, size;
    size = wand_pop.size();
    for(i=0; i<size; i++){
        x_pixel =  (int)((wand_pop[i].x)*(x_to_pixel));
        y_pixel =  (int)((wand_pop[i].y)*(y_to_pixel));
        if(x_pixel >= 0 && x_pixel <= IMG_WIDTH && y_pixel >= 0 && y_pixel <= IMG_HEIGHT){
            circle(image, Point(x_pixel,y_pixel), y_to_pixel*RADIUS_WANDER, wand_pop[i].color, -1,  LINE_8 );
            //sprintf(label, "%d", i);
            //putText(image, label, Point(x_pixel/*-5*/,y_pixel/*+5*/), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0,0,0), 1);
            line (image, Point(x_pixel+(cos(wand_pop[i].angle)*y_to_pixel*RADIUS_WANDER),y_pixel+(sin(wand_pop[i].angle)*y_to_pixel*RADIUS_WANDER)), Point(x_pixel+(cos(wand_pop[i].angle)*3*y_to_pixel*RADIUS_WANDER),y_pixel+(sin(wand_pop[i].angle)*3*y_to_pixel*RADIUS_WANDER)), Scalar(0,0,0), 1, LINE_8);
        }
    }

    size = carn_pop.size();
    for(i=0; i<size; i++){
        x_pixel =  (int)((carn_pop[i].x)*(x_to_pixel));
        y_pixel =  (int)((carn_pop[i].y)*(y_to_pixel));
        if(x_pixel >= 0 && x_pixel <= IMG_WIDTH && y_pixel >= 0 && y_pixel <= IMG_HEIGHT){
            circle(image, Point(x_pixel,y_pixel), y_to_pixel*RADIUS_CARN, carn_pop[i].color, -1,  LINE_8 );
            //sprintf(label, "%d", i);
            //putText(image, label, Point(x_pixel/*-5*/,y_pixel/*+5*/), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0,0,0), 1);
            line (image, Point(x_pixel+(cos(carn_pop[i].angle)*y_to_pixel*RADIUS_CARN),y_pixel+(sin(carn_pop[i].angle)*y_to_pixel*RADIUS_CARN)), Point(x_pixel+(cos(carn_pop[i].angle)*3*y_to_pixel*RADIUS_CARN),y_pixel+(sin(carn_pop[i].angle)*3*y_to_pixel*RADIUS_CARN)), Scalar(0,0,0), 1, LINE_8);
        }
    }

    size = plants_pop.size();
    for(i=0; i<size; i++){
        x_pixel =  (int)((plants_pop[i].x)*(x_to_pixel));
        y_pixel =  (int)((plants_pop[i].y)*(y_to_pixel));
        if(x_pixel >= 0 && x_pixel <= IMG_WIDTH && y_pixel >= 0 && y_pixel <= IMG_HEIGHT){
            circle(image, Point(x_pixel,y_pixel), y_to_pixel*RADIUS_PLANTS, plants_pop[i].color, -1,  LINE_8 );
        }
    }

    return image;
}