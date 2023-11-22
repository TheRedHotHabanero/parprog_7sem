#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <cmath>

void sieveOfEratosthenes(long long int n) {
    // Create Vector to store information about primary numbers
    std::vector<bool> isPrime(n + 1, 1);

    // Lets start from the very first primary number - 2
    // Начинаем с первого простого числа - 2
    for (long long int p = 2; p <= n; p++) {
        // Если текущее число p еще не было отмечено, как составное
        if (isPrime[p]) {
            // Отмечаем все кратные p как составные числа
            for (int i = std::pow(p, 2); i <= n; i += p) {
                // isPrime[i] = 0;
            }
        }
    }

    // Represent all primary numbers
    //std::cout << "Primary numbers from N = " << n << ":" << std::endl;
    // int primary_counter = 0;
    // for (int p = 2; p <= n; p++) {
    //     if (isPrime[p]) {
    //         // std::cout << p << " ";
    //         primary_counter += 1;
    //     }
    // }
    // std::cout << std::endl;
    // std::cout << "Sequential: Quantity of primary numbers is " << primary_counter << "." << std::endl;
}

void parallelSieveOfEratosthenes(long long int n) {
    // Создаем вектор для хранения информации о простых числах
    std::vector<bool> isPrime(n + 1, 1);
    int sqrt_n = std::sqrt(n) + 1;
    #pragma opm sections
    {
        #pragma omp sections
        {
            #pragma omp parallel for schedule(dynamic) shared(isPrime)
            for (int i = 2; i <= n; i+=2) {
                isPrime[i] = 0;
            }
        }
        // Начинаем с первого простого числа - 2
        #pragma omp sections
        {
            for (int p = 3; p * p <= n; p+=2) {
                // Если текущее число p еще не было отмечено, как составное
                if (isPrime[p]) {
                    // Пропускаем кратные числа p, начиная с p^2
                    #pragma omp parallel for schedule(dynamic) shared(isPrime) firstprivate(p)
                    for (int i = p * p; i <= n; i += p) {
                        // isPrime[i] = 0;
                    }
                }
            }
        }
    }

    // Выводим простые числа (можете закомментировать эту часть, если не нужно выводить числа)
    // std::cout << "Primary numbers for N = " << n << ":" << std::endl;
    // int primary_counter = 1;
    // #pragma omp parallel for schedule(dynamic) shared(isPrime)
    // for (int p = 2; p <= n; p++) {
    //     if (isPrime[p]) {
    //         // std::cout << p << " ";
    //         primary_counter++;
    //     }
    // }
    // std::cout << std::endl;
    // std::cout << "Parallel: Quantity of primary numbers is " << primary_counter << "." << std::endl;
}

int main() {
    // Enter N number
    long long int N;
    std::cout << "Enter number N: ";
    std::cin >> N;

    // Замеряем время выполнения для параллельной версии
    auto startParallel = std::chrono::high_resolution_clock::now();
    parallelSieveOfEratosthenes(N);
    auto stopParallel = std::chrono::high_resolution_clock::now();
    auto durationParallel = std::chrono::duration_cast<std::chrono::milliseconds>(stopParallel - startParallel);
    std::cout << "Parallel taken time: " << durationParallel.count() << " mcs" << std::endl;

    // Замеряем время выполнения для последовательной версии
    auto startSequential = std::chrono::high_resolution_clock::now();
    sieveOfEratosthenes(N);
    auto stopSequential = std::chrono::high_resolution_clock::now();
    auto durationSequential = std::chrono::duration_cast<std::chrono::milliseconds>(stopSequential - startSequential);
    std::cout << "Sequantial taken time: " << durationSequential.count() << " mcs" << std::endl;

    return 0;
}