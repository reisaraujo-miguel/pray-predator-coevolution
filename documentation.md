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
a variable of value __n__ corresponds to a rotation of n hundredths of a full circle. The weight variables assume
