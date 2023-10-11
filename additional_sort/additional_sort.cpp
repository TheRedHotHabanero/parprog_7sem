#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter number of threads." << std::endl;
        return 1;
    }

    int threads_from_user = std::atoi(argv[1]);

    return 0;
}
