#include <iostream>
#include <cmath>
#include <fstream>
#include <chrono>
#include <mpi.h>

const int YSIZE = 5000;
const int XSIZE = 5000;

static inline double initial_value(int y, int x)
{
    return 10 * y + x;
}

double **empty_matrix(int len_y, int len_x)
{
    double **res = (double **)calloc(len_y, sizeof(double *));
    for (int i = 0; i < len_y; ++i)
    {
        res[i] = (double *)calloc(len_x, sizeof(double));
    }
    return res;
}

void free_matrix(double **matrix, int len_y)
{
    for (int t = 0; t < len_y; ++t)
    {
        free(matrix[t]);
    }
    free(matrix);
}

void task_1_sequential()
{
    std::ofstream ff("result_task_1_sequential.txt");
    double **a = empty_matrix(YSIZE, XSIZE);
    int y, x;
    for (y = 0; y < YSIZE; y++)
    {
        for (x = 0; x < XSIZE; x++)
        {
            a[y][x] = 10 * y + x;
        }
    }

    // начало измерения времени
    double time_1 = MPI_Wtime();
    for (y = 1; y < YSIZE; y++)
    {
        for (x = 8; x < XSIZE; x++)
        {
            a[y][x] = sin(5 * a[y - 1][x - 8]);
        }
    }
    double time_2 = MPI_Wtime();
    printf("%lf", time_2 - time_1);
    // окончание измерения времени
    // Запись результатов в файл
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            ff << a[i][j] << ' ';
        }
        ff << '\n';
    }
    free_matrix(a, YSIZE);
}

void task_1_parallel(int argc, char *argv[])
{
    std::ofstream ff("result_task_1_sequential.txt");
    if (argc != 1 && argc != 2)
    {
        printf("Wrong number of args! Please provide 2 arguments\n");
        exit(-1);
    }

    MPI_Init(&argc, &argv);
    int my_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size == 1)
    {
        printf("world_size == 1");
        abort();
    }

    if (my_rank == 0)
    {
        task_1_sequential(); // Call the sequential part in rank 0
    }
    else
    {
        // Not null rank
        int s = world_size - 1; // executing processes
        // Computing row roots
        double message[XSIZE / 8 + 10];
        for (int curr_y0 = my_rank - 1; curr_y0 < YSIZE; curr_y0 += s)
        {
            for (int curr_x0 = 0; curr_x0 < 8; ++curr_x0)
            {
                message[0] = (double)curr_y0;
                message[1] = (double)curr_x0;
                double *arr = message + 2;
                int y = curr_y0;
                int x = curr_x0;
                arr[0] = initial_value(curr_y0, curr_x0);
                int i = 1;
                y += 1;
                x += 8;
                while (y < YSIZE && x < XSIZE)
                {
                    arr[i] = sin(5 * arr[i - 1]);
                    i++;
                    y += 1;
                    x += 8;
                }
                MPI_Send(
                    message,
                    i + 2,
                    MPI_DOUBLE,
                    0, // the zero rank.
                    0,
                    MPI_COMM_WORLD);
            }
        }

        for (int curr_x0 = (my_rank - 1) % 8 + 8; curr_x0 < XSIZE; curr_x0 += s)
        {
            if ((my_rank - 1) % 8 != curr_x0)
            {
            }
            message[0] = 0.0;
            message[1] = (double)curr_x0;
            int curr_y0 = 0;
            int x = curr_x0;
            int y = curr_y0;
            double *arr = message + 2;
            arr[0] = initial_value(curr_y0, x);
            y += 1;
            x += 8;
            int i = 1;
            while (y < YSIZE && x < XSIZE)
            {
                arr[i] = sin(5 * arr[i - 1]);
                i++;
                y += 1;
                x += 8;
            }
            MPI_Send(
                message,
                i + 2,
                MPI_DOUBLE,
                0, // the zero rank.
                0,
                MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    // Запись результатов в файл
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 500; ++j)
        {
            ff << arr[i][j] << ' ';
        }
        ff << '\n';
    }
}

int main(int argc, char *argv[])
{
    task_1_sequential();
    task_1_parallel(argc, argv);
    return 0;
}
