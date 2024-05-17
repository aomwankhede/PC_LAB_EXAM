#include <omp.h>
#include <stdio.h>
#include <math.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    long long n = 100; // Number of intervals
    double a = 0.0, b = 1.0; // Integration interval
    double h = (b - a) / n; // Width of each interval
    double sum = 0.0;
    int i;

    // Start timing
    double start_time = omp_get_wtime();

    // Parallelize the loop with OpenMP
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    // Multiply the sum by the width of each interval
    double pi = sum * h;

    // End timing
    double end_time = omp_get_wtime();
    double time_taken = end_time - start_time;

    // Print the result
    printf("Approximate value of pi: %.16f\n", pi);
    printf("Time taken: %.6f seconds\n", time_taken);

    return 0;
}

