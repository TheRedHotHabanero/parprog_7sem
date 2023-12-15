#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

const double tol = 1e-6;
const double sqrt_a = sqrt(2.0);
const double x_start = -10.0;
const double x_end = 10.0;

double f(double x, double y, double a) {
    return a * (pow(y, 3) - y);
}

double newton(double ym1, double y, double yp1, double h, double a) {
    double f_m1 = f(0, ym1, a);
    double f_m = f(0, y, a);
    double f_p1 = f(0, yp1, a);
    double delta = 0.0;

    do {
        double y_prime = y + delta;
        double f_prime = f(0, y_prime, a);

        if (std::abs(f_m - f_prime) < tol) {
            delta = std::numeric_limits<double>::max();
            break;
        }

        delta -= (h * h) * (f_prime - (2.0 * f_m - f_m1) / 12.0) /
                 (2.0 * (f_m - f_prime));
    } while (std::abs(delta) > tol);

    return y + delta;
}

void solve_bvp(double a, int num_points, const std::string& filename) {
    double h = (x_end - x_start) / static_cast<double>(num_points);
    double *y = new double[num_points + 1];

    y[0] = sqrt_a;
    y[num_points] = sqrt_a;

    #pragma omp parallel for
    for (int i = 1; i < num_points; ++i) {
        double x = x_start + i * h;
        y[i] = newton(y[i - 1], y[i], y[i + 1], h, a);
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i <= num_points; ++i) {
        // Проверка на NaN перед записью в файл
        if (!std::isnan(y[i])) {
            double x = x_start + i * h;
            outFile << x << "\t" << y[i] << std::endl;
        }
    }

    outFile.close();
    delete[] y;
}

int main() {
    double a_min = 100.0;
    double a_max = 1000000.0;
    int num_points = 400;

    for (double a = a_min; a <= a_max; a *= 10) {
        std::string filename = "solution_a_" + std::to_string(a) + ".txt";
        solve_bvp(a, num_points, filename);
    }

    return 0;
}
