#ifndef TIMSORT_H
#define TIMSORT_H

#include "part.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

const int dx = 1;
const int dy = 2;
const int dz = 3;

void merge(std::vector<int> &inputArray, std::vector<Part> &parts, bool isXY, std::vector<int> &tmp);

void tryMerge(std::vector<int> &inputArray, std::vector<Part> &parts, std::vector<int> &tmp, bool isMerge = false);

void timsort(std::vector<int> &inputArray, std::vector<Part>& parts, std::vector<int>& tmp, int partSize);

#endif
