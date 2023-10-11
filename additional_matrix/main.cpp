#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

#include "matrix.h"

using matrix_type = std::vector<std::vector<int>>;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter Matrix Size." << std::endl;
        return 1;
    }

    /* Оставим на случай, если понадобится ручной ввод размера блоков
    if (argc != 3) {
        std::cout << "There are not enough arguments. Enter Matrix Size and size of blocks." << std::endl;
        return 1;
    }

    if (std::atoi(argv[1]) <= 1 || std::atoi(argv[2]) <= 1 || std::atoi(argv[2]) > std::atoi(argv[1])) {
        std::cout << "Invalid arguments. Enter number more than 1." << std::endl;
        return 2;
    }
    */
    if (std::atoi(argv[1]) <= 1) {
        std::cout << "Invalid arguments. Enter number more than 1." << std::endl;
        return 2;
    }
    const int N = std::atoi(argv[1]); // Размер квадратной матрицы
    // const int BLOCK_SIZE = std::atoi(argv[2]); // Размер блока для разделения матриц
    const int BLOCK_SIZE = 100; // Размер блока для разделения матриц

    // Создание двух квадратных матриц A и B
    matrix_type matrixA(N, std::vector<int>(N, 0));
    matrix_type matrixB(N, std::vector<int>(N, 0));

    fill_matrix(matrixA, N);
    fill_matrix(matrixB, N);

    if (N <= 25) {
        print_matrix(matrixA, N, "MATRIX A");
        print_matrix(matrixB, N, "MATRIX B");
    }

    /*
    matrix_type matrixResultSeq = trivial::matrix_multiplication_sequential(matrixA, matrixB);
    matrix_type matrixResultPar = trivial::matrix_multiplication_parallel(matrixA, matrixB);

    if (!check_res(matrixResultSeq, matrixResultPar)) {
        std::cout << "Invalid results for trivial." << std::endl;
        return 3;
    }
    */

    matrix_type matrixResultSeqBoosted = boosted::call_boosted_matrix_multiplication_sequential(matrixA, matrixB, N, BLOCK_SIZE);
    matrix_type matrixResultParBoosted = boosted::call_boosted_matrix_multiplication_parallel(matrixA, matrixB, N, BLOCK_SIZE);

    if (!check_res(matrixResultSeqBoosted, matrixResultParBoosted)) {
        std::cout << "Invalid results for boosted." << std::endl;
        return 4;
    }

    return 0;
}