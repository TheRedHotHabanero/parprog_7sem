#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter N." << std::endl;
        return 1;
    }

    int N = std::atoi(argv[1]);
    long double sum = 0.0;
    int num_threads_to_print = 0;

    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads(); // Returns the number of threads in the team currently executing the parallel region from which it is called
        int thread_num = omp_get_thread_num(); // Returns the number of the currently executing thread within the team
        double thread_sum = 0.0;

        num_threads_to_print = num_threads;

        for (int i = thread_num + 1; i <= N; i += num_threads) {
            thread_sum += 1.0 / i;
        }

        #pragma omp critical
        {
            sum += thread_sum;
        }
    }

    std::cout << "Sum of 1/n for n from 1 to " << N << " is " << sum << std::endl;
    std::cout << "Used " << num_threads_to_print << " threads to count. " << std::endl;

    return 0;
}
