#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

const int ISIZE = 5000;
const int JSIZE = 5000;
void task_3_sequential() {
    double** a = new double*[ISIZE];
    double** b = new double*[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
        b[i] = new double[JSIZE];
    }

    // Инициализация массивов
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
            b[i][j] = 0;
        }
    }

    // Начало измерения времени
    auto start_time = std::chrono::high_resolution_clock::now();

    // Обработка массива a
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            a[i][j] = sin(0.002 * a[i][j]);
        }
    }

    // Обработка массива b
    for (int i = 0; i < ISIZE - 4; i++) {
        for (int j = 1; j < JSIZE; j++) {
            b[i][j] = a[i + 4][j - 1] * 1.5;
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Sequential: " << duration.count() << " mls" << std::endl;

    // Запись результатов в файл
    std::ofstream ff("result_task_3_sequential.txt");
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            ff << b[i][j] << ' ';
        }
        ff << '\n';
    }
    ff.close();
}

void task_3_parallel() {
    double** a = new double*[ISIZE];
    double** b = new double*[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
        b[i] = new double[JSIZE];
    }

    std::ofstream ff("result_task_3_parallel.txt");

    // Инициализация массивов
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
            b[i][j] = 0;
        }
    }

    // Начало измерения времени
    auto start_time = std::chrono::high_resolution_clock::now();

    // Обработка массива a параллельно
    // Основной цикл для параллелизма
    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            a[i][j] = sin(0.002 * a[i][j]);
        }
    }

    // Барьерная синхронизация между циклами
    #pragma omp barrier

    // Обработка массива b параллельно с копированием данных
    #pragma omp parallel for // от этого есть прирост, но не великий
    for (int i = 0; i < ISIZE - 4; i++) {
        for (int j = 1; j < JSIZE; j++) {
            b[i][j] = a[i + 4][j - 1] * 1.5;
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Parallel: " << duration.count() << " mls" << std::endl;

    // Запись результатов в файл
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            ff << b[i][j] << ' ';
        }
        ff << '\n';
    }
    ff.close();
}

int main() {
    task_3_sequential();
    task_3_parallel();

    return 0;
}