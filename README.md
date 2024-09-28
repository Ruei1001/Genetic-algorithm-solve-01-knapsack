Genetic Algorithm for 0/1 Knapsack Problem
This project implements a genetic algorithm (GA) to solve the 0/1 knapsack problem. The algorithm evolves a population of potential solutions to maximize the profit of selected items while staying within a weight constraint.

Problem Definition
The 0/1 knapsack problem is an optimization problem where you are given a set of items, each with a weight and a profit. The objective is to select a subset of items that maximizes the total profit without exceeding a given capacity (i.e., total weight limit).

Algorithm Overview
The solution uses a genetic algorithm with the following steps:

Initialization: Generate an initial population of random solutions. Each solution is represented as a bit string where each bit corresponds to whether an item is included (1) or excluded (0) from the knapsack.

Selection: Use tournament selection to choose individuals from the population based on their fitness (profit-to-weight ratio). The fittest individuals have a higher chance of being selected.

Crossover: Pair individuals and perform crossover, where bits are swapped between two solutions to create new individuals. This simulates recombination of "genes" to produce offspring.

Mutation: Randomly flip some bits in a solution to introduce diversity and avoid premature convergence.

Evaluation: Evaluate each solution by calculating its total weight and profit. If a solution exceeds the weight capacity, items with the worst profit-to-weight ratio are removed until it satisfies the constraint.

Termination: The algorithm runs for a fixed number of evaluations and returns the best solution found.

File Structure
main.cpp: Contains the genetic algorithm implementation for the knapsack problem.
dataset/: Directory containing problem instances (e.g., item.txt), with each file describing the number of items, their weights, and profits.
How to Run
Compile the code using a C++ compiler:

bash
Copy code
g++ main.cpp -o knapsack
Run the compiled program:

bash
Copy code
./knapsack
The program will read the dataset file dataset/dt01/item.txt and execute the genetic algorithm for 30 iterations. It will print the result for each run and calculate the average best solution.

Input File Format
The dataset file should be structured as follows:

<num_items> <capacity>
<weight_1> <profit_1>
<weight_2> <profit_2>
...
<weight_n> <profit_n>
num_items: Number of items.
capacity: Maximum weight capacity of the knapsack.
For each item, specify its weight and profit.
Example:

10 50
10 60
20 100
30 120
...

The genetic algorithm uses the following parameters, which can be adjusted in the code:

Population Size (MAX_POPULATION): The number of solutions in the population (default: 1000).
Max Evaluations (MAX_EVALUATION): The maximum number of evaluations (default: 1000).
Crossover Rate (CROSSOVER_RATE): The probability of crossover between two solutions (default: 0.6).
Mutation Rate (MUTATION_RATE): The probability of mutating a solution (default: 0.01).
Example Output
For each iteration, the program will print the best solution found, and after all iterations, it will print the average best solution:


Best solution for iteration 1: 340
Best solution for iteration 2: 345
...
Average best solution: 342
Dependencies
Standard C++ libraries: <iostream>, <fstream>, <vector>, <string>, <bitset>, etc.
The code is written in C++ and should compile with any modern C++ compiler (e.g., g++).
Notes
The current implementation assumes that the maximum number of items in the knapsack is 32. This is due to the use of bitset<32>. If more items are required, this can be adjusted accordingly.
Make sure to provide a valid dataset file in the dataset/ folder.
