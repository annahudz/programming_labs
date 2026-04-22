#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include "LexLess.h"
#include <vector>
using namespace std;

void bubbleSort(vector<vector<int>>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (!lexLess(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

#endif