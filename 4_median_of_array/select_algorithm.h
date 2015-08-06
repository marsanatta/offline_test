#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

int partition(int *arr, const int &l, const int &r, const int &pivot_i);
int findMedian(int *arr, const int &n);
int medianOfMedians(int *arr, const int &l, const int &r, const int &k);
int quickSelect(int *arr, const int &l, const int &r, const int &k);
