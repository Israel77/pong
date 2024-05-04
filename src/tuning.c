/**
* Genetic algorithm for tuning the PID Controller
*/
#include "ai/battle.h"
#include "ai/pid.h"
#include <assert.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

const int POPULATION_SIZE = 128;
const int POOL_SIZE = 16;
const int NUM_GENERATIONS = 100;
const double MUTATION_RATE = 0.02f;

typedef struct {
	PIDController controller;
	int fitness;
} Candidate;

/**
 * Merges two sorted subarrays of the input population array into a single sorted subarray in the output array.
 *
 * This function is a helper for the _mergeSort function, performing the merge step of the merge sort algorithm.
 *
 * @param input The original population array.
 * @param output The output array to store the merged subarray.
 * @param pLeft Pointer to the start index of the left subarray.
 * @param endLeft Index of the end of the left subarray.
 * @param pRight Pointer to the start index of the right subarray.
 * @param endRight Index of the end of the right subarray.
 * @param writePosition The index in the output array to write the merged subarray.
 */
void _mergeSortedArrays(Candidate *input, Candidate *output, int *pLeft,
			int endLeft, int *pRight, int endRight,
			int writePosition)
{
	if (
		// Get value from left iff there are elements left on the left side
		*pLeft < endLeft &&
		// and either the left side is bigger than the right side
		(input[*pLeft].fitness > input[*pRight].fitness ||
		 // or the right side has no elements left
		 *pRight >= endRight)) {
		output[writePosition] = input[*pLeft];
		(*pLeft)++;
	} else if (*pRight < endRight) {
		output[writePosition] = input[*pRight];
		(*pRight)++;
	}
}

/**
 * Merge two sorted subarrays of the population array into a single sorted array.
 *
 * This function is used as a helper function by the _mergeSort function to
 * perform the merge step of the merge sort algorithm.
 *
 * @param population The original population array.
 * @param partitionSize The size of each subarray to be merged.
 * @param totalSize The total size of the population array.
 * @return A new sorted array containing the merged subarrays.
 *
 * Time complexity: O(n), where n is the total size of the population array.
 * Space complexity: O(n), as a new auxiliary array of size n is created.
 */
Candidate *_merge(Candidate *population, int partitionSize, int totalSize)
{
	// Auxiliary array used by the mergesort algorithm
	Candidate *auxiliary = malloc(sizeof(Candidate) * totalSize);
	int writePosition = 0;

	for (int i = 0; i <= totalSize; i += 2 * partitionSize) {
		int pLeft = i;
		int endLeft = i + partitionSize;

		int pRight = i + partitionSize;
		int endRight = i + 2 * partitionSize;

		while (writePosition < totalSize &&
		       (pLeft < endLeft || pRight < endRight)) {
			_mergeSortedArrays(population, auxiliary, &pLeft,
					   endLeft, &pRight, endRight,
					   writePosition);
			writePosition++;
		}
	}

	return auxiliary;
}

/**
 * Reverse sorts the given population of candidates by fitness
 * using a merge sort algorithm.
 *
 * @param population The population of candidates to be sorted.
 * @return The sorted population of candidates.
 */
Candidate *_mergeSort(Candidate *population)
{
	for (int p = 1; p < POPULATION_SIZE; p *= 2) {
		population = _merge(population, p, POPULATION_SIZE);
	}
	return population;
}

/**
 * Initializes a population of candidate solutions for a genetic algorithm.
 *
 * This function allocates memory for a population of candidate solutions, and
 * initializes each candidate with random values for the PID controller
 * parameters (kp, ki, kd). The fitness of each candidate is initially set to 0.
 *
 * The function then prints the initial values of the PID controller parameters
 * for each candidate in the population.
 *
 * @return A pointer to the initialized population of candidates.
 */
Candidate *initPopulation()
{
	Candidate *population = malloc(sizeof(Candidate) * POPULATION_SIZE);

	for (int i = 0; i < POPULATION_SIZE; i++) {
		population[i].controller = (PIDController){
			.kp = -10. + (double)rand() / RAND_MAX * 20.0f,
			.ki = -10. + (double)rand() / RAND_MAX * 20.0f,
			.kd = -10. + (double)rand() / RAND_MAX * 20.0f,
		};
		population[i].fitness = 0;
	}

	printf("Initial population:");
	for (int i = 0; i < POPULATION_SIZE; i++) {
		printf("[%f, %f, %f]\n", population[i].controller.kp,
		       population[i].controller.ki,
		       population[i].controller.kd);
	}

	return population;
}

/**
 * Selects the POOL_SIZE fittest candidates from the given population.
 *
 * @param population The population of candidates to select the fittest from.
 * @return A newly allocated array of the POOL_SIZE fittest candidates.
 */
Candidate *selectFittest(Candidate *population)
{
	// Ensure that the pool size is not larger than the population size
	assert(POOL_SIZE <= POPULATION_SIZE);

	population = _mergeSort(population);

	Candidate *fittest = malloc(sizeof(Candidate) * POOL_SIZE);
	for (int i = 0; i < POOL_SIZE; i++) {
		fittest[i] = population[i];
	}

	return fittest;
}

