# Pray-Predator Coevolution

## Objectives

The objective of this project is to develop an evolutionary algorithm that coevolves two independent
populations: prays and predators, so that they "learn" to interact over time reaching a stable configuration.

## Implementation and evolutive parameters

The individuals' (herbivores and carnivores) perception of the environment consists on locating the closest obstacle of each type: plant, herbivore and carnivore, and accesing the angular deviation of each of those obstacles in relation to the direction it's facing. Based on these angular deviation the individual can rotate, resulting in a new moving direction.

For each of the three types of obstacles (plant, herbivore and carnivore) there is an associated variable that determines the rotation in relation to the obstacle in question. Therefore there will be three rotation values from which a weighted average is taken. Both the rotation values and the weights are evolutive parameters, as well as the individual's speed, all of them are randomly initialized.

Rotation variables:
- plant_const
- wand_const
- carn_const

Weight variables:
- plant_weight
- wand_weight
- canr_weight

The rotation variables assume values from 0 to 100, so that in the scale adopted the circle is divided in 100 parts. Therefore a variable of value __n__ corresponds to a rotation of n hundredths of a full circle in relation to the obstacle's position. The weight variables are initialized with values ranging from 0 to 10, however no limits are set, therefore the GA can "cheat" through mutation.

Moreover there are also evolutive parameters that determine how far away the individual can "see", those genes are:
- height_limit: boolean parameter that determines whether or not there will be a limit to the distance the individual "sees";
- height: corresponds to the actual distance limit (in pixels), but it's only considered if the height_limit gene is set to 1.
In other words, this means that, if the _height/_limit_ gene is acrive, the individual can only locate the closest obstacle to itself if the obstacle is whithin a radius of _height_ pixels.

## Fitness score

An entity's fitness score is its energy, and it's computed differently for herbivores and carnivores.

- __Carnivores__
<br/>Each time a carnivore attacks a herbivore its energy is increased by 1. However, if a herbivore bumps into a carnivore
from behind there are no changes to the latter's score (the carnivore doesn't gain energy).

- __Herbivores__
<br/>The herbivores, refered to as __wanderers__ throughout the code, have health and hurt scores. Each time it eats, its health is increased by one, and each time it runs into a carnivore, or is being attacked by one, its hurt score is increased by one.
<br/>The energy is calculated in the following manner:  _HEALTH\_CONST·health - HURT\_CONST·hurt_, where the _HEALTH_CONST_ and _HURT_CONST_ are set by macros.

Varying the HEALTH_CONST and HURT_CONST determines different pray behaviors. Setting those macros as: 
```cpp
#define HURT_CONST 1
#define HEALTH_CONST 20
```
frequently results, overtime, in a herbivore population that prioritizes eating rather then running away from carnivores, whereas the outcome of setting them as:
```cpp
#define HURT_CONST 1
#define HEALTH_CONST 10
```
is generally a herbivore population that prioritizes fleeing over eating.

## Evolutive strategies

Both tournament and elitism methods were implemented, although only elitism was implemented with inheritance. In order to maintain diversity mutation occurs at crossover and predation/migration occurs at an interval of _MIGRATION_ generations.
To reduce the negative effects of noise the inheritance technique is applied.

#### Mutation

As well as maintaining diversity, mutation is used to counterbalance the average process employed in the crossing over.
Since the rotation and weight variables are of type _int_, when the average of the parent's variables results in a floating point number, it is rounded down. This affects mainly the weight variables due to its small range (from 0 to 10)
resulting in a slow but constant decrease of those variables. To revert this process, the probability of mutating up is set as greater then the probability of mutating down.

#### Predation/Migration

Every _MIGRATION_ generations the worst individual from both pray and predator's population in eliminated and replaced by a random individual. This technique counterbalances the quick convergence inherent to the elitism method.

#### Inheritance (implemented for elitism)

The developed environment is highly noisy since an individuals score depends not only on its own fitness but also on its surroundings. Threfore a highly apt individual can be far away from any food or be under chase, receiving a bad score, and an unfit individual can, by chance, bump into food or not be attacked, receiving a good score or even becoming the best of the current generation, in which case it passes on its bad genes to the whole of the new population.
Such cenarios were quite commom, resulting in sudden drops of the whole population's aptness, mainly between herbivores. <br/>To avoid this, the offspring inherits the energy score of its _HERITAGE_ last forefathers, which are stored in a vector.
When calculating an individual's fitness the average is taken from its energy and its forefathers' energies.
<br/>This way an unlucky apt individual, probably the offsprint of apt parents, still gets a good evaluation and a lucky but unfit individual will have a lower probability of achieving a score so good that it overruns an individual with a good heritage.
<br/>Nevertheless, eventually an entity which is offspring to unapt parents with low scores can achieve a high energy score not by luck but by aptness. In order to preserve such individuals, the best individual (determined by the average of its and its forefathers energies) mates only with individuals that have lower energies than itself, considering only their performance on the current generation, the others (with higher scores considering only the current generation) are cloned, giving them another chance.


#### Speeding up evolution

In order to speed up the evolutive process and the achievment of a stable configuration the first herbivore's and carnivore's population can be initialized with a relatively apt individual.
Hence, for the herbivore's population one individual can be initialized with the following varables:
```cpp
plant_const = 0
wand_const = 30
carn_const = 30

plant_weight = 10
wand_weight = 0
canr_weight = 0
```
Meaning that it goes towards the plants and exclusively prioritizes eating.

For the carnivore population one individual can be initialized as:
```cpp
plant_const = 30
wand_const = 0
carn_const = 30

plant_weight = 0
wand_weight = 10
canr_weight = 0
```
Meaning that it goes towards the herbivores and exclusively prioritizes eating.

## Behavior Analysis
[behaviorAnalysis.md](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/behaviorAnalysis.md)
<br/>