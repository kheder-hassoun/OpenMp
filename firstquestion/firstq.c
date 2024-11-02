#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>
//  the function f(x) = ln(x) / x
double f(double x) {
    return log(x) / x;
}

// here we calculate the area under the curve using the Riemann sum method
double calculate_area(double a, double b, int n, int num_threads) {
    double width = (b - a) / n;
    double total_area = 0.0;

    // Start timer
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

    // eend timer
    double end_time = omp_get_wtime();
    printf("Total computation time: %f seconds\n", end_time - start_time);

    return total_area;
}

int main() {
    double a = 1.0;
    double b = 10.0;
    int n;               // number of rectangles
    int num_threads;    

  printf("\n----------------------  start program  ----------------------\n\n ");
    printf("Enter the number of rectangles like (10000, 1000000 , ....) : ");
if (scanf("%d", &n) != 1) {
    fprintf(stderr, "Error reading the number of rectangles.\n");
    return 1;  
}
    printf("Enter the number of threads:  ");
    if (scanf("%d", &num_threads) != 1) {
    fprintf(stderr, "Error reading the number of threads.\n");
    return 1;  // Exit with an error code
}
    printf("\n----------------------   results  ----------------------\n\n ");

    double area = calculate_area(a, b, n, num_threads);
    printf("Approximate area under the curve: %f\n", area);
    printf("\n----------------------   gprof results  ----------------------\n\n ");
    return 0;
}
