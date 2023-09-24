#include <omp.h>
#include <iostream>

/* #pragma omp parallel
{
// Код внутри блока выполняется параллельно.
printf("Hello! \n");
}
*/

// gcc --fopenmp

int main() {
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num(); // using omp funcs
        int num_threads = omp_get_num_threads(); // using omp funcs again
        
        #pragma omp critical // эта штука нужна для избавления от конфликтов доступа к потоку вывода
        {
            std::cout << "I`m thread #" << thread_num << " . But we have " << num_threads
                      << " threads in summ. Hello World!!!" << std::endl;
        }
    }

    return 0;
}