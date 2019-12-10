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
