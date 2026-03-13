#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include "LexLess.h"
#include <algorithm>

// Lomuto partition
 int partitionLomuto(std::vector<std::vector<int>>& arr, int low, int high) {
    std::vector<int> pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (lexLess(arr[j], pivot) || arr[j] == pivot) { 
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(std::vector<std::vector<int>>& arr, int low, int high) {
    if (low < high) {
        int p = partitionLomuto(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

#endif
