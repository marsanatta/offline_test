#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>

int partition(int *arr, const int &l, const int &r, const int &pivot);
void printArray(const int *arr, const int &n);
void printMedian(int *arr, const int &n);
int findMedian(int *arr, const int &n);
int findKthSmallest(int *arr, const int &l, const int &r, const int &k);

int main(int argc, const char *argv[])
{
    int arr1[] = {6,38,49,55,11,44,33};
    int arr2[] = {11,41,42,43,31,91,81,71,61};

    printMedian(arr1, sizeof(arr1) / sizeof(arr1[0]));
    printMedian(arr2, sizeof(arr2) / sizeof(arr2[0]));

    return 0;
}

// find median in array arr; n is the length of the array
void printMedian(int *arr, const int &n) {

    if (n < 1) // if array is empty, just return
        return;

    // print array
    std::cout << "Array: ";
    printArray(arr, n);

    // find median and print it
    double median;
    if ((n & 0x01) == 1) { // array length is odd
        median = findKthSmallest(arr, 0, n - 1, n / 2 + 1);
    }
    else { // array length is even
        median = static_cast<double>(findKthSmallest(arr, 0, n - 1, n / 2) + 
                                     findKthSmallest(arr, 0, n - 1, n / 2 + 1)) / 2.0;
    }
    std::cout << "Median: " << median << std::endl;
}

// print the array arr; n is the length of the array
void printArray(const int *arr, const int &n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// partition the sub-array[l..r] around pivot
// return the position of pivot after partition
int partition(int *arr, const int &l, const int &r, const int &pivot)
{
    // search for pivot in arr[l..r] and swap it with last element
    int i;
    for (i = l; i < r; ++i)
        if (arr[i] == pivot)
           break;
    std::swap(arr[i], arr[r]);

    // do partition
    i = l;
    for (int j = l; j <= r - 1; ++j)
    {
        if (arr[j] <= pivot)
        {
            std::swap(arr[i], arr[j]); // ensure that i's left elements are less than the pivot
            i++;
        }
    }
    std::swap(arr[i], arr[r]); // swap back the pivot; finish partition
    return i;                  // return the position of the pivot
}

// sort the array of size n and return its median
// the time complexity will be O(1) since the GROUP_SIZE is a constant
int findMedian(int *arr, const int &n)
{
    if (n <= 1)
        return *arr;
    std::sort(arr, arr + n);  // Sort the array
    // we don't need to consider odd and even array length cases,
    // since this median is used for partition
    return arr[n / 2];
}

const int GROUP_NUM = 5; // number of elements in a group (used in Median of Medians algorithm)
// find kth smallest number in the sub-array[l..r]
int findKthSmallest(int *arr, const int &l, const int &r, const int &k)
{
    int n = r - l + 1; // length of the sub array

    // if k is out of range, return INT_MAX
    if (k <= 0 || k > n)
        return INT_MAX;

    // divide sub-arrary[l..r] in groups of size GROUP_NUM (the last group length can be less than GROUP_NUM)
    // calculate median of each groups and store them in median array
    int median[static_cast<int>(ceil(n / GROUP_NUM))];
    int median_i;
    for (median_i = 0; median_i < n / GROUP_NUM; ++median_i)
        median[median_i] = findMedian(arr + l + median_i * GROUP_NUM, GROUP_NUM);
    if (median_i * GROUP_NUM < n) { // last group with elements less than GROUP_NUM
        median[median_i] = findMedian(arr + l + median_i * GROUP_NUM, n % GROUP_NUM); 
        median_i++;
    }    

    int const medianNum = median_i; // the length of median array

    // Find median of all medians recursively
    int medOfMedians;
    if (medianNum == 1) // first median is the median of medians since there's only one median
        medOfMedians = median[0];
    else {
        // we don't need to consider odd and even array length cases,
        // since this median is used for partition
        medOfMedians = findKthSmallest(median, 0, medianNum - 1, medianNum / 2);
    }

    // partition the array by the median of medians
    int pos = partition(arr, l, r, medOfMedians);

    // if the pos is the kth number, return it
    if (pos - l == k - 1)
        return arr[pos];
    if (pos - l > k - 1)  // If position is more than kth, find kth within left sub-array
        return findKthSmallest(arr, l, pos - 1, k);
    else                  // If position is less kth, find kth within right sub-array 
        return findKthSmallest(arr, pos + 1, r, k - pos + l - 1);  
}
