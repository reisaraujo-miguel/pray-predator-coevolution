#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <deque>
using namespace std;
using namespace cv;

#define HERITAGE 5
#define MATING_INTERVAL 200
#define MIGRATION 10

////////////////////////// MUTATION //////////////////////

// mutate by how much:
#define ANGLE_MUTATION 1
#define WEIGHT_MUTATION 1
#define SPEED_MUTATION 1

// mutation probability:
#define CHILD_MUTATION_PROB 100  // wonderers
#define CARN_CHILD_MUTATION_PROB 100
#define CONST_UP 20
#define CONST_DOWN 20
#define WEIGHT_UP 30
#define WEIGHT_DOWN 10
#define SPEED_UP 20
#define SPEED_DOWN 20

//////////////////////////  MATRIX  ////////////////////////

#define X 600
#define Y 400

#define XSIZE X
#define YSIZE Y
#define XRESTRAINT X
#define YRESTRAINT Y

//////////////////////////  GUI  ///////////////////////////

#define IMG_WIDTH 900
#define IMG_HEIGHT 600

////////////////////////////////////////////////////////////

#define OK 1
#define ERROR 0
#define PI 3.14159265

//////////////////////// POPULATION ////////////////////////

#define POP_WONDER 10
#define POP_PLANTS 10
#define POP_CARN 10

#define RADIUS_WONDER 5
#define RADIUS_PLANTS 5
#define RADIUS_CARN 5

#define MAX_SPEED 21
#define MAX_WEIGHT 11
#define MAX_CONST 101

#define N 0   // empty
#define H 1   // herbivore
#define C 2   // carnivore
#define P 3   // plant
#define W 4   // wonderer

///////////////////////// PARETO CURVE /////////////////////

#define HURT_CONST 1
#define HEALTH_CONST 20

////////////////////////////////////////////////////////////

typedef int Type;      // matrix data type

typedef struct{

    int x,y;
    int speed;  // pixels per frame
    float angle;    // angle relative to an horizontal line (downwards angle, it seems)

    int energy;

    // wonderers only
    int health;
    int hurt;

    bool best;

    // genes
    int plant_const, plant_weight;  // 0 to 100, 0 to 10
    int wond_const, wond_weight;  // 0 to 100, 0 to 10
    int carn_const, carn_weight;

    deque <int> heritage; // use only PUSH_FRONT and POP_BACK
    int average_energy;
    int h_count; // verify is heritage is full

    Vec3b color;

}population;

typedef struct{
    int x,y;
    Vec3b color;
}plants;

/********************************************** MATRIX SET UP *************************************************************/

void initialize_matrix(Type matrix[][XSIZE]);
int check_disponibility(Type matrix[][XSIZE], int x, int y);

bool check_for_obstacles(int x0, int y0, float angle, int speed, int* type);
void first_obstacle_bfs(int startx, int starty, int* xobs, int* yobs, int* type_obs);
float calculate_angle(int x, int y, int xobs, int yobs, float dir_angle);
void first_plant_bfs(int startx, int starty, int* xobs, int* yobs);
void first_wonderer_bfs(int startx, int starty, int* xobs, int* yobs);
void obstacles_bfs(int startx, int starty, int* xplant, int* yplant, int* xwond, int* ywond, int* xcarn, int* ycarn);


/************************************************ WONDERERS ***************************************************************/

void initialize_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]);
void import_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]);
void move_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]);
void random_wonderers(std::vector<population> &pop, Type matrix[][XSIZE]);
void rotation_equation(std::vector<population> &pop, int index, int obs_type, float deviation);
void genetic_rotation(std::vector<population> &pop, int index);

void elitism(std::vector<population> &pop, Type matrix[][XSIZE]);
void tournament(std::vector<population> &pop, Type matrix[][XSIZE]);
void best_wonderer(std::vector<population> &pop);
population cross_over(std::vector<population> &pop, int p1, int p2);
void mutation(population* ind);

void elitism_heritage(std::vector<population> &pop, Type matrix[][XSIZE]);
void tournament_heritage(std::vector<population> &pop, Type matrix[][XSIZE]);
void best_wonderer_heritage(std::vector<population> &pop);
population cross_over_heritage(std::vector<population> &pop, int p1, int p2);


/************************************************** PLANTS ****************************************************************/

void initialize_plants(std::vector<plants> &pop, Type matrix[][XSIZE]);
void new_plants(std::vector<plants> &pop, Type matrix[][XSIZE]);


/************************************************* CARNIVORES *************************************************************/

void initialize_carnivores(std::vector<population> &pop, Type matrix[][XSIZE]);
void import_carnivores(std::vector<population> &pop, Type matrix[][XSIZE]);
void move_carnivores(std::vector<population> &pop, Type matrix[][XSIZE]);
bool carnivores_check_for_obstacles(int x0, int y0, float angle, int speed, int *type);

void carnivores_elitism(std::vector<population> &pop, Type matrix[][XSIZE]);
void carnivores_tournament(std::vector<population> &pop, Type matrix[][XSIZE]);
population carnivores_cross_over(std::vector<population> &pop, int p1, int p2);
void carnivores_mutation(population* ind);
void best_carnivore(std::vector<population> &pop);

void carnivores_elitism_heritage(std::vector<population> &pop, Type matrix[][XSIZE]);
void carnivores_tournament_heritage(std::vector<population> &pop, Type matrix[][XSIZE]);
population carnivores_cross_over_heritage(std::vector<population> &pop, int p1, int p2);
void best_carnivore_heritage(std::vector<population> &pop);


/******************************************************* GUI *************************************************************/

Mat print_wonderers(std::vector<population> &pop);
Mat print_img(std::vector<population> &wond_pop, std::vector<plants> &plants_pop, std::vector<population> &carn_pop);