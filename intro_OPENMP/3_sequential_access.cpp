#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {

    int common_variable = 0;

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter number of threads." << std::endl;
        return 1;
    }

    const int num_threads = std::atoi(argv[1]); // Количество потоков

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_num = omp_get_thread_num();

        #pragma omp critical // Обеспечение атомарности
        {
            common_variable++;
            std::cout << "Thread #" << thread_num << " on line. Common variable = " << common_variable << std::endl;
        }
    }

    return 0;
}
