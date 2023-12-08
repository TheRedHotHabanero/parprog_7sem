#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

#include "matrix.h"

using matrix_type = std::vector<std::vector<int>>;

matrix_type trivial::matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB) {

    const int N = matrixA.size();

    matrix_type matrixRes(N, std::vector<int>(N, 0));
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                matrixRes[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "Taken time sequential: " << duration.count() << " ml" << std::endl;

    return matrixRes;
}

matrix_type trivial::matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB) {

    const int N = matrixA.size();

    matrix_type matrixRes(N, std::vector<int>(N, 0));
    auto start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                matrixRes[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "Taken time parallel: " << duration.count() << " ml" << std::endl;

    return matrixRes;
}