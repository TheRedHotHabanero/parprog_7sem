#include "common.hpp"

void run()
{
    auto A_1 = initA_1();
    auto A = initA();
    auto Y = initY();
    double mer = 10.0;
    int curIter = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while (mer > 0.005)
    {
        auto F = Par::calcF(Y);
        auto dif = Par::Minus(F, Par::Mult(A, Y));
        Y = Par::Plus(Y, Par::Div(Par::Mult(A_1, dif), 10));
        mer = Par::dumpMer(dif);
        ++curIter;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Parallel time : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Used " << curIter << " iterations\n";
    Par::dumpToFile(Y, "solution_par.txt");
}

int main(int argc, char **argv)
{
    run();
    return 0;
}