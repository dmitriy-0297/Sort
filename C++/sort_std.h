#ifndef SORT_STL_H
#define SORT_STL_H

#include <iostream>
#include <vector>
#include <algorithm>

void sortArray (std::vector<int>& v) {
    std::sort(v.begin(), v.end());
}

#endif // SORT_STL_H
