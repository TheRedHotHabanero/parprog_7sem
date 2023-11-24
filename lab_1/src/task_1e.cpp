#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

const int ISIZE = 5000;
const int JSIZE = 5000;

void task_1_sequential() {
    double** a = new double*[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
    }

    std::ofstream ff("result_task_1_sequential.txt");

    // Инициализация массива
    for (int i = 0; i < ISIZE; ++i)
    {
        for (int j = 0; j < JSIZE; ++j)
        {
            a[i][j] = 10 * i + j;
        }
    }

    // Начало измерения времени
    auto start_time = std::chrono::high_resolution_clock::now();

    // Часть кода для измерения времени
    for (int i = 0; i < ISIZE - 4; ++i)
    {
        for (int j = 0; j < JSIZE - 2; ++j)
        {
            a[i][j] = std::sin(0.1 * a[i + 4][j + 2]);
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Sequential: " << duration.count() << " mls" << std::endl;

    // Запись результатов в файл
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            ff << a[i][j] << ' ';
        }
        ff << '\n';
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < ISIZE; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
}

void task_1_parallel() {

    double **a = new double *[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
    }

    std::ofstream ff("result_task_1_parallel.txt");

    // Инициализация массива
    for (int i = 0; i < ISIZE; ++i)
    {
        for (int j = 0; j < JSIZE; ++j)
        {
            a[i][j] = 10 * i + j;
        }
    }

    // Начало измерения времени
    auto start_time = std::chrono::high_resolution_clock::now();

    // Часть кода для измерения времени с использованием OpenMP
    #pragma omp parallel for collapse(2) shared(a) schedule(static)
    for (int i = 0; i < ISIZE - 4; ++i)
    {
        for (int j = 0; j < JSIZE - 2; ++j)
        {
            double temp = std::sin(0.1 * a[i + 4][j + 2]);
            #pragma omp atomic write
            a[i][j] = temp;
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Parallel: " << duration.count() << " mls" << std::endl;

    // Запись результатов в файл
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            ff << a[i][j] << ' ';
        }
        ff << '\n';
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < ISIZE; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
}

int main() {
    task_1_sequential();
    task_1_parallel();

    return 0;
}