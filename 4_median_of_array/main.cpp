#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "select_algorithm.h"

void printArray(const int *arr, const int &n);
void printMedian(int *arr, const int &n, int (*findKthSmallest)(int *arr, const int &l, const int &r, const int &k));

int main(int argc, const char *argv[])
{
    int arr1[] = {6,38,49,55,11,44,33};
    int arr2[] = {11,41,42,43,31,91,81,71,61};

    std::cout << "Way1: Median of Medians"  << std::endl;
    printMedian(arr1, sizeof(arr1) / sizeof(arr1[0]), medianOfMedians);
    printMedian(arr2, sizeof(arr2) / sizeof(arr2[0]), medianOfMedians);
    std::cout << std::endl;

    std::cout << "Way2: Quick Select" << std::endl;
    srand(time(NULL));
    printMedian(arr1, sizeof(arr1) / sizeof(arr1[0]), quickSelect);
    printMedian(arr2, sizeof(arr2) / sizeof(arr2[0]), quickSelect);

    return 0;
}

// print median in array arr of size n
// findKthSmallest is the function pointer to the function which finds kth smallest element in an array
void printMedian(int *arr, const int &n, int (*findKthSmallest)(int *arr, const int &l, const int &r, const int &k)) {

    if (n < 1) // if array is empty, just return
        return;
    
    int *arr_cpy = new int[n];
    memcpy(arr_cpy, arr, sizeof(int) * n);

    // print array
    std::cout << "Array: ";
    printArray(arr_cpy, n);

    auto begin = std::chrono::high_resolution_clock::now();  
    // find median and print it
    double median;
    if ((n & 0x01) == 1) { // array length is odd
        median = findKthSmallest(arr_cpy, 0, n - 1, n / 2 + 1);
    }
    else { // array length is even
        median = static_cast<double>(findKthSmallest(arr_cpy, 0, n - 1, n / 2) + 
                findKthSmallest(arr_cpy, 0, n - 1, n / 2 + 1)) / 2.0;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << "Find Median: " << median << " in " << ns << " ns" << std::endl;

    delete[] arr_cpy;
}

// print the array arr; n is the length of the array
void printArray(const int *arr, const int &n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

