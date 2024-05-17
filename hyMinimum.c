#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>

#define ARRAY_SIZE 100000

// Function to find the minimum value in an array using OpenMP
int find_min(int *array, int size) {
    int min_value = array[0];
    #pragma omp parallel for reduction(min:min_value)
    for (int i = 1; i < size; i++) {
        if (array[i] < min_value) {
            min_value = array[i];
        }
    }
    return min_value;
}

int main(int argc, char *argv[]) {
    int rank, size, i;
    int *array = NULL;
    int local_min, global_min;
    int local_array_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_array_size = ARRAY_SIZE / size;
    int *local_array = (int *)malloc(local_array_size * sizeof(int));

    // Seed the random number generator differently in each process
    srand(time(NULL) + rank);

    // Generate the random numbers in parallel
    #pragma omp parallel for
    for (i = 0; i < local_array_size; i++) {
        local_array[i] = rand() % 1000000; // Random numbers between 0 and 999999
    }

    // Each process finds the minimum value in its local array
    local_min = find_min(local_array, local_array_size);

    // Gather the local minimums and find the global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Print the global minimum from the root process
    if (rank == 0) {
        printf("The minimum value in the array is %d\n", global_min);
    }

    // Clean up
    free(local_array);
    MPI_Finalize();

    return 0;
}

