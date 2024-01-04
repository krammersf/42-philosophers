
# Philosophers

The dining philosopher's problem is the classical problem of synchronization which says that Five philosophers are sitting around a circular table and their job is to think and eat alternatively. A bowl of noodles is placed at the center of the table along with five chopsticks for each of the philosophers. To eat a philosopher needs both their right and a left chopstick. A philosopher can only eat if both immediate left and right chopsticks of the philosopher is available. In case if both immediate left and right chopsticks of the philosopher are not available then the philosopher puts down their (either left or right) chopstick and starts thinking again.

This is a project called "philo" which simulates the dining philosophers problem using threads and mutexes. It is implemented in the C programming language.

The challenge is to design an algorithm that allows the philosophers to dine peacefully without getting into a deadlock or starvation situation.

The "philo" project provides a solution to this problem by creating a simulation of the dining philosophers scenario. It utilizes threads to represent each philosopher and mutexes to represent the chopsticks. The program ensures that the philosophers follow a set of rules to avoid deadlocks and provide fairness in resource allocation.

## Compilation

To build the project, follow these steps:

1. Build the project using the provided Makefile:

   ```
   make
   ```

This will compile the source files and generate an executable named `philo`.

## Run

Once you have built the project, you can run it with the following command:

```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `<number_of_philosophers>`: The number of philosophers sitting around the table.
- `<time_to_die>`: The maximum time in milliseconds that a philosopher can survive without eating.
- `<time_to_eat>`: The time in milliseconds it takes for a philosopher to finish eating.
- `<time_to_sleep>`: The time in milliseconds the philosopher spends sleeping after eating.
- `[number_of_times_each_philosopher_must_eat]` (optional): The number of times each philosopher must eat before the simulation ends. If not provided, the simulation will continue indefinitely.

Example usage:

```
./philo 5 800 200 200
```

This command will run the simulation with 5 philosophers, a time to die of 800 milliseconds, a time to eat of 200 milliseconds, and a time to sleep of 200 milliseconds. In this example, the simulation will continue indefinitely and any philosopher will die.

## Check Data Races
The project cannot have `data races`, which means it cannot have access to a shared variable between threads without a synchronization mechanism. To check if the project has `data races` was used the compilation flag `-fsanitize=thread`. To compile the program with this flag, on the Makefile, remove the `#` of line 21 and save.
```
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
```
Then compile the project again.
```bash
make re
``` 

If the program has no data races, the program will run normally. Otherwise, the program will stop and show at the terminal where the error is.

## Grade: 100/100

## Used tests
- 42-philosophers-tester: https://github.com/dantonik/42-philosophers-tester
- alientest_philosopher: https://github.com/lienardale/alientest_philosopher
- philosophers-visualizer: https://nafuka11.github.io/philosophers-visualizer

### Disclaimer

Maybe you could notice a different coding style. At 42 we need to follow some rules according to the coding standard of the school such as:
```
- No for, do while, switch, case or goto 
- No functions with more than 25 lines 
- No more than 5 functions per each file
- No more than 5 variables in the same function
- No assigns and declarations assigns in the same line
```
Click here to read the norm file of 42 school.

