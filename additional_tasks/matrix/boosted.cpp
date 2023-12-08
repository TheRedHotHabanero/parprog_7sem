#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

#include "matrix.h"

using matrix_type = std::vector<std::vector<int>>;

// Алгоритм разделяй и властвуй. Он опирается на разложение на блоки и  вычисляет элементы
// рекурсивно с помощью скалярного произведения как в базовом случае
matrix_type boosted::boosted_matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB, const int &N, const int& BLOCK_SIZE) {

    if (N <= BLOCK_SIZE) {
        // Базовый случай: выполнение обычного умножения матриц
        return trivial::matrix_multiplication_sequential(matrixA, matrixB);
    }
    
    // Рекурсивный случай: разделение матриц на подматрицы и умножение
    int new_size = N / 2;
    matrix_type matrixA11(new_size, std::vector<int>(new_size));
    matrix_type matrixA12(new_size, std::vector<int>(new_size));
    matrix_type matrixA21(new_size, std::vector<int>(new_size));
    matrix_type matrixA22(new_size, std::vector<int>(new_size));

    matrix_type matrixB11(new_size, std::vector<int>(new_size));
    matrix_type matrixB12(new_size, std::vector<int>(new_size));
    matrix_type matrixB21(new_size, std::vector<int>(new_size));
    matrix_type matrixB22(new_size, std::vector<int>(new_size));

    // Разбиение матриц на подматрицы
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrixA11[i][j] = matrixA[i][j];
            matrixA12[i][j] = matrixA[i][j + new_size];
            matrixA21[i][j] = matrixA[i + new_size][j];
            matrixA22[i][j] = matrixA[i + new_size][j + new_size];

            matrixB11[i][j] = matrixB[i][j];
            matrixB12[i][j] = matrixB[i][j + new_size];
            matrixB21[i][j] = matrixB[i + new_size][j];
            matrixB22[i][j] = matrixB[i + new_size][j + new_size];
        }
    }

    // Рекурсивно умножаем подматрицы
    matrix_type matrixRes11 = boosted_matrix_multiplication_sequential(matrixA11, matrixB11, new_size, BLOCK_SIZE);
    matrix_type matrixRes12 = boosted_matrix_multiplication_sequential(matrixA12, matrixB21, new_size, BLOCK_SIZE);
    matrix_type matrixRes21 = boosted_matrix_multiplication_sequential(matrixA21, matrixB12, new_size, BLOCK_SIZE);
    matrix_type matrixRes22 = boosted_matrix_multiplication_sequential(matrixA22, matrixB22, new_size, BLOCK_SIZE);

    // Собираем результаты в одну матрицу
    matrix_type matrixRes(N, std::vector<int>(N, 0));
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrixRes[i][j] = matrixRes11[i][j];
            matrixRes[i][j + new_size] = matrixRes12[i][j];
            matrixRes[i + new_size][j] = matrixRes21[i][j];
            matrixRes[i + new_size][j + new_size] = matrixRes22[i][j];
        }
    }
    return matrixRes;
}

// Параллельный алгоритм разделяй и властвуй. Он опирается на разложение на блоки и  вычисляет элементы
// рекурсивно с помощью скалярного произведения как в базовом случае
matrix_type boosted::boosted_matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE) {

    if (N <= BLOCK_SIZE) {
        // Базовый случай: выполнение обычного умножения матриц
        return trivial::matrix_multiplication_parallel(matrixA, matrixB);
    }
    // Рекурсивный случай: разделение матриц на подматрицы и умножение
    int new_size = N / 2;
    matrix_type matrixA11(new_size, std::vector<int>(new_size));
    matrix_type matrixA12(new_size, std::vector<int>(new_size));
    matrix_type matrixA21(new_size, std::vector<int>(new_size));
    matrix_type matrixA22(new_size, std::vector<int>(new_size));

    matrix_type matrixB11(new_size, std::vector<int>(new_size));
    matrix_type matrixB12(new_size, std::vector<int>(new_size));
    matrix_type matrixB21(new_size, std::vector<int>(new_size));
    matrix_type matrixB22(new_size, std::vector<int>(new_size));

    // Разбиение матриц на подматрицы
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrixA11[i][j] = matrixA[i][j];
            matrixA12[i][j] = matrixA[i][j + new_size];
            matrixA21[i][j] = matrixA[i + new_size][j];
            matrixA22[i][j] = matrixA[i + new_size][j + new_size];

            matrixB11[i][j] = matrixB[i][j];
            matrixB12[i][j] = matrixB[i][j + new_size];
            matrixB21[i][j] = matrixB[i + new_size][j];
            matrixB22[i][j] = matrixB[i + new_size][j + new_size];
        }
    }

    // Рекурсивно умножаем подматрицы
    matrix_type matrixRes11, matrixRes12, matrixRes21, matrixRes22;

    #pragma omp task shared(matrixRes11) 
    matrixRes11 = boosted_matrix_multiplication_parallel(matrixA11, matrixB11, new_size, BLOCK_SIZE);

    #pragma omp task shared(matrixRes12)
    matrixRes12 = boosted_matrix_multiplication_parallel(matrixA12, matrixB21, new_size, BLOCK_SIZE);

    #pragma omp task shared(matrixRes21)
    matrixRes21 = boosted_matrix_multiplication_parallel(matrixA21, matrixB12, new_size, BLOCK_SIZE);

    #pragma omp task shared(matrixRes22) 
    matrixRes22 = boosted_matrix_multiplication_parallel(matrixA22, matrixB22, new_size, BLOCK_SIZE);

    // Ждем завершения всех задач
    #pragma omp taskwait

    // Собираем результаты в одну матрицу
    matrix_type matrixRes(N, std::vector<int>(N, 0));
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            matrixRes[i][j] = matrixRes11[i][j];
            matrixRes[i][j + new_size] = matrixRes12[i][j];
            matrixRes[i + new_size][j] = matrixRes21[i][j];
            matrixRes[i + new_size][j + new_size] = matrixRes22[i][j];
        }
    }
    return matrixRes;
}