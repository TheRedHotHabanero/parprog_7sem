#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <mpi.h>

const int ISIZE = 5000;
const int JSIZE = 5000;

void task_1_sequential()
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

    std::cout << "Sequential: " << duration.count() << " mls" << std::endl;

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
}

void task_1_parallel(int argc, char **argv)
{
    int i, j;

    MPI_Init(&argc, &argv);

    int commsize, this_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_rank);

    double* a = (double*) calloc(ISIZE * JSIZE, sizeof(double));

    std::ofstream ff("result_task_1_parallel.txt");
    for (i = 0; i < ISIZE; i++)
    {
        for (j = 0; j < JSIZE; j++)
        {
            a[i * JSIZE + j] = 10 * i + j;
        }
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    j = this_rank;
    for (i = 0; i < ISIZE - 1; i++)
    {
        for (; j < JSIZE - 8;)
        {
            auto &tmp = a[i * JSIZE + j];
            a[(1 + i) * JSIZE + (8 + j)] = std::sin(5 * tmp);
            j += commsize;
        }
        j %= (JSIZE - 8);
    }
    // Окончание измерения времени
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Parallel: " << duration.count() << " mls" << std::endl;
    // окончание измерения времени

    if (this_rank != 0)
    {
        j = this_rank;
        for (i = 0; i < ISIZE - 1; i++)
        {
            for (; j < JSIZE - 8;)
            {
                int index = (1 + i) * JSIZE + (j + 8);
                MPI_Send(&a[index], 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
                j += commsize;
                MPI_Barrier(MPI_COMM_WORLD);
            }
            j %= (JSIZE - 8);
        }
    }
    else
    {
        j = 0;
        for (i = 0; i < ISIZE - 1; i++)
        {
            for (; j < JSIZE - 8;)
            {
                for (int rank = 0 + 1; rank < commsize; rank++)
                {
                    int index = (1 + i + (j + 8 + rank) / JSIZE) * JSIZE + (j + 8 + rank) % JSIZE;
                    MPI_Recv(&a[index], 1, MPI_DOUBLE, rank, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
                }
                j += commsize;
                MPI_Barrier(MPI_COMM_WORLD);
            }
            j %= (JSIZE - 8);
        }
    }

    if (this_rank == 0)
    {
        for (int i = 0; i < 500; ++i)
        {
            for (int j = 0; j < 500; ++j)
            {
                ff << a[i * JSIZE + j] << ' ';
            }
            ff << '\n';
        }
    }
    // Освобождение выделенной памяти
    free(a);

    MPI_Finalize();
}

int main(int argc, char **argv)
{
    task_1_sequential();
    task_1_parallel(argc, argv);

    return 0;
}