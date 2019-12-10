# Pray-Predator coevolution

An evolutionary algorithm written in c++ to evolve a pray-predator environment.
<br/>
<br/>
<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/evolution.gif?raw=true" height="300">
</p>
The environment consists of plants (green), herbivores (blue) and carnivores (pink), the herbivores and carnivores coevolve over time learning to interact with each other. The elitism selection method with mutation was employed, as well as predation and inheritance techniques.
<br/>

## Predation
Every 15 generations (or other chosen interval) the worst individual from both pray and predator's population in eliminated and replaced by a random individual. This technique increases the population's diversity counterbalancing the quick convergence due to the elitism method.
<br/>

## Inheritance
Due to the noise inherent to the environment and the established interactions the population's fitness can suddenly deteriorate from one generation to the other. To avoid this the offspring inherit their parent's fitness score decreasing the probability of a bad individual obtaining by luck a good score that allows it to pass on its genes to the next generation.

