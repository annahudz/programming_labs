#ifndef LEXLESS_H
#define LEXLESS_H
#include <iostream>
#include <vector>
bool lexLess(const std::vector<int>& a, const std::vector<int>& b) {
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}
#endif