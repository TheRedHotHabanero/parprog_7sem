#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

const int ISIZE = 5000;
const int JSIZE = 5000;


void example_parallel() {
    double** a = new double*[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
    }

    std::ofstream ff("result_example_parallel.txt");

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
    #pragma omp parallel for
    for (int i = 0; i < ISIZE; ++i)
    {
        #pragma omp parallel for
        for (int j = 0; j < JSIZE; ++j)
        {
            a[i][j] = std::sin(2 * a[i][j]);
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Parallel: " << duration.count() << " mls" << std::endl;

    // Запись результатов в файл
    for (int i = 0; i < ISIZE; ++i)
    {
        for (int j = 0; j < JSIZE; ++j)
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

void example_sequential() {
    double** a = new double*[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
    }

    std::ofstream ff("result_example_sequential.txt");

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
    for (int i = 0; i < ISIZE; ++i)
    {
        for (int j = 0; j < JSIZE; ++j)
        {
            a[i][j] = std::sin(2 * a[i][j]);
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Sequential: " << duration.count() << " mls" << std::endl;

    // Запись результатов в файл
    for (int i = 0; i < ISIZE; ++i)
    {
        for (int j = 0; j < JSIZE; ++j)
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
    example_sequential();
    example_parallel();
    return 0;
}
