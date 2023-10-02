#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

// #pragma omp parallel proc_bind(spread) num_threads(N)

/*
#pragma omp parallel for collapse(2)
    for (i = 0; i < imax; i++) {
        for (j = 0; j < jmax; j++) {
            // какой-то код
        }
    }
*/

void fill_matrix(std::vector<std::vector<int>>& matrix, const int &N) {

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

void print_matrix(std::vector<std::vector<int>>& matrix, const int &N, const std::string &msg) {

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
    std::vector<std::vector<int>> matrixA(N, std::vector<int>(N, 0));
    std::vector<std::vector<int>> matrixB(N, std::vector<int>(N, 0));

    fill_matrix(matrixA, N);
    fill_matrix(matrixB, N);

    print_matrix(matrixA, N, "MATRIX A");
    print_matrix(matrixB, N, "MATRIX B");

    return 0;
}