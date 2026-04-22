#ifndef MERGESORT_H
#define MERGESORT_H
#include "LexLess.h"
#include <vector>
using namespace std;


void merge(vector<vector<int>>& arr, int left, int mid, int right) {
    vector<vector<int>> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (lexLess(arr[i], arr[j])) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++) arr[left + k] = temp[k];
}

void mergeSortBottomUp(vector<vector<int>>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size*= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            merge(arr, left, mid, right);
        }
    }
}

#endif