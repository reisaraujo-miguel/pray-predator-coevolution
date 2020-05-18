# Pray-predator coevolution

## Noise analysis

[teste](##coevolution-implications)


The environment where the genetic algorithm is tested and evaluated is highly noisy since an individual's score depends not only on its own fitness but also on its surroundings. If ignored, this characteristic of the simulations can impair data analysis, since much of the oscilations perceived in the population's score overtime is due to noise. 

In order to establish a threshold that allows pinpointing actual changes in a population's behavior as oposed to performance fluctuations due to noise, some simulations were run with fixed herbivores and carnivores. This means that the populations weren't evolving (therefore there were no changes in behavior), they were let to interact during the normal duration of a generation and when this interval was over, the environment was simply reset (the individuals were placed in random positions), those operations were repeated over a determined number of generations, as when running the GA. 

Plotting the graphs corresponding to the _moving average_ over 50 generations of the each of population's _mean energy_ ([genetic configuration](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/ref/genes.md#noise-analysis)), the following pattern was obtained:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/noise.png?raw=true" height="300">
</p>

on a smaller time window:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/noise_smaller_interval.png?raw=true" height="300">
</p>

The fluctuation observed are solely due to the environments' noise. Now plotting the graphs corresponding to the fittest individual's scores overtime, we still observe large oscilations:

<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/noise_fittest_score.png?raw=true" height="300">
</p>

This observations seem to indicate that the algorithm has robustness problems. The fittest individual score sets a upper bound on the whole population's score, so when it drops, this means that all other individuals achived still lower scores. Such oscilations pose problems to the evolution process, because it becomes highly susceptible to luck. 

Searching for possible causes for such oscilations, we came across the frequent formation of clusters, as seen on the animation bellow:

<br/>
<p align="center">
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/clusters_small.gif?raw=true" height="300">
</p>

Those clusters are probably the cause of the undesirable oscilations observed. Such lockings occur because the individuals cannot go over obstacles, they must deviate. The objective is that the indivuduals gradullay learn/evolve this behavior, but the amount of noise implicated wasn't expected. 
In order to verify these supositions and the actual impacts of clusterings, further simulations shall be run enabling the individuals to [pass over obstacles](##no-obstacle-simulations).


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
<img src="https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/img/diagram.png?raw=true" height="300" title="Simulation 2">
</p>

However, the constant changes in the populations due to the presure of coevolution, made it hard to analyse specific behaviors developed by each of the populations, and set apart evolutive successes from trasitional states. In order to accomplish this analysis, each of the populations were let to evolve with the other kept fixed. The result was the development of a variety of behaviors. 

## Only carnivores evolving

For the simulations with evolving carnivores, apt herbivores were initialized and maintained fixed.

The herbivore's genetic configuration was the following:

Gene type | Value 
--- | --- 
Plant constant | 0
Herbivore constant | -7
Carnivore constant | 12
Plant weight | 30
Herbivore weight | 5
Carnivore weight | 0
Search height limit | None
Speed | 24

meaning that they prioritize eating and didn't even perceive the presence of carnivores. This genetic configuration was taken out of a previous simulation and it corresponded to a peak in herbivores' performance.

For this same hervibore condition, the carnivores showed a variety of responses. The development of those diverse behaviors are due to the different nudges noise causes on evolution, but they were also influenced by changes in non-evolutive parameters, such as population size, inheritance, and the number of frames the populations were let to interact during each generation. 

Some of those behaviors are listed bellow. All of them reflect increased energy values that stabilized for a while, corresponding to plateaus on the graphs plotted.

- carnivores agglomerated around plants or circled around them, waiting for the herbivores to come \[[video1](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%404037_circle_around_plants_10000gen_200int_10carn_10herb_10plan_5heritHerb_5heritCarn_20health_20ev(1).txt.mp4)\], in some cases, in addition to that, they also developed sawrm behavior, moving around in groups \[[video2](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%401999_plant_aglomeration_group_chasing_10000gen_200int_10carn_10herb_10plan_5heritHerb_5heritCarn_20health_20ev(1).txt.mp4)\]\[[video3](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%401999_plant_contouring_group_chasing_10000gen_200int_10carn_10herb_10plan_5heritHerb_10heritCarn_20health_20ev(2).txt.mp4)\];
- in some simulations, the carnivores restricted significantly their vision range, but developed diverse reactions to extern stimuli, such as:
  - following whatever came close, be it carnivore, herbivore or plant \[[video4](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%408254_follow_whatever_comes_close_10000gen_200int_10carn_10herb_10plan_5heritHerb_5heritCarn_20health_20ev(1).txt.mp4)\];
  - avoiding other carnivores (hunting alone), circling around plants and chasing herbivores\[[video5](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%401971_limited_view_hunt_alone_circle_plants_chase_herb_10000gen_200int_5carn_10herb_10plan_5heritHerb_5heritCarn_20health_20ev(3).txt.mp4)\];
- carnivores exclusively hunted herbivores \[[video6](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%405000_just_chase_10000gen_200int_5carn_10herb_10plan_5heritHerb_10heritCarn_20health_20ev(4).txt.mp4)\] \[[video7](https://github.com/AliceDeLorenci/pray-predator-coevolution/blob/master/evolutionaryAlgorithm/plotterData/only_carnivores_evolving_mutation_bug/%408000_carn_chase_herb_10000gen_200int_10carn_10herb_10plan_5heritHerb_5heritCarn_20health_20ev(1).txt.mp4)\].

It is worth commenting that the simulations corresponding to the analysis above showed unexpected downward slopes on the ponctuation of carnivore's. This wasn't expected as the herbivore's weren't evolving, therefore, the carnviores should improve gradually and possibly reach a stagnation point, susceptible only to noise fluctuations. Nevertheless, patterns such as highlightes bellow were recurrent:




## Only herbivores evolving

## Alternating evolution

## Inheritance influence on stability

## No-obstacle simulations
