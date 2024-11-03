#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>
#include <stdlib.h> 

double f(double x) {
    return log(x) / x;
}

void get_input(int *n, int *num_threads) {
    printf("\n----------------------  start program  ----------------------\n\n ");
    
    printf("Enter the number of rectangles (e.g., 10000, 1000000, ...): ");
    if (scanf("%d", n) != 1) {
        fprintf(stderr, "Error reading the number of rectangles.\n");
        exit(1);
    }

    printf("Enter the number of threads: ");
    if (scanf("%d", num_threads) != 1) {
        fprintf(stderr, "Error reading the number of threads.\n");
        exit(1);
    }
}

double calculate_area(double a, double b, int n, int num_threads) {
    double width = (b - a) / n;
    double total_area = 0.0;

    double start_time = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        double partial_area = 0.0;
        double thread_start_time = omp_get_wtime();
        
        #pragma omp for
        for (int i = 0; i < n; i++) {
            double x = a + i * width;
            partial_area += f(x) * width;
        }

        double thread_end_time = omp_get_wtime();

        #pragma omp critical
        {
            total_area += partial_area;
            printf("Thread %d contributed area: %f, Time taken: %f seconds\n", thread_id, partial_area, thread_end_time - thread_start_time);
        }
    }

    double end_time = omp_get_wtime();
    printf("Total computation time: %f seconds\n", end_time - start_time);

    return total_area;
}

void display_results(double area) {
    printf("\n----------------------   results  ----------------------\n\n ");
    printf("Approximate area under the curve: %f\n", area);
    printf("\n----------------------   end results   ----------------------\n\n ");
}

int main() {
    double a = 1.0;
    double b = 10.0;
    int n;               // mumber of rectangles
    int num_threads;     // number of threads

    get_input(&n, &num_threads);

    double area = calculate_area(a, b, n, num_threads);

    display_results(area);

    return 0;
}

