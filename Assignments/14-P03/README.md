## Program 3 - Modeling Covid19 Part 2
#### Due: 05-01-2020 (Friday @ 5:00 p.m.)

## Overview

I've posted a few python / pygame example code listings that progressively take you through ... well not a ton of gaming code, but enough to do what we need to get started with our covid19 simulation. This isn't strictly a visualization, but it will make it more interesting if we visualize our infected vs susceptible and recovered. 


### Disease Model

Not every simulation uses the same "model". We are using the SIR model (or a simple variation of) becuase it is straightforward and fits our purposes. However if we decide to use another model, we don't want our "simulation" to be tightly coupled with only a single disease model. For example the SEIR model or the SIS model. Therefore I propose a class that will allow us to load any model. 

The SIR model: 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/sir_flow_diagram_2020.png" width="500">

**State Descriptions:** 

| #    | State       | Description                                     | Exceptions                 |
| :--- | :---------- | :---------------------------------------------- | :------------------------- |
| 1    | Susceptible | Any person who can catch the disease            | Already infected or immune |
| 2    | Infectious  | A person that has the disease and is contagious | Quarantined                |
| 3    | Recovered   | A person who had the disesase and recovered     |                            |

**Additional State Info:**

| #    | State       | Color  | Image                              |
| :--- | :---------- | :----- | :--------------------------------- |
| 1    | Susceptible | Yellow | ![](./images/pac_yellow_30x30.png) |
| 2    | Infectious  | Red    | ![](./images/pac_red_30x30.png)    |
| 3    | Recovered   | Green  | ![](./images/pac_green_30x30.png)  |



<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19a_uml_2020.png" height="150">




### Simulation Class



|                                          Sim Disease Variables                                          |                                     Sim Additional Variables 2                                      |
| :-----------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------: |
| <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19_sir_model_vals.png" width="350"> | <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19_sim_params.png" width="200"> |

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19b_uml_2020.png" width="150">


### Other Possible Classes

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19_uml_2020.png" width="350">




## Discussion

This project is to take the **SIR** model and visualize a Covid19 outbreak with a population of people (or any flu basically). We did not discuss specifics in the beginning since we were really getting up to speed with python. Also, I wanted everyone to approach the problem in their own way. We looked at a [3 Blue One Brown video](https://www.youtube.com/watch?v=gxAaO2rsdIs&t=460s) modeling disease outbreak, and this will be our major influence for our last program. Not his visualizations, but the major influences to the outbreak that he discusses. Your program will do visualizations, but your grade will be determined on how you organize and design each of your classes.

Don't forget about the [Dry Principle](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself) when creating your classes. Each class should be responsible for one logical component of your simulation. I gave some examples at the top of this document, but there are many viable solutions.

## Project



### Deliverables

Deliverables coming







