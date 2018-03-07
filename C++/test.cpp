#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include <time.h>
#include "sort_plpl.h"

std::vector<std::vector<int> > sortVec(std::vector<std::vector<int> > vec, int n, int div_vec){
  std::vector<std::vector<int> > v; //создаю вектор векторов отсортированный
  for (int i = 0; i < div_vec; ++i){
    v.push_back(sortArray(vec.at(i), (n / div_vec)));
  }
  return v;
}

std::vector<std::vector<int> > divVec(std::vector<int> arr, int n, int div_vec){ // создание v[vec]
  std::vector<std::vector<int> > v;
  for (int i = 0; i < div_vec; ++i){
    std::vector<int> vec;
    v.push_back(vec);
  }
  for(int k = 0; k < n; ++k){
    for(int i = 0; i < div_vec; ++i){
      for(int j = 0; j < (n / div_vec); ++j){
        v.at(i).push_back(arr[k]);
        ++k;
      }
    }
  }
  return v;
}

std::vector<std::vector<int> > checkVec(std::vector<std::vector<int> > vSort, std::vector<int> Array, int n, int div_vec){
  std::vector<std::vector <int> > vec;
  for (int i = 0; i < div_vec; ++i){
    std::vector<int> v;
    vec.push_back(v);
  }
  while(div_vec != 1){
    div_vec = div_vec / 2;
    vSort.clear();
    vSort = divVec(Array, n, div_vec);
    std::cout << '\n';std::cout << "Vector[vector]: " << std::endl;
      for (int i = 0; i < div_vec; ++i){
        for (int j = 0; j < (n / div_vec); ++j){
          std::cout << vSort.at(i).at(j) << " ";
        }
        std::cout << "\n";
      }
      vec.clear();
      for (int i = 0; i < div_vec; ++i){
        std::vector<int> v;
        vec.push_back(v);
      }
      for(int i = 0; i < div_vec; ++i){
        for(int j = 0; j < (n / div_vec); ++j){
          vec.at(i).push_back(sortVec(vSort, n, div_vec).at(i).at(j));
        }
      }
      std::cout << "Vec[vec] sort: ";
      std::cout << std::endl;
      for (int i = 0; i < div_vec; ++i){
        for (int j = 0; j < (n / div_vec); ++j){
          std::cout << vec.at(i).at(j) << " ";
        }
        std::cout << "\n";
      }
    }
  return vec;
}

int main(){
  float duration;
  clock_t start, finish;
  int n = 0; //размер основного массива
  int div_vec = 0; //на сколько делин исходный массив
  std::cout << "Enter count: ";
  std::cin >> n;
  std::cout << "Enter div array: ";
  std::cin >> div_vec;
  std::vector<int> Array;
  for (int i = 0; i < n; i++){ // формируем значения исходного массива
    Array.push_back(rand() % 100);
  }
  std::cout << "Array start: " << std::endl;
  for (int i = 0; i < n; i++){
    std::cout << Array.at(i) << " ";
  }
  std::cout << "\n";
  std::vector<std::vector <int> > v(divVec(Array, n, div_vec));
  std::cout << '\n';std::cout << "Vector[vector]: " << std::endl;
    for (int i = 0; i < div_vec; ++i){
      for (int j = 0; j < (n / div_vec); ++j){
        std::cout << v.at(i).at(j) << " ";
      }
      std::cout << "\n";
    }

  start = clock();

  std::vector<std::vector <int> > vSort(sortVec(v, n, div_vec));
  std::cout << "Vec[vec] sort: ";
  std::cout << std::endl;
  for (int i = 0; i < div_vec; ++i){
    for (int j = 0; j < (n / div_vec); ++j){
      std::cout << vSort.at(i).at(j) << " ";
    }
    std::cout << "\n";
  }

  std::vector<int> sortArray;
  std::vector<std::vector<int> > vecSort = checkVec(vSort, Array, n, div_vec);
  for (int i = 0; i < 1; ++i){
    for (int j = 0; j < 50; ++j){
        sortArray.push_back(vecSort.at(i).at(j));
    }
  }

  finish = clock();

  Array.clear();
  vecSort.clear();
  std::cout << "\n";
  std::cout << "Array sort: ";
  std::cout << std::endl;
  for (int i = 0; i < n; ++i){
      std::cout << sortArray.at(i) << " ";
    }
    std::cout << "\n";
    duration = (float)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "Time: " << "\n";
    std::cout << duration << "\n";
  return 0;
}
