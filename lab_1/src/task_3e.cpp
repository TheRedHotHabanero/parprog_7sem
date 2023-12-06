#include <iostream>
#include <fstream>
#include <cmath>

const int ISIZE = 5000;
const int JSIZE = 5000;

void task_3_sequential() {
    double a[ISIZE][JSIZE], b[ISIZE][JSIZE];

    // Инициализация массивов
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
            b[i][j] = 0;
        }
    }

    // Начало измерения времени

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

    // Запись результатов в файл
    std::ofstream ff("result.txt");
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            ff << b[i][j] << ' ';
        }
        ff << '\n';
    }
    ff.close();
}

void task_2_parallel() {
    double a[ISIZE][JSIZE], b[ISIZE][JSIZE];

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
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            a[i][j] = sin(0.002 * a[i][j]);
        }
    }

    // Обработка массива b параллельно с копированием данных
    #pragma omp parallel for
    for (int i = 0; i < ISIZE - 4; i++) {
        #pragma omp simd
        for (int j = 1; j < JSIZE; j++) {
            b[i][j] = a[i + 4][j - 1] * 1.5;
        }
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Параллельно: " << duration.count() << " мс" << std::endl;

    // Запись результатов в файл
    std::ofstream ff("result_parallel.txt");
    for (int i = 0; i < ISIZE; i++) {
        for (int j = 0; j < JSIZE; j++) {
            ff << b[i][j] << ' ';
        }
        ff << '\n';
    }
    ff.close();

    return 0;
}