#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

#include "matrix.h"

using matrix_type = std::vector<std::vector<int>>;

void fill_matrix(matrix_type& matrix, const int &N) {

    const int min_value = 1;
    const int max_value = 99;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min_value, max_value);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = distribution(gen);
        }
    }
}

void print_matrix(matrix_type& matrix, const int &N, const std::string &msg) {

    const int max_width = 5;

    std::cout << "-------" << msg << "-------" << std::endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << std::setw(max_width) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "-----------------------" << std::endl;
}

matrix_type boosted::call_boosted_matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE) {
    auto start_time_seq = std::chrono::high_resolution_clock::now();
    matrix_type matrixResultBoostSeq = boosted_matrix_multiplication_sequential(matrixA, matrixB, N, BLOCK_SIZE);
    auto end_time_seq = std::chrono::high_resolution_clock::now();
    auto duration_seq = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_seq - start_time_seq);
    std::cout << "Taken time boosted sequential: " << duration_seq.count() << " ml" << std::endl;
    return matrixResultBoostSeq;    
}

matrix_type boosted::call_boosted_matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB, const int &N, const int& BLOCK_SIZE) {
    auto start_time_par = std::chrono::high_resolution_clock::now();
    matrix_type matrixResultBoostPar = boosted_matrix_multiplication_parallel(matrixA, matrixB, N, BLOCK_SIZE);
    auto end_time_par = std::chrono::high_resolution_clock::now();
    auto duration_par = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_par - start_time_par);
    std::cout << "Taken time boosted parallel: " << duration_par.count() << " ml" << std::endl;
    return matrixResultBoostPar;
}

bool check_res(const matrix_type& res_seq, const matrix_type& res_par) {
    return (res_seq == res_par);
}