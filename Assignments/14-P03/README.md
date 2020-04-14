## Program 3 - Modeling Covid19 Part 2
#### Due: 04-16-2020 (Thursday @ 12:30 p.m.)

### Overview

I've posted a few python / pygame example code listings that progressively take you through ... well not a ton of gaming code, but enough to do what we need to get started with our covid19 simulation. This isn't strictly a visualization, but it will make it more interesting if we visualize our infected vs susceptible and recovered. 




### Covid 19 Proposed Class Diagram

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19a_uml_2020.png" width="350">

### Classes To Add

| Variable              | Description                                        |   Ranges    |
| :-------------------- | :------------------------------------------------- | :---------: |
| `Beta`                | Probability that someone gets infected             |   0 - .99   |
| `Gamma`               | The rate infected moves to recovered               | 1 - D days  |
| `Nu`                  | The rate at which susceptible become vaccinated    | 1 - D days  |
| `Initial susceptible` | # of susceptible individuals at beginning of a run | N * Percent |
| `Initial infected `   | # of infected individuals at beginning of a run    | N * Percent |
| `Initial recovered`   | # of recovered individuals at beginning of a run   | N * Percent |
| `Iterations`          | How many days to run for                           | N * Percent |


| Variable                   | Description | Value |
| :------------------------- | :---------- | :---: |
| Hospital capacity          |             |  5%   |
| Input fatality rate        |             |  3%   |
| Self-quarantine rate       |             |  25%  |
| Self-quarantine strictness |             |  25%  |
| Encounters per day         |             |  10   |
| Travel radius              |             |   5   |
| Transmission rate          |             |  0.4  |
| Days in incubation         |             |   7   |
| Days with symptoms         |             |   8   |

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/covid19b_uml_2020.png" width="350">






