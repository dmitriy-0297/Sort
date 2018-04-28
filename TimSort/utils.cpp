#include "utils.h"
#include <algorithm>
#include <iostream>

int getMax(std::vector<int>::iterator beg, std::vector<int>::iterator end) {
    int mx = *beg;
    for (std::vector<int>::iterator it = beg + 1; it != end; ++it) {
        if (*it > mx) {
            mx = *it;
        }
    }
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(std::vector<int>::iterator beg, std::vector<int>::iterator end, int exp)
{
    std::vector<int> output;
    #pragma omp parallel for
    for (int i = 0; i < end-beg; ++i) {
        output.push_back(0);
    }
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    #pragma omp parallel for
    for (i = 0; i < end - beg; ++i) {
        count[(*(beg + i) / exp) % 10]++;
    }

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    #pragma omp parallel for
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    #pragma omp parallel for
    for (i = end - beg - 1; i >= 0; i--)
    {
        //std::cout << output[count[(*(beg + i) / exp) % 10] - 1] << "\n";
        output[count[(*(beg + i) / exp) % 10] - 1] = *(beg + i);
        count[(*(beg + i) / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    std::vector<int>::iterator it2 = output.begin();
    for (std::vector<int>::iterator it = beg; it != end; ++it,++it2) {
        *it = *it2;
    }
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(std::vector<int>::iterator beg, std::vector<int>::iterator end)
{
    // Find the maximum number to know number of digits
    int m = getMax(beg, end);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(beg, end, exp);
    }
}

// ответ должен быть в диапазоне (64,128]
inline int getMinSize(int n) {
  int r = 0;
  while (n >= 128) {
    n >>= 1;
    r |= n & 1;
  }
  return n + r;
}

void selection_sort(std::vector<int> &inputArray, int beg, int last) {
  for (int i = beg; i<last; ++i) {
    int min_pos = i;
    for (int j = i + 1; j<last; ++j) {
      if (inputArray[j] < inputArray[min_pos])
        min_pos = j;
    }
    std::swap(inputArray[i], inputArray[min_pos]);
  }
}

void generateRandomVector(std::vector<int>& inputArray, int arraySize) {
  for (int i = 0; i < arraySize; ++i) {
    inputArray.push_back(rand() % 10000);
  }
}

void printVector(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}
