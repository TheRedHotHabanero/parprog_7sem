#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <cmath>

void sieveOfEratosthenes(long long int n) {
    std::vector<bool> isPrime(n + 1, true);

    for (long long int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            for (long long int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // Output prime numbers
    // std::cout << "Prime numbers for N = " << n << ":" << std::endl;
    // int prime_counter = 0;
    // for (long long int p = 2; p <= n; p++) {
    //     if (isPrime[p]) {
    //         std::cout << p << " ";
    //         prime_counter++;
    //     }
    // }
    // std::cout << std::endl;
    // std::cout << "Sequential: Quantity of prime numbers is " << prime_counter << "." << std::endl;
}

void parallelSieveOfEratosthenes(long long int n, int num_threads) {
    std::vector<bool> isPrime(n + 1, true);
    long long int square = std::sqrt(n);

    #pragma omp parallel num_threads(num_threads) default(none) shared(isPrime, n, square)
    {
        #pragma omp for schedule(dynamic)
        for (long long int p = 2; p < square + 1; p++) {
            if (isPrime[p]) {
                for (long long int i = p * p; i <= n; i += p) {
                    isPrime[i] = false;
                }
            }
        }
    }

    // Output prime numbers
    // std::cout << "Prime numbers for N = " << n << ":" << std::endl;
    // int prime_counter = 0;
    // #pragma omp parallel for schedule(dynamic) reduction(+:prime_counter)
    // for (long long int p = 2; p <= n; p++) {
    //     if (isPrime[p]) {
    //         std::cout << p << " ";
    //         prime_counter++;
    //     }
    // }
    // std::cout << std::endl;
    // std::cout << "Parallel: Quantity of prime numbers is " << prime_counter << "." << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <N> <num_threads>" << std::endl;
        return 1;
    }
    const long long int N = std::atoi(argv[1]);
    const int num_threads = std::atoi(argv[2]);

    // Measure the execution time for the sequential version
    std::cout << N << ",";
    auto startSequential = std::chrono::high_resolution_clock::now();
    sieveOfEratosthenes(N);
    auto stopSequential = std::chrono::high_resolution_clock::now();
    auto durationSequential = std::chrono::duration_cast<std::chrono::microseconds>(stopSequential - startSequential);
    std::cout << durationSequential.count();

    // Measure the execution time for the parallel version
    auto startParallel = std::chrono::high_resolution_clock::now();
    parallelSieveOfEratosthenes(N, num_threads);
    auto stopParallel = std::chrono::high_resolution_clock::now();
    auto durationParallel = std::chrono::duration_cast<std::chrono::microseconds>(stopParallel - startParallel);
    std::cout << "," << durationParallel.count() << std::endl;

    return 0;
}