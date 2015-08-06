#include "select_algorithm.h"

// partition the sub-array arr[l..r] around pivot
// pivot_i: the index of pivot
// return the position of the pivot after partition
int partition(int *arr, const int &l, const int &r, const int &pivot_i)
{
    // swap pivot with the last element
    const int pivot = arr[pivot_i];
    if (pivot_i != r) 
        std::swap(arr[pivot_i], arr[r]);
    //const int pivot = arr[pivot_i];

    // do partition
    int chg = l;
    for (int i = l; i <= r - 1; ++i)
    {
        if (arr[i] <= pivot)
        {
            std::swap(arr[chg], arr[i]); // ensure that i's left elements are less than the pivot
            chg++;
        }
    }
    std::swap(arr[chg], arr[r]); // swap back the pivot; finish partition
    return chg;                  // return the position of the pivot
}

// sort the array arr of size n and return its median
int findMedian(int *arr, const int &n)
{
    if (n < 1)
        throw std::invalid_argument("Empty array");
    if (n == 1) 
        return *arr;
    std::sort(arr, arr + n);  // Sort the array
    // we don't need to consider odd and even array length cases,
    // since this median is used for partition
    return arr[n / 2];
}

const int GROUP_NUM = 5; // number of elements in a group (used in Median of Medians algorithm)
// Median of medians algorithm: find k th smallest number in the sub-array[l..r]
int medianOfMedians(int *arr, const int &l, const int &r, const int &k)
{
    int n = r - l + 1; // length of the sub array

    // if k is out of range, throw exception
    if (k <= 0 || k > n)
        throw std::invalid_argument("invalid k-th");

    // divide sub-arrary[l..r] in groups of size GROUP_NUM (the last group length can be less than GROUP_NUM)
    // calculate median of each groups and store them in median array
    int const medianNum = static_cast<int>(ceil(static_cast<double>(n) / static_cast<double>(GROUP_NUM)));
    //int const medianNum = (n + 4) / GROUP_NUM;
    int median[medianNum];
    int median_i;
    for (median_i = 0; median_i < n / GROUP_NUM; ++median_i)
        median[median_i] = findMedian(arr + l + median_i * GROUP_NUM, GROUP_NUM);
    if (median_i * GROUP_NUM < n) { // last group with elements less than GROUP_NUM
        median[median_i] = findMedian(arr + l + median_i * GROUP_NUM, n % GROUP_NUM); 
    }    

    // Find median of all medians recursively
    int medOfMedians;
    if (medianNum == 1) // first median is the median of medians since there's only one median
        medOfMedians = median[0];
    else {
        // we don't need to consider odd and even array length cases,
        // since this median is used for partition
        medOfMedians = medianOfMedians(median, 0, medianNum - 1, medianNum / 2);
    }

    // get the medOfMedians's index
    int pivot_i;
    for (pivot_i = l; pivot_i < r; ++pivot_i) {
        if (arr[pivot_i] == medOfMedians)
            break;
    }
    // partition the array around median of medians
    int pos = partition(arr, l, r, pivot_i);

    if (pos - l + 1 == k) // if the pos is the kth number, return it   
        return arr[pos];
    if (pos - l + 1 > k)  // if position is more than kth, find kth within left sub-array
        return medianOfMedians(arr, l, pos - 1, k);
    else                  // if position is less than kth, find kth within right sub-array 
        return medianOfMedians(arr, pos + 1, r, k - pos + l - 1);  
}

// Quick select algorithm: find k th smallest number in the sub-array[l..r]
int quickSelect(int *arr, const int &l, const int &r, const int &k) {

    const int n = r - l + 1;
    // if k is out of range, throw exception
    if (k <= 0 || n < k)
        throw std::invalid_argument("invalid k-th");

    int pivot_i = l + rand() % n; // random pick up a pivot

    // partition arr[l..r] around pivot
    int pos = partition(arr, l, r, pivot_i);

    if (pos - l + 1 == k)     // if the pos is the kth number, return it   
        return arr[pos];
    else if (pos - l + 1 > k) // if position is more than kth, find kth within left sub-array 
        return quickSelect(arr, l, pos - 1, k);
    else                      // if position is less than kth, find kth within right sub-array  
        return quickSelect(arr, pos + 1, r, k - pos + l - 1);
}



