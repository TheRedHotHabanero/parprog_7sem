#include <iostream>
#include <cmath>
#include <fstream>
#include <chrono>
#include <mpi.h>

const int ISIZE = 5000;
const int JSIZE = 5000;

void task_1_sequential() {
    double** a = new double*[ISIZE];
    for (int i = 0; i < ISIZE; ++i) {
        a[i] = new double[JSIZE];
    }

    int i, j;

    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }

    // Начало измерения времени
    auto start_time = std::chrono::high_resolution_clock::now();

    for (i = 1; i < ISIZE; i++) {
        for (j = 8; j < JSIZE; j++) {
            a[i][j] = sin(5 * a[i - 1][j - 8]);
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Sequential: " << duration.count() << " mls" << std::endl;

    std::ofstream ff("result_task_1_sequential.txt");
    if (!ff.is_open()) {
        std::cerr << "Error while opening file" << std::endl;
    }

    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            ff << a[i][j] << ' ';
        }
        ff << '\n';
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < ISIZE; ++i) {
        delete[] a[i];
    }
    delete[] a;
}

void task_1_parallel(int rank, int size) {
    // Вычисляем количество строк для каждого процесса
    int local_rows = ISIZE / size;

    // Выделяем память только для локальной части массива
    double** a_local = new double*[local_rows];
    for (int i = 0; i < local_rows; ++i) {
        a_local[i] = new double[JSIZE];
    }

    int i, j;

    // Создаем временный буфер для scatter и gather
    double* temp_buffer = nullptr;

    if (rank == 0) {
        double** a = new double*[ISIZE];
        for (int i = 0; i < ISIZE; ++i) {
            a[i] = new double[JSIZE];
            for (j = 0; j < JSIZE; j++) {
                a[i][j] = 10 * i + j;
            }
        }

        // Выделяем временный буфер для scatter
        temp_buffer = new double[ISIZE * JSIZE];

        // Заполняем временный буфер данными
        for (int i = 0; i < ISIZE; i++) {
            for (j = 0; j < JSIZE; j++) {
                temp_buffer[i * JSIZE + j] = a[i][j];
            }
        }

        // Освобождение выделенной памяти
        for (int i = 0; i < ISIZE; ++i) {
            delete[] a[i];
        }
        delete[] a;
    }

    // Начало измерения времени
    auto start_time = std::chrono::high_resolution_clock::now();

    // Рассылка данных из процесса 0 на все процессы
    MPI_Scatter(temp_buffer, local_rows * JSIZE, MPI_DOUBLE, a_local[0], local_rows * JSIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Освобождение временного буфера
    if (rank == 0) {
        delete[] temp_buffer;
    }

    // Распараллеливание по внешнему циклу
    for (i = 0; i < local_rows; i++) {
        for (j = 8; j < JSIZE; j++) {
            a_local[i][j] = sin(5 * a_local[i][j - 8]);
        }
    }

    // Сбор результатов обратно на процессе 0
    MPI_Gather(a_local[0], local_rows * JSIZE, MPI_DOUBLE, temp_buffer, local_rows * JSIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Запись результатов в файл
        std::ofstream ff("result_task_1_parallel.txt");
        if (!ff.is_open()) {
            std::cerr << "Error while opening file!" << std::endl;
            MPI_Finalize();
        }

        // Запись данных из временного буфера в файл
        for (int i = 0; i < ISIZE; i++) {
            for (j = 0; j < JSIZE; j++) {
                ff << temp_buffer[i * JSIZE + j] << ' ';
            }
            ff << '\n';
        }
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < local_rows; ++i) {
        delete[] a_local[i];
    }
    delete[] a_local;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        task_1_sequential();
    }

    task_1_parallel(rank, size);

    MPI_Finalize();

    return 0;
}
