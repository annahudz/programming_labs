#ifndef HYBRIDSORT_H
#define HYBRIDSORT_H

#include <vector>
#include "LexLess.h"
#include <algorithm>

const int THRESHOLD = 10;

 void insertionSort(std::vector<std::vector<int>>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        std::vector<int> key = arr[i];
        int j = i - 1;
        while (j >= low && lexLess(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Lomuto partition 
 int partitionHybrid(std::vector<std::vector<int>>& arr, int low, int high) {
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

// HybridSort: QuickSort + InsertionSort
 void hybridSort(std::vector<std::vector<int>>& arr, int low, int high) {
    if (high - low + 1 <= THRESHOLD) {
        insertionSort(arr, low, high);
        return;
    }
    if (low < high) {
        int p = partitionHybrid(arr, low, high);
        hybridSort(arr, low, p - 1);
        hybridSort(arr, p + 1, high);
    }
}

#endif