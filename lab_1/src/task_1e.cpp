#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <mpi.h>

const int ISIZE = 5000;
const int JSIZE = 5000;

std::chrono::milliseconds task_1_sequential()
{
    int i, j;

    double **a = new double *[ISIZE];
    for (int i = 0; i < ISIZE; ++i)
    {
        a[i] = new double[JSIZE];
    }

    std::ofstream ff("result_task_1_sequential.txt");

    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            a[i][j] = 10 * i + j;
        }
    }
    auto start_time = std::chrono::high_resolution_clock::now();

    // Начало измерения времени
    for (i = 1; i < ISIZE; i++)
    {
        for (j = 8; j < JSIZE; j++)
        {
            a[i][j] = std::sin(5 * a[i - 1][j - 8]);
        }
    }
    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            ff << a[i][j] << ' ';
        }
        ff << '\n';
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < ISIZE; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
    return duration;
}

void task_1_parallel(int argc, char **argv)
{
    int i, j;

    int commsize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double* a = new double[ISIZE * JSIZE];

    std::ofstream ff("result_task_1_sequential.txt");
    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            a[i * JSIZE + j] = 10 * i + j;
        }
    }

    int jsize_per_thread = (JSIZE - 8) / commsize;
    int line_start = jsize_per_thread * rank;
    int line_end = jsize_per_thread * (rank + 1);
    if (rank == commsize - 1)
        line_end = (JSIZE - 8);

    int per_thread_size = line_end - line_start;
    double per_thread_array[JSIZE];

    int* recvcnts = new int[commsize];
    int* displs = new int[commsize];

    MPI_Barrier(MPI_COMM_WORLD);
    for (int k = 0; k < commsize - 1; k++)
    {
        recvcnts[k] = per_thread_size;
    }
    recvcnts[commsize - 1] = per_thread_size + (JSIZE - 8) % commsize;

    for (int k = 0; k < commsize; k++)
    {
        displs[k] = 8 + k * per_thread_size;
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    // Начало измерения времени
    for (i = 0; i < ISIZE - 1; i++)
    {
        for (j = line_start; j < line_end; j++)
        {
            per_thread_array[j + 8] = std::sin(5 * a[i * JSIZE + j]);
        }

        MPI_Allgatherv(&per_thread_array[line_start + 8], per_thread_size, MPI_DOUBLE,
                       &a[(i + 1) * JSIZE], recvcnts, displs, MPI_DOUBLE, MPI_COMM_WORLD);
    }

    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < 500; ++i)
        {
            for (int j = 0; j < 500; ++j)
            {
                ff << a[i * JSIZE + j] << ' ';
            }
            ff << '\n';
        }
        delete[] a;
        delete[] recvcnts;
        delete[] displs;
        std::cout << "Parallel: " << duration.count() << " mls" << std::endl;
    }
}

int main(int argc, char **argv)
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        std::cout << "Sequential: " << task_1_sequential().count() << " mls" << std::endl;
    }
    task_1_parallel(argc, argv);

    MPI_Finalize();

    return 0;
}
