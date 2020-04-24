
#define GUI_ON 1

#define FILE_NUMBER 1


#define HERITAGE_WANDER 5
#define HERITAGE_CARN 5

#define MATING_INTERVAL 200 // number of frames per generation

#define GENERATION 10000

#define MIGRATION 10

// population sizes
#define POP_WANDER 10
#define POP_PLANTS 10
#define POP_CARN 5


///////////////////////////////////////// MUTATION /////////////////////////////////////////

#define AVERAGE_INTERVAL 20 
// in order to analise stagnation or detarioration of the system, an average 
// of the fittest individual's energy over <AVERAGE_INTERVAL> generations
// will be taken

#define EVALUATE_INTERVAL 20
// if the average energy of the fittest individuals over <AVERAGE_INTERVAL>
// deteriorates during a <EVALUATE_INTERVAL> generations period, than dynamic
// mutation shall be activated

#define DYNAMIC_DURATION 20 // duration of a dynamic_mutation cycle

// mutate by how much:
#define DYNAMIC_PROPORTION 1 
// for dynamic cycle, the mutation increments/decrements will be multiplied by <DYNAMIC_PROPORTION>
// 1 = OFF

#define ANGLE_MUTATION 1       // angle = [0,100]
#define WEIGHT_MUTATION 1      // weight = [0,10]
#define SPEED_MUTATION 1       // speed = [0,20]
#define HEIGHT_MUTATION 10     // height -> no limits

// mutation probability:
#define CHILD_MUTATION_PROB 100         // probability that a herbivore/wanderer offspring will mutate
#define CARN_CHILD_MUTATION_PROB 100    // probability that a carnivore offspring will mutate

// probability that a specific gene shall mutate, all genes have the same mutation
// probability (40%) distributed between mutating up and down, with the exception of BOOL_HEIGHT
#define CONST_UP 20
#define CONST_DOWN 20
#define WEIGHT_UP 30    // counter balance the fact that division of integerz always rounds down
#define WEIGHT_DOWN 10
#define SPEED_UP 20
#define SPEED_DOWN 20
#define BOOL_HEIGHT 20
#define HEIGHT 20

///////////////////////////////////////// PARETO CURVE /////////////////////////////////////////

#define HURT_CONST 1
#define HEALTH_CONST 20

////////////////////////////////////////////////////////////////////////////////////////////////

#define BIG_SIZE 100  // height gene restraint for random initialization only

