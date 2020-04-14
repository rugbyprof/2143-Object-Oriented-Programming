## Program 3 - Modeling Covid19 Part 1
#### Due: 04-03-2020 (Friday @ 12:30 p.m.)

### Overview

We are going to create a set of classes that will model a typical viral outbreak. Don't panic, it's really just updating values based on time and probabilities (this means a loop with a counter and some arithmetic). That may be a tad over simple, but it really is doable at our level. When you get ~~SFML~~ Pygame running and then into visualizing the spread, it may get a little harder. 

Below I grabbed some resources that discuss this thing called the SIR model (pronounced `sear`). It is a real model that is used in epidemiology (albeit a little old). I like this example because it is exactly what most computer scientists do in the real world: they use their CS skills in another field. I learned a ton about cochlear implants and hearing / speech tests doing research with a local doctor. I had to learn to implement certain things (like audiogram software) correctly. I had to understand the "lingo" :) 

So, the SIR model will give you and I proper terminology to help not only solve our ultimate goal of visualizing disease spread, but have a decent conversation and understand what each of us are talking about. The immediate goal is to understand the terminology and a grasp of the problem.  Think in terms of code re-use, modular design, composition and inheritance and all those awesome things we've learned so far. I'm not going to post any code this first go round, because I don't want to influence the way you think. So go over the SIR model below and start to formulate a plan of attack on how you would design a solution (NOT code a solution).

### SIR Model

The **SIR** models the flows of people between three states: ***susceptible (S), infected (I), and resistant (R)***. Each of those variables represents the number of people in those groups. The parameters ***alpha*** and ***beta*** partially control how fast people move from being susceptible to infected (***beta***), and from infected to resistant (***gamma***).

The SIR model is used where individuals infect each other directly (rather than through a disease vector such as a mosquito). An individual who recovers from the illness is also modeled to have perfect immunity to the disease thereafter. Contact between people is also modeled to be random.

The rate that people become infected is proportional to the number of people who are infected, and the number of people who are susceptible. If there are lots of people infected, the chances of a susceptible coming into contact with someone who is infected is high. Likewise, if there are very few people who are susceptible, the chances of a susceptible coming into contact with an infected is lower (since most of the contact would be between the non-susceptible people--either infected or resistant).

Out implementation will include an additional parameter, ***nu***, which allows people to become vaccinated. A vaccinated person moves from being susceptible to being resistant without going through the infected stage.

### Modeling

As the first step in the modeling process, we identify the independent and dependent variables. The independent variable is time  ***t***,  measured in days. We consider two related sets of dependent variables.

>**NOTE:** Dependent and independent variables are variables in mathematical modeling, statistical modeling and experimental sciences. ***Independent variables*** are controlled inputs. ***Dependent variables*** represent the output or outcome resulting from altering these inputs.

The first set of dependent variables counts people in each of the groups, each as a function of time:

| Variable   | Description                              |
| :--------- | :--------------------------------------- |
| `S = S(t)` | is the number of susceptible individuals |
| `I = I(t)` | is the number of infected individuals    |
| `R = R(t)` | is the number of recovered individuals   |

When they say "function of time" that means that as our loop runs incrementing our counter (***t***), then we can take a snapshot of the problem space and know for sure at any time ***t*** how many are susceptible, infected, and recovered (or dead).


The second set of dependent variables represents the fraction of the total population in each of the three categories. **N = total population**.

| Variable        | Description                                |
| :-------------- | :----------------------------------------- |
| `s(t) = S(t)/N` | the susceptible fraction of the population |
| `i(t) = I(t)/N` | the infected fraction of the population    |
| `r(t) = R(t)/N` | the recovered fraction of the population   |

The above dependant variables are what we want to ultimately keep track of but looking at the percentage of each, we could visualize the "big picture". This is where we would see how steep our infected curve gets. So its not only about S,I,and R. We also need some variables to get our simulation started. Again, N = total population.

| Variable              | Description                                        |   Ranges    |
| :-------------------- | :------------------------------------------------- | :---------: |
| `Beta`                | Probability that someone gets infected             |   0 - .99   |
| `Gamma`               | The rate infected moves to recovered               | 1 - D days  |
| `Nu`                  | The rate at which susceptible become vaccinated    | 1 - D days  |
| `Initial susceptible` | # of susceptible individuals at beginning of a run | N * Percent |
| `Initial infected `   | # of infected individuals at beginning of a run    | N * Percent |
| `Initial recovered`   | # of recovered individuals at beginning of a run   | N * Percent |
| `Iterations`          | How many days to run for                           | N * Percent |


### Online Example Model

There is an example outbreak visualization that the 3Blue1Brown video mentioned and can be found here https://meltingasphalt.com/interactive/outbreak/. Below are the values used to influence the simulation on the page (one of them at the bottom):

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

We wont use all these parameters to model our simulation, but we could if we wanted to. I would go to the website and play around with the input values trying to flatten the curve like Grant did on his 3Blue1Brown video.

### Thoughts

There are a lot of terms and variables discussed. Try and take a step back and think simple and logical. Write on paper how a person could be represented as a class. Then think about what a person does. Look at all the terms we discussed to help you create your classes (like travel radius). How in heck will we represent travel? If we travel, then we have a position .... If we have a position, then where am I being positioned?!? Am I in a list? A grid? 

If I was doing research, we call that going down the rabbit hole, meaning you look up a definition that leads to another definition, and another , and another ... You get the point.

But its OK in doing your design. Think about what values need remembered. What logical item they belong to. And where and/or how those items need to be stored. 

>**NOTE:** I don't want to influence your assessment by telling you how many classes you should have, or give you hints about pitfalls. But I will say that each class should represent something that can stand on its own. I will also say you should not have just a single class. We haven't discussed this in class from a raw problem statement and frankly I'm nervous. I want you to put a lot of thought into it! I'm ok with collaboration, just don't have everyone turn in the same design.

Good Luck!

### Deliverables 

- A uml diagram of your design solution to this problem. 
- Refer to [07-H04](../07-H04/README.md) for reference.
- Create a folder called `P03` in your assignments folder.
- Place all images and relevant materials into this folder. 
- Put it on github.
