# Pray-predator coevolution

## Noise analysis
The environment whre the genetic algorithm is tested and evaluated is highly noisy since an individuals score depends not only on its own fitness but also on its surroundings. If ignored, this characteristic of the simulations can impair data analysis, since much of the oscilations perceived in the population's energy overtime is due to noise. In order to establish a threshold that allows pinpointing actual changes in a population's behavior as oposed to normal performance fluctuations, some simulations were run with fixed herbivores and carnivores. This means that the populations weren't evolving (therefore there were no changes in behavior), they were let to interact during the normal duration of a generation and when this interval was over, the environment was simply reset (the individuals were placed in random positions), those operations were repeated over a determined number of generations as when running the GA. 
Plotting the graphs corresponding to average over 50 generations of the population's mean energy, the following pattern was obtained:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/50graph.jpg?raw=true" height="300">
</p>