/**
 * Performs crossover between the fittest candidates in the population to produce
 * a new generation of offspring.
 *
 * @param fittest The fittest candidates in the population.
 * @return A new array of offspring candidates.
 */
Candidate *crossover(Candidate *fittest)
{
	Candidate *offspring = malloc(sizeof(Candidate) * POPULATION_SIZE);

	for (int i = 0; i < POPULATION_SIZE; i++) {
		int parent1 = rand() % POOL_SIZE;
		int parent2 = rand() % POOL_SIZE;

		offspring[i].controller.kp = (fittest[parent1].controller.kp +
					      fittest[parent2].controller.kp) /
					     2.0;

		offspring[i].controller.ki = (fittest[parent1].controller.ki +
					      fittest[parent2].controller.ki) /
					     2.0;

		offspring[i].controller.kd = (fittest[parent1].controller.kd +
					      fittest[parent2].controller.kd) /
					     2.0;

		offspring[i].fitness = 0;
	}

	return offspring;
}

/**
 * Mutates the given population of candidates by randomly adjusting the PID
 * controller parameters of each candidate.
 *
 * @param offspring The population of candidates to mutate.
 * @return The mutated population of candidates.
 */
Candidate *mutate(Candidate *offspring)
{
	for (int i = 0; i < POPULATION_SIZE; i++) {
		if ((double)rand() / RAND_MAX < MUTATION_RATE) {
			offspring[i].controller.kp +=
				(double)rand() / RAND_MAX * 2.5;
			offspring[i].controller.ki +=
				(double)rand() / RAND_MAX * 2.5;
			offspring[i].controller.kd +=
				(double)rand() / RAND_MAX * 2.5;
		}
	}

	return offspring;
}

/**
 * Helper function for updateFitness.
 * Increments the fitness of the candidates based on the result of their battle.
 *
 * @param player1 Pointer to the first candidate.
 * @param player2 Pointer to the second candidate.
 * @param result Pointer to the result of the battle between the two candidates.
 */
void incrementFitness(Candidate *player1, Candidate *player2, Result *result)
{
	if (result->forcedFinish) {
		int totalScore = result->player1Score + result->player2Score;

		if (totalScore == 0)
			return;

		player1->fitness += result->player1Score * 100 / totalScore;
		player2->fitness += result->player2Score * 100 / totalScore;
	} else if (result->player1Score > result->player2Score) {
		player1->fitness += 100;
	} else {
		player2->fitness += 100;
	}
}

/**
 * Performs a swiss-style tournament to update the fitness of the candidates in the population.
 *
 * The function creates pairings of candidates, simulates a battle between them, and updates their fitness
 * based on the result of the battle. The battle is simulated by calling the `battle()` function, which
 * compares the performance of the two candidates' PID controllers.
 *
 * @param population The array of candidates in the population.
 */
void updateFitness(Candidate *population)
{
	// Create the pairings for a swiss-style tournament
	int pairings[POPULATION_SIZE / 2][2];
	for (int i = 0; i < POPULATION_SIZE / 2; i++) {
		pairings[i][0] = i * 2;
		pairings[i][1] = i * 2 + 1;
	}

	// For each pairing, simulate a battle and update the fitness
	for (int i = 0; i < POPULATION_SIZE / 2; i++) {
		int player1 = pairings[i][0];
		int player2 = pairings[i][1];

		PIDController *controller1 = &population[player1].controller;
		PIDController *controller2 = &population[player2].controller;

		// printf("Starting battle between player [%f, %f, %f] and player [%f, %f, %f]\n",
		//        controller1->kp, controller1->ki, controller1->kd,
		//        controller2->kp, controller2->ki, controller2->kd);

		Result result = battle(controller1, controller2);

		incrementFitness(&population[player1], &population[player2],
				 &result);

		// printf("=== Results ===\n");
		// printf("[%f, %f, %f] -> %i(%i)\n", controller1->kp,
		//        controller1->ki, controller1->kd, result.player1Score,
		//        population[player1].fitness);
		// printf("[%f, %f, %f] -> %i(%i)\n", controller2->kp,
		//        controller2->ki, controller2->kd, result.player2Score,
		//        population[player2].fitness);
		// printf("======= \n");
	}
}

int main(void)
{
	Candidate *population = initPopulation();

	for (int generation = 0; generation < NUM_GENERATIONS; generation++) {
		// printf("Starting generation: %d\n", generation);

		updateFitness(population);
		Candidate *fittest = selectFittest(population);

		// Generates offspring in all generations but the last one
		if (generation < NUM_GENERATIONS - 1) {
			Candidate *offspring = mutate(crossover(fittest));
			population = offspring;
		}
	}

	printf("Results: \n");
	population = _mergeSort(population);
	for (int i = 0; i < POPULATION_SIZE; i++) {
		Candidate candidate = population[i];
		printf("[%f, %f, %f] (%i)\n", candidate.controller.kp,
		       candidate.controller.ki, candidate.controller.kd,
		       candidate.fitness);
	}

	free(population);
	return 0;
}
