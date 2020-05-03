# Pray-predator coevolution

## Noise analysis

The environment where the genetic algorithm is tested and evaluated is highly noisy since an individual's score depends not only on its own fitness but also on its surroundings. If ignored, this characteristic of the simulations can impair data analysis, since much of the oscilations perceived in the population's score overtime is due to noise. 

In order to establish a threshold that allows pinpointing actual changes in a population's behavior as oposed to performance fluctuations due to noise, some simulations were run with fixed herbivores and carnivores. This means that the populations weren't evolving (therefore there were no changes in behavior), they were let to interact during the normal duration of a generation and when this interval was over, the environment was simply reset (the individuals were placed in random positions), those operations were repeated over a determined number of generations as when running the GA. 

Plotting the graphs corresponding to the moving average over 50 generations of the each of population's mean energy, the following pattern was obtained:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/noise.png?raw=true" height="300">
</p>

on a smaller time window:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/noise_smaller_interval.png?raw=true" height="300">
</p>

The fluctuation observed are solely due to the environments' noise.

## Coevolution implications

The fact that two interacting populations (herbivores and carnivores) coevolve separetly, but directly interfering with each other's performance, implicates that a point where the solutions stabilizes (like local or global optimas) isn't reached (or at least hasn't been observed so far). The carnivores and herbivores behaviors are interdependent, so for a given herbivore population the carnivores will evolve developing behaviors that improve performance for the given conditions. In turn, changes in the carnivore's population triggers the adaptation of herbivores, reestarting the cycle. Therefore we end up with constant changes in carnivores' and herbivores' behavior.

Simulations where both populations evolved simultaneously resulted in graphs such as:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/both_evolve1.png?raw=true" height="300" title="Simulation 1">
</p>

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/both_evolve2.png?raw=true" height="300" title="Simulation 2">
</p>

It can be seen that the herbivore's and carnivore's performance are mostly mirrored, which was expected. Increased energy levels of carnivores means that they are chasing more eficiently, causing the herbivores' energy score to reduce. The opposite is also true, when the energy score of the herbivore population increases this means that they are either eating more or avoiding predators more eficiently, the later case causes the carnivore's energy to decrease.

In general, the following cycle was observed throughout the simulations:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/diagram.png?raw=true" height="200" title="Simulation 2">
</p>

However, the constant changes in the populations due to the presure of coevolution, made it hard to analyse specific behaviors developed by each of the populations, and set apart evolutive successes from trasitional states. In order to accomplish this analysis, each of the populations were let to evolve with the other kept fixed. The result was the development of a variety of behaviors.

## Only carnivores evolving

## Only herbivores evolving