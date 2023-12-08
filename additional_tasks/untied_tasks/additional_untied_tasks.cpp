#include <omp.h>
#include <iostream>

void safe_untied_tasks(const int& num_threads) {

    int common_variable = 0;

    #pragma omp parallel num_threads(num_threads) shared (common_variable)
    {
        int thread_num = omp_get_thread_num();

        /*
        #pragma omp critical:
            Используется для создания критических секций, где только ОДИН поток
        может выполнять код внутри этой секции в ОПРЕДЕЛЕННЫЙ момент времени.
            Гарантирует, что код внутри критической секции будет выполнен 
        только одним потоком, и остальные потоки будут ОЖИДАТЬ, 
        пока критическая секция освободится.
            Обычно используется для ПРЕДОТВРАЩЕНИЯ ГОНОК данных 
        при доступе к общим ресурсам, таким как общие переменные.
        */

        #pragma omp critical // директива, 
        {
            // Создаем две задачи типа "untied" c явной синхронизацией
            #pragma omp task
            {
                #pragma omp atomic
                common_variable += 1;
            }

            #pragma omp task
            {
                #pragma omp atomic
                common_variable *= 2; // Важен порядок, что умножается! до сложения или после. или после скольких?
            }
            // std::cout << "Thread #" << thread_num << " on line. Common variable = " << common_variable << std::endl;
            #pragma omp wait
        }
    }

    std::cout << "Safe mode. Common variable: " << common_variable << std::endl;

    return;
}

void unsafe_untied_tasks(const int& num_threads) {

    int common_variable = 0;

    #pragma omp parallel num_threads(num_threads) shared (common_variable)
    {
        int thread_num = omp_get_thread_num();


        // Создаем две задачи типа "untied" c явной синхронизацией
        #pragma omp task
        {
            #pragma omp atomic // спойлер - не спасает
            common_variable += 1;
        }

        #pragma omp task
        {
            #pragma omp atomic // спойлер - не спасает
            common_variable *= 2; // Важен порядок, что умножается! до сложения или после. или после скольких?
        }
        // std::cout << "Thread #" << thread_num << " on line. Common variable = " << common_variable << std::endl;
        #pragma omp wait
    }

    std::cout << "Unsafe mode. Common variable: " << common_variable << std::endl;

    return;
}

/*
void unsafe2_untied_tasks(const int& num_threads) {

    int common_variable = 0;

    #pragma omp parallel num_threads(num_threads) shared (common_variable)
    {
        int thread_num = omp_get_thread_num();


        // Создаем две задачи типа "untied" c явной синхронизацией
        #pragma omp task
        {
            #pragma omp atomic
            common_variable += 2;
        }

        #pragma omp task
        {
            #pragma omp atomic 
            common_variable -= 4;
        }
        // std::cout << "Thread #" << thread_num << " on line. Common variable = " << common_variable << std::endl;
    }

    std::cout << "Unsafe mode 2. Common variable: " << common_variable << std::endl;

    return;
}
*/


int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cout << "Not enough arguments. Enter number of func to use: Safe untied - 1, Unsafe untied - 2"
                  << "Then enter bumber of threads" << std::endl;
        return 1;
    }

    if (std::atoi(argv[1]) != 1 && std::atoi(argv[1]) != 2) {
        std::cout << "Invalid arguments. Number of func to use should be 1 or 2" << std::endl;
        return 2;
    }
    int func = std::atoi(argv[1]);

    if (std::atoi(argv[2]) > omp_get_thread_limit()) {
        std::cout << "Invalid arguments. Enter number of threads less than 2147483647." << std::endl;
        return 2;
    }
    const int num_threads = std::atoi(argv[2]);

    const int operations = 10;
    if (func == 1) {
        for (int i = 0; i < operations; i++) {
            safe_untied_tasks(num_threads);
        }
    } else {
        for (int i = 0; i < operations; i++) {
            unsafe_untied_tasks(num_threads);
            // unsafe2_untied_tasks(num_threads);
        }
    }

    return 0;
}
