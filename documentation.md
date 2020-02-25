# Pray-Predator Coevolution

## Objectives

The objective of this project is to develop an evolutionary algorithm that coevolves two independent
populations: prays and predators, so that they "learn" to interact over time reaching a stable configuration.

## Implementation and evolutive parameters

The individuals, both herbivores and carnivores, perceive their surrounding through a breadth first search that 
locates the first obstacle of each type: plant, herbivore and carnivore, and informs the angle to each of the obstacles 
in relation to the direction the entity is facing. Based on these the individual can rotate, resulting in a new moving 
direction.

For each of the three types of obstacles there is an associated variable that determines the rotation in relation to the
obstacle in question. Therefore there will be three rotation values from which a weighted average is taken. Both the rotation values and 
the weights are evolutive parameters, as well as the individual's speed, all of them are randomly initialized.

Rotation variables:
- plant_const
- wand_const
- carn_const

Weight variables:
- plant_weight
- wand_weight
- canr_weight

The rotation variables assume values from 0 to 100. In the scale adopted the circle is divided in 100 parts, therefore
a variable of value __n__ corresponds to a rotation of n hundredths of a full circle in relation to the obstacle's position. The weight variables assume values from 0 to 10. Although initialized inside those intervals, no limits are set, therefore the GA can "cheat" through mutation.

## Fitness score

An entity's fitness score is its energy, and it's calculated differently for herbivores and carnivores.

- __Carnivores__
<br/>Each time a carnivore attacks a herbivore its energy is increased by 1. However, if a herbivore bumps into a carnivore
there are no changes to the latter's score.

- __Herbivores__
<br/>The herbivores, refered to as __wanderers__ throughout the code, have health and hurt scores. Each time it eats, its health is increased by one, and each time it runs into a carnivore, or is being attacked by one, its hurt score is increased by one.
<br/>The energy is calculated in the following manner:  _HEALTH\_CONST·health - HURT\_CONST·hurt_, where the _HEALTH_CONST_ and _HURT_CONST_ are set by macros.

Varying the HEALTH_CONST and HURT_CONST determines different pray behaviors. Setting those macros as: 
```cpp
#define HURT_CONST 1
#define HEALTH_CONST 20
```
results, overtime, in a herbivore population that prioritizes eating rather then running away from carnivores, whereas
the outcome of setting them as:
```cpp
#define HURT_CONST 1
#define HEALTH_CONST 10
```
is a herbivore population that prioritizes fleeing over eating.

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

The developed environment is highly noisy since an individuals score depends not only on its own fitness but also on its surroundings. Threfore a highly apt individual can be far away from any food or be under chase, receiving a bad score, and an unfit individual can, by chance, bump into food or not be attacked, receiving a good score or even becoming the best of the current generation, in which case it passes on its bad genes to the whole new population.
Such cenarios were quite commom, resulting in sudden drops of the whole population's aptness, mainly between the herbivores. <br/>To avoid this, the offspring inherits the energy score of its _HERITAGE_ last forefathers, which are stored in a vector.
When calculating an individual's fitness the average is taken from its energy and its forefathers' energies.
<br/>This way an unlucky apt individual, probably the offsprint of apt parents, still gets a good evaluation and a lucky but unfit individual will have a lower probability of achieving a score so good that it overruns an individual with a good heritage.
<br/>Nevertheless, eventually an entity which is offspring to unapt parents with low scores can achieve a high energy score not by luck but by aptness. In order to preserve such individuals, the best individual (determined by the average of its and its forefathers energies) mates only with individuals that have lower energies than itself, considering the current generation, the others (with higher scores considering only the current generation) are cloned, giving them another chance.


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
