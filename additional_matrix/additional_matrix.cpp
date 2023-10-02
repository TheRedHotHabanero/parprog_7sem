#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

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

matrix_type matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB) {

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
    std::cout << "Taken time sequential: " << duration.count() << " ml" << std::endl;

    return matrixRes;
}

matrix_type matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB) {

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
    std::cout << "Taken time parallel: " << duration.count() << " ml" << std::endl;

    return matrixRes;
}
 

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter Matrix Size." << std::endl;
        return 1;
    }

    if (std::atoi(argv[1]) <= 1) {
        std::cout << "Invalid arguments. Enter number more than 1." << std::endl;
        return 2;
    }
    const int N = std::atoi(argv[1]); // Размер квадратной матрицы

    // Создание двух квадратных матриц A и B
    matrix_type matrixA(N, std::vector<int>(N, 0));
    matrix_type matrixB(N, std::vector<int>(N, 0));

    fill_matrix(matrixA, N);
    fill_matrix(matrixB, N);

    if (N <= 25) {
        print_matrix(matrixA, N, "MATRIX A");
        print_matrix(matrixB, N, "MATRIX B");
    }

    matrix_type matrixResultSeq = matrix_multiplication_sequential(matrixA, matrixB);
    // print_matrix(matrixResultSeq, N, "RESULT MATRIX - SEQUENTIAL MODE");

    matrix_type matrixResultPar = matrix_multiplication_parallel(matrixA, matrixB);
    // print_matrix(matrixResultPar, N, "RESULT MATRIX - PARALLEL MODE");


    return 0;
}