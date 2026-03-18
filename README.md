# 🍝 Philosophers

*I never thought philosophy would be so deadly.* **Philosophers** is a famous 42 Network project that introduces the basics of multithreading, concurrency, and process synchronization in C. 

---

## 📖 About The Project

This project is a variation of the classic **Dining Philosophers problem** originally formulated by Edsger Dijkstra. It serves as an introduction to the complex world of concurrent programming. 

The goal is to simulate a group of philosophers sitting at a round table doing three things: **eating, sleeping, and thinking**. However, there's a catch: they must share a limited number of forks, and a philosopher needs *two* forks to eat. If a philosopher goes too long without eating, they starve and die, ending the simulation.

### 🎯 Core Objectives
* Master the creation and joining of threads using `pthread_create` and `pthread_join`.
* Understand and prevent **Data Races** and **Deadlocks**.
* Implement state synchronization using **Mutexes** (`pthread_mutex_init`, `lock`, `unlock`, `destroy`).
* Manage precise time calculations in C (`gettimeofday`).

---

## ⚙️ The Rules of the Table

1. There are `N` philosophers sitting around a circular table.
2. There is one fork placed between each pair of philosophers (Total `N` forks).
3. A philosopher must hold exactly **two forks** (their left and their right) to eat.
4. The philosophers never communicate with each other. They don't know if another philosopher is about to die.
5. The simulation stops if a philosopher dies of starvation.
6. The entire program must be free of data races (all shared variables must be protected by mutexes).

---

## 🛠️ Getting Started

### Prerequisites
* A standard C compiler (`cc`, `gcc`, or `clang`)
* `make` utility
* `pthread` library (standard on Unix/Linux systems)

### Installation & Compilation

1. Clone the repository:
   ```bash
   git clone git@github.com:yuuryyy/philosophers_42.git
   cd philosophers_42/philo
   ```

2. Compile the executable:
   ```bash
   make
   ```
   This will generate the `philo` executable.

### Makefile Rules
* `make` / `make all`: Compiles the `philo` program.
* `make clean`: Removes the compiled `.o` object files.
* `make fclean`: Removes the object files and the executable.
* `make re`: Runs `fclean` followed by `all`.

---

## 💻 Usage

Run the simulation by passing the required timing arguments in milliseconds.

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments Breakdown:
* `number_of_philosophers`: The number of philosophers (and forks) at the table.
* `time_to_die` (in ms): If a philosopher doesn’t start eating `time_to_die` milliseconds after starting their last meal or the beginning of the simulation, they die.
* `time_to_eat` (in ms): The time it takes for a philosopher to eat. They will need to hold two forks during this time.
* `time_to_sleep` (in ms): The time a philosopher spends sleeping.
* `number_of_times_each_philosopher_must_eat` *(optional)*: If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops only when a philosopher dies.

### Example Executions

**Example 1: The philosophers should not die.**
```bash
./philo 5 800 200 200
```
*With 5 philosophers, a time to die of 800ms, and 200ms to eat/sleep, everyone has plenty of time to share the forks without starving.*

**Example 2: A philosopher will die.**
```bash
./philo 4 310 200 100
```
*With these tight constraints, the delay in waiting for forks will eventually cause a philosopher to cross the 310ms starvation threshold.*

---
*Developed by Youssra Chagri at 1337 (UM6P).*
