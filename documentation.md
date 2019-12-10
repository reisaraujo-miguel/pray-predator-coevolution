# Pray-Predator Coevolution

## Objectives

The objective of this project is to develop an evolutionary algorithm that coevolves two independent
populations: prays and predators, so that they "learn" to interact over time reaching a stable configuration.

## Implementation and evolutive parameters

The individuals, both herbivores and carnivores, perceive their surrounding through a breadth first search that 
locates the first obstacle of each type: plant, herbivore and carnivore, and informs the angle to each of the obstacles 
in relation to the direction the entity is facing. Based on these the individual can rotate, resulting in a new moving 
direction.

For each of the three types of obstacles there is an associated variable that determines the rotation in relation to this 
obstacle. Therefore there will be three rotation values from which a weighted average is taken. Both the rotation values and 
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
a variable of value __n__ corresponds to a rotation of n hundredths of a full circle. The weight variables assume values from 0 
to 10. Although initialized in those intervals, no limits are set, therefore the GA can "cheat" through mutation.

## Fitness score

An entity's fitness score is its energy, and it's calculated differently for herbivores and carnivores.

- __Carnivores__
<br/>Each time a carnivore attacks a herbivore its energy is increased by 1. However, if a herbivore bumps into a carnivore
there are no changes to latter's score.

- __Herbivores__
<br/>The herbivores, refered to as __wanderers__ throughout the code, have health and hurt scores. Each time it eats, its health is increased by one, and each time it runs into a carnivore, or is being attacked by one, its hurt score is increased by one.
<br/>The energy is calculated in the following manner:  _HEALTH\_CONST·health + HURT\_CONST·hurt_, where the _HEALTH_CONST_ and _HURT_CONST_ are set by macros.

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
To reduce the negative effects of noise the inheritance technique was applied.

### Mutation
As well as maintaining diversity, the mutation is used to counterbalance the average process employed in the crossing over.
Since the the rotation and weight variables are of type _int_, when the average of the parent's variables results in a floating point number, it is rounded down. This affects mainly the weight variables due to its small range (from 0 to 10)
resulting in a slow but constant decrease of those variables. To revert this process, the probability of mutating up is set as greater then the probability of mutating down.

### Predation/Migration
Every _MIGRATION_ generations the worst individual from both pray and predator's population in eliminated and replaced by a random individual. This technique counterbalances the quick convergence inherent to the elitism method.

### Inheritance


