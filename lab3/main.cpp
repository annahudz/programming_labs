#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "BubbleSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HybridSort.h"
#include "LexLess.h"

using namespace std;

vector<vector<int>> random_lists(int n, int m) {
    vector<vector<int>> arr(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i][j] = rand() % 50;
    return arr;
}

void show_lists(vector<vector<int>>& arr) {
    for (auto& v : arr) {
        cout << "{ ";
        for (int x : v) cout << x << " ";
        cout << "} ";
    }
    cout << endl;
}

void demonstration_mode() {
    cout << "DEMONSTRATION MODE\n";

    int n = 5;
    vector<vector<int>> base = random_lists(n, 5);

    cout << "Initial lists:\n";
    show_lists(base);

    vector<vector<int>> a1 = base;
    cout << "Bubble sort:\n";
    bubbleSort(a1);
    show_lists(a1);

    vector<vector<int>> a2 = base;
    cout << "Merge sort:\n";
    mergeSortBottomUp(a2);
    show_lists(a2);

    vector<vector<int>> a3 = base;
    cout << "Quick sort:\n";
    quickSort(a3, 0, a3.size() - 1);
    show_lists(a3);

    vector<vector<int>> a4 = base;
    cout << "Hybrid sort:\n";
    hybridSort(a4, 0, a4.size() - 1);
    show_lists(a4);

    vector<vector<int>> a5 = base;
    cout << "Library sort:\n";
    sort(a5.begin(), a5.end(), lexLess);
    show_lists(a5);

    cout << endl;
}

void benchmark(vector<vector<int>> data) {
    vector<vector<int>> arr;
    clock_t start, end;

    arr = data;
    start = clock();
    bubbleSort(arr);
    end = clock();
    cout << "Bubble sort: " << double(end - start) / CLOCKS_PER_SEC << " sec\n";

    arr = data;
    start = clock();
    quickSort(arr, 0, arr.size() - 1);
    end = clock();
    cout << "Quick sort: " << double(end - start) / CLOCKS_PER_SEC << " sec\n";

    arr = data;
    start = clock();
    mergeSortBottomUp(arr);
    end = clock();
    cout << "Merge sort: " << double(end - start) / CLOCKS_PER_SEC << " sec\n";

    arr = data;
    start = clock();
    hybridSort(arr, 0, arr.size() - 1);
    end = clock();
    cout << "Hybrid sort: " << double(end - start) / CLOCKS_PER_SEC << " sec\n";

    arr = data;
    start = clock();
    sort(arr.begin(), arr.end(), lexLess);
    end = clock();
    cout << "Library sort: " << double(end - start) / CLOCKS_PER_SEC << " sec\n";

    cout << endl;
}

void benchmark_mode() {
    cout << "BENCHMARK MODE\n";

    cout << "Random lists:\n";
    vector<vector<int>> random_arr = random_lists(20, 5);
    benchmark(random_arr);

    cout << "Almost sorted lists:\n";
    vector<vector<int>> almost_sorted = {
        {1,2,3,4,5},{1,2,3,4,6},{1,2,3,4,7},{1,2,3,4,8},{1,2,3,4,9},
        {1,2,3,4,10},{1,2,3,4,11},{1,2,3,4,13},{1,2,3,4,12},{1,2,3,4,14}
    };
    benchmark(almost_sorted);

    cout << "Almost reverse lists:\n";
    vector<vector<int>> almost_reverse = {
        {9,9,9,9,9},{8,8,8,8,8},{7,7,7,7,7},{6,6,6,6,6},{5,5,5,5,5},
        {4,4,4,4,4},{3,3,3,3,3},{2,2,2,2,2},{0,0,0,0,0},{1,1,1,1,1}
    };
    benchmark(almost_reverse);
}

int main() {
    srand(time(0));
    demonstration_mode();
    benchmark_mode();
    return 0;
}