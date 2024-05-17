#include <mpi.h>
#include <stdio.h>
#include <math.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int rank, size, i;
    long long n = 100000; // Number of intervals
    double local_sum = 0.0, total_sum = 0.0;
    double a = 0.0, b = 1.0; // Integration interval
    double h = (b - a) / n; // Width of each interval

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process calculates its portion of the sum
    for (i = rank; i < n; i += size) {
        double x = a + (i + 0.5) * h;
        local_sum += f(x);
    }

    // Multiply the sum by the width of each interval
    local_sum *= h;

    // Reduce all local sums to a total sum in process 0
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 prints the result
    if (rank == 0) {
        printf("Approximate value of pi: %.16f\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}

