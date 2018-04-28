#include "timsort.h"
#include <omp.h>
#include <random>
#include <ctime>

int main() {

  std::srand(time(NULL));

  int inputArrSize = 0;
  std::cout << "Set array size: ";
  std::cin >> inputArrSize;
  std::vector<int> inputArray;

  int partSize = 0;
  std::cout << "Set part size: ";
  std::cin >> partSize;
  std::cout << "\n";

  generateRandomVector(inputArray, inputArrSize);

  if (inputArray.size() <= 500) {
    //std::cout << "Input array: \n";
    //printVector(inputArray.begin(), inputArray.end());
  }

  std::vector<Part> parts;
  std::vector<int> tmp(inputArrSize);

  double start = omp_get_wtime();
  timsort(inputArray, parts, tmp, partSize);
  std::cout << "\nSort time: " << omp_get_wtime() - start << "\n\n";

  //if (inputArray.size() <= 500) {
    //std::cout << "Sort array: \n";
    //printVector(inputArray.begin(), inputArray.end());
  //}

  return 0;
}
