#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

using matrix_type = std::vector<std::vector<int>>;

void fill_matrix(matrix_type& matrix, const int &N);
void print_matrix(matrix_type& matrix, const int &N, const std::string &msg);
bool check_res(const matrix_type& res_seq, const matrix_type& res_par);

namespace trivial {
    matrix_type matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB);
    matrix_type matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB);
}

namespace boosted {
    matrix_type boosted_matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB, const int &N, const int& BLOCK_SIZE);
    matrix_type boosted_matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE);

    matrix_type call_boosted_matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE);
    matrix_type call_boosted_matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB, const int &N, const int& BLOCK_SIZE);
}
