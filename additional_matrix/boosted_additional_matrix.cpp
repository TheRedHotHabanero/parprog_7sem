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
    // auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                matrixRes[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "Taken time sequential: " << duration.count() << " ml" << std::endl;

    return matrixRes;
}

matrix_type matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB) {

    const int N = matrixA.size();

    matrix_type matrixRes(N, std::vector<int>(N, 0));
    // auto start_time = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                matrixRes[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "Taken time parallel: " << duration.count() << " ml" << std::endl;

    return matrixRes;
}

// Алгоритм разделяй и властвуй. Он опирается на разложение на блоки и  вычисляет элементы
// рекурсивно с помощью скалярного произведения как в базовом случае
matrix_type boosted_matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB, const int &N, const int& BLOCK_SIZE) {

    if (N <= BLOCK_SIZE) {
        // Базовый случай: выполнение обычного умножения матриц
        return matrix_multiplication_sequential(matrixA, matrixB);
    } else {
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
}

// Параллельный алгоритм разделяй и властвуй. Он опирается на разложение на блоки и  вычисляет элементы
// рекурсивно с помощью скалярного произведения как в базовом случае
matrix_type boosted_matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE) {

    if (N <= BLOCK_SIZE) {
        // Базовый случай: выполнение обычного умножения матриц
        return matrix_multiplication_sequential(matrixA, matrixB);
    } else {
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
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixA11[i][j] = matrixA[i][j];
                        matrixB11[i][j] = matrixB[i][j];
                    }
                }
            }
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixA12[i][j] = matrixA[i][j + new_size];
                        matrixB12[i][j] = matrixB[i][j + new_size];
                    }
                }
            }
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixA21[i][j] = matrixA[i + new_size][j];
                        matrixB21[i][j] = matrixB[i + new_size][j];
                    }
                }
            }
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixA22[i][j] = matrixA[i + new_size][j + new_size];
                        matrixB22[i][j] = matrixB[i + new_size][j + new_size];
                    }
                }
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
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixRes[i][j] = matrixRes11[i][j];
                    }
                }
            }
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixRes[i][j + new_size] = matrixRes12[i][j];
                    }
                }
            }
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixRes[i + new_size][j] = matrixRes21[i][j];
                    }
                }
            }
            #pragma omp section
            {
                for (int i = 0; i < new_size; i++) {
                    for (int j = 0; j < new_size; j++) {
                        matrixRes[i + new_size][j + new_size] = matrixRes22[i][j];
                    }
                }
            }
        }
        return matrixRes;
    }
}

void call_boosted_matrix_multiplication_sequential(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE) {
    auto start_time_seq = std::chrono::high_resolution_clock::now();
    matrix_type matrixResultBoostSeq = boosted_matrix_multiplication_sequential(matrixA, matrixB, N, BLOCK_SIZE);
    auto end_time_seq = std::chrono::high_resolution_clock::now();
    auto duration_seq = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_seq - start_time_seq);
    std::cout << "Taken time boosted sequential: " << duration_seq.count() << " ml" << std::endl;
}

void call_boosted_matrix_multiplication_parallel(const matrix_type& matrixA, const matrix_type& matrixB, const int &N , const int& BLOCK_SIZE) {
    auto start_time_par = std::chrono::high_resolution_clock::now();
    matrix_type matrixResultBoostPar = boosted_matrix_multiplication_parallel(matrixA, matrixB, N, BLOCK_SIZE);
    auto end_time_par = std::chrono::high_resolution_clock::now();
    auto duration_par = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_par - start_time_par);
    std::cout << "Taken time boosted parallel: " << duration_par.count() << " ml" << std::endl;
}

bool check_res(const matrix_type& res_seq, const matrix_type& res_par) {
    return (res_seq == res_par);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cout << "There are not enough arguments. Enter Matrix Size." << std::endl;
        return 1;
    }

    if (std::atoi(argv[1]) <= 1 || std::atoi(argv[2]) <= 1 || std::atoi(argv[2]) > std::atoi(argv[1])) {
        std::cout << "Invalid arguments. Enter number more than 1." << std::endl;
        return 2;
    }
    const int N = std::atoi(argv[1]); // Размер квадратной матрицы
    const int BLOCK_SIZE = std::atoi(argv[2]); // Размер блока для разделения матриц
    // const int BLOCK_SIZE = 

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
    matrix_type matrixResultPar = matrix_multiplication_parallel(matrixA, matrixB);

    if (!check_res(matrixResultSeq, matrixResultPar)) {
        std::cout << "Invalid results." << std::endl;
        return 3;
    }

    call_boosted_matrix_multiplication_sequential(matrixA, matrixB, N, BLOCK_SIZE);
    call_boosted_matrix_multiplication_parallel(matrixA, matrixB, N, BLOCK_SIZE);

    return 0;
}