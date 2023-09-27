#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {

    int nested = omp_get_nested();

    if (nested <= 0) {
        omp_set_nested(1); // Enable nesting if off. Any non-nullable value turns nesting on
        omp_set_dynamic(0); // Enable changing number of threads which are available in future parallel regions white executing
    }

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter number of threads." << std::endl;
        return 1;
    }

    // должно отпачковываться, и на каждом уровне количество потоков суммарно есть прошлое умноженное на нынешнее

    int threads_from_user = std::atoi(argv[1]);

    const int level_1 = 5;
    const int level_2 = 3;
    const int level_3 = 2;

    int counter = 0;

    // why only 8 left?? but more than 8 left when nesting is off
    #pragma omp parallel shared(counter) num_threads(level_1)
    {
        int thread_num_1 = omp_get_thread_num(); // using omp funcs
        int num_threads_1 = omp_get_num_threads(); // Returns the number of threads in the team currently executing the parallel region from which it is called
        #pragma omp critical // Using for preventing conflicts in out stream
        {
            counter +=1;
            std::cout << "Thread num = " << thread_num_1
                      << ". Summ of threads on this level = " << num_threads_1
                      << ". Level of nesting = " << omp_get_level() << std::endl;
        }
        #pragma omp parallel shared(counter, thread_num_1, num_threads_1)
        {
            int thread_num_2 = omp_get_thread_num() + omp_get_num_threads() * thread_num_1; // using omp funcs
            int num_threads_2 = omp_get_num_threads() * num_threads_1; // Returns the number of threads in the team currently executing the parallel region from which it is called
            #pragma omp critical // Using for prevent conflicts in out stream
            {
                counter += 1;
                std::cout << "Thread num = " << thread_num_2
                          << ". Summ of threads on this level = " << num_threads_2 
                          << ". Summ of threads on the previous level = " << num_threads_1
                          << ". Level of nesting = " << omp_get_level() << std::endl;
            }

            #pragma omp parallel shared(counter, thread_num_2, num_threads_2)
            {
                int thread_num_3 = omp_get_thread_num() + omp_get_num_threads() * thread_num_2; // using omp funcs
                int num_threads_3 = omp_get_num_threads() * num_threads_2; // Returns the number of threads in the team currently executing the parallel region from which it is called
                #pragma omp critical // Using for prevent conflicts in out stream
                {
                    counter += 1;
                    std::cout << "Thread num = " << thread_num_3
                              << ". Summ of threads on this level = " << num_threads_3
                              << ". Summ of threads on the previous level = " << num_threads_1
                              << ". Level of nesting = " << omp_get_level() << std::endl;
                }
            }
        }
    }

    return 0;
}
