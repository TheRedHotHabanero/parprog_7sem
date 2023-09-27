#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {

    int nested = omp_get_nested();

    if (nested <= 0) {
        omp_set_nested(1); // Enable nesting if off. Any non-nullable value turns nesting on
        omp_set_dynamic(1); // Enable changing number of threads which are available in future parallel regions white executing
    }

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter number of threads." << std::endl;
        return 1;
    }

    // должно отпачковываться, и на каждом уровне количество потоков суммарно есть прошлое умноженное на нынешнее

    int threads_from_user = std::atoi(argv[1]);
    // omp_get_thread_limit()

    std::cout << threads_from_user << " threads_from_user" << std::endl;

    const int level_1 = 1;
    const int level_2 = 2;
    const int level_3 = 3;

    // why only 8 left?? but more than 8 left when nesting is off
    omp_set_num_threads(threads_from_user - level_1); // Set number of threads to see difference in levels
    #pragma omp parallel
    {
        omp_set_num_threads(threads_from_user - level_2); // Set number of threads to see difference in levels
        #pragma omp critical // Using for prevent conflicts in out stream
        {
            std::cout << "Thread num = " << omp_get_thread_num() 
                      << ". Summ of threads on this level = " << omp_get_num_threads() 
                      << ". Summ of threads on the previous level = "
                      << ". Level of nesting = " << omp_get_level() << std::endl;
        }
        #pragma omp parallel
        {
            omp_set_num_threads(threads_from_user - level_3); // Set number of threads to see difference in levels
            #pragma omp critical // Using for prevent conflicts in out stream
            {
                std::cout << "Thread num = " << omp_get_thread_num() 
                          << ". Summ of threads on this level = " << omp_get_num_threads() 
                          << ". Summ of threads on the previous level = "
                          << ". Level of nesting = " << omp_get_level() << std::endl;
            }

            #pragma omp parallel
            {
                #pragma omp critical // Using for prevent conflicts in out stream
                {
                    std::cout << "Thread num = " << omp_get_thread_num() 
                              << ". Summ of threads on this level = " << omp_get_num_threads()
                              << ". Summ of threads on the previous level = "
                              << ". Level of nesting = " << omp_get_level() << std::endl;
                }
            }
        }
    }

    return 0;
}
