#ifndef UTILS_H
#define UTILS_H

#include <iterator>
#include <vector>

int getMax(std::vector<int>::iterator beg, std::vector<int>::iterator end);
void countSort(std::vector<int>::iterator beg, std::vector<int>::iterator end, int exp);
void radixsort(std::vector<int>::iterator beg, std::vector<int>::iterator end);

inline int getMinSize(int n);

void selection_sort(std::vector<int> &inputArray, int beg, int last);

void generateRandomVector(std::vector<int>& inputArray, int arraySize);
void printVector(std::vector<int>::iterator start, std::vector<int>::iterator end);

#endif // UTILS_H
