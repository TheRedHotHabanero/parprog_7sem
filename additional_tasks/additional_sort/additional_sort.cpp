#include <omp.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>
#include <algorithm>

void fill_array(std::vector<int>& array, const int &N) {

    const int min_value = 1;
    const int max_value = 500;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min_value, max_value);

    for (int i = 0; i < N; i++) {
        array[i] = distribution(gen);
    }
}

// Merging two sorted arrays into one
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// PArallel sort using merge sort with OMP
void slow_parallelMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
    if (left < right) {
        if (right - left < threshold) {
        if (right - left < threshold) {
            // Используем сортировку слиянием
            int mid = left + (right - left) / 2;
            slow_parallelMergeSort(arr, left, mid, threshold);
            slow_parallelMergeSort(arr, mid + 1, right, threshold);
            merge(arr, left, mid, right);
        }
        }
        else {
            int mid = left + (right - left) / 2;

            #pragma omp parallel
            #pragma omp single nowait
            {
                #pragma omp task
                slow_parallelMergeSort(arr, left, mid, threshold);

                #pragma omp task
                slow_parallelMergeSort(arr, mid + 1, right, threshold);
            }
            #pragma omp taskwait

            merge(arr, left, mid, right);
        }
    }
}


// PArallel sort using merge sort with OMP
void parallelMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
    if (left < right) {
        if (right - left < threshold) {
            std::sort(arr.begin() + left, arr.begin() + right + 1);
        }
        else {
            int mid = left + (right - left) / 2;

            #pragma omp parallel
            #pragma omp single nowait
            {
                #pragma omp task
                parallelMergeSort(arr, left, mid, threshold);

                #pragma omp task
                parallelMergeSort(arr, mid + 1, right, threshold);
            }
            #pragma omp taskwait

            merge(arr, left, mid, right);
        }
    }
}

int check_sort(const std::vector<int> &array, const int& array_size, const int &threshold) {
    std::vector<int> tmp1 = array;
    parallelMergeSort(tmp1, 0, array_size - 1, threshold);
    std::vector<int> tmp2 = tmp1;
    parallelMergeSort(tmp1, 0, array_size - 1, threshold);
    for (int i = 0; i < array_size; i++) {
        if (tmp1[i] != tmp2[i]) {
            std::cout << "Error. Results are invald." << std::endl;
            return 1;
        }
    }

    return 0;
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "There are not enough arguments. Enter size of array." << std::endl;
        return 1;
    }

    int array_size = std::atoi(argv[1]);

    std::vector<int> array(array_size);
    fill_array(array, array_size);

    int threshold = 300; // Min for starting sequential part

    std::vector<int> copy = array;

    double slow_start_time = omp_get_wtime();
    slow_parallelMergeSort(array, 0, array_size - 1, threshold);
    double slow_end_time = omp_get_wtime();
    double slow_time = (slow_end_time - slow_start_time) * 1000;

    double start_time = omp_get_wtime();
    parallelMergeSort(copy, 0, array_size - 1, threshold);
    double end_time = omp_get_wtime();
    double time = (end_time - start_time) * 1000;

    // check_sort(array, array_size, threshold);    

    // std::cout << "Taken time: " << (end_time - start_time) * 1000 << " ms" << std::endl;
    std::cout << array_size << "," << slow_time << "," << time << std::endl;

    return 0;
}