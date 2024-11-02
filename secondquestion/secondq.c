#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <complex.h>
#include <time.h>

// Define the bounds for the area in the complex plane to sample
#define X_MIN -2.0
#define X_MAX 2.0
#define Y_MIN -2.0
#define Y_MAX 2.0

// Function to determine if a complex number is in the Mandelbrot set
int is_in_mandelbrot(double complex c) {
    double complex z = 0;
    int max_iterations = 1000;
    for (int i = 0; i < max_iterations; i++) {
        z = z * z + c;
        if (cabs(z) > 2) return 0;
    }
    return 1;
}

// Monte Carlo approximation function
double monte_carlo_mandelbrot(int num_points, int num_threads) {
    int count_in_set = 0;

    #pragma omp parallel for num_threads(num_threads) reduction(+:count_in_set)
    for (int i = 0; i < num_points; i++) {
        double x = X_MIN + (X_MAX - X_MIN) * (double)rand() / RAND_MAX;
        double y = Y_MIN + (Y_MAX - Y_MIN) * (double)rand() / RAND_MAX;
        double complex c = x + y * I;

        if (is_in_mandelbrot(c)) {
            count_in_set++;
        }
    }

    double area = ((X_MAX - X_MIN) * (Y_MAX - Y_MIN)) * (double)count_in_set / num_points;
    return area;
}

int main() {
    int num_points = 10000000;  // Total number of points
    int num_threads = 4;        // Set this to the number of available CPUs or experiment with different values

    srand(time(NULL)); // Seed the random number generator

    printf("Sequential calculation:\n");
    double start_time = omp_get_wtime();
    double area_seq = monte_carlo_mandelbrot(num_points, 1);
    double time_seq = omp_get_wtime() - start_time;
    printf("Estimated area (sequential): %f\n", area_seq);
    printf("Time (sequential): %f seconds\n", time_seq);

    printf("\nParallel calculation with %d threads:\n", num_threads);
    start_time = omp_get_wtime();
    double area_par = monte_carlo_mandelbrot(num_points, num_threads);
    double time_par = omp_get_wtime() - start_time;
    printf("Estimated area (parallel): %f\n", area_par);
    printf("Time (parallel): %f seconds\n", time_par);

    double speedup = time_seq / time_par;
    printf("\nSpeedup: %f\n", speedup);

    return 0;
}
