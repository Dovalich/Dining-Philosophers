# Philosophers

The Dining Philosophers is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

https://en.wikipedia.org/wiki/Dining_philosophers_problem

![Dining Philosophers](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png)

### Concepts I've learned about:

- Concurrency
- Parallelism
- Data-Races
- Deadlocks
- Resource Starvation
- Priority inversion
- Mutexes and Semaphores
- Threads and Processes


### How to use

-> Git clone

-> make

-> Read instructions below

-> run ./philosophers [args]

### Instructions

The program takes the following arguments:

number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

**Explanation of the arguments:**

◦ number_of_philosophers: is the number of philosophers and also the number
of forks.

◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting their last meal or the beginning of the simulation,
it dies.

◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time they will need to keep the two forks.

◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.

◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.
