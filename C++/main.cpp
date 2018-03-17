#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include "sort.h"

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
    std::cout << '\n';
    std::cout << "Vector[vector]: " << std::endl;
    for (int i = 0; i < div_vec; ++i){
        for (int j = 0; j < (n / div_vec); ++j){
            std::cout << v.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }
    return v;
}

void combAndSortVec(std::vector<int>& v_1, std::vector<int>& v_2){ //сортировка 2 массивов
    std::vector<int> v;
    int vecSize = v_1.size();
    int vSize = int(v_1.size()) + int(v_2.size());
    for(int i = 0; i < v_1.size(); i++){
        v.push_back(v_1[i]);
    }
    for(int i = 0; i < v_2.size(); i++){
        v.push_back(v_2[i]);
    }
    sortArray(v, int(v.size()));
    v_1.clear();
    v_2.clear();
    int j = 0;
    for (int i = 0; i < int(v.size()); ++i){
        if (i >= int(vecSize)){
            v_2.push_back(v.at(i));
        }else if(i < int(vecSize)){
            v_1.push_back(v.at(i));
        }
    }
}

void randArray(std::vector<int>& Array, int n){ //запоняем массив
    for (int i = 0; i < n; i++){ // формируем значения исходного массива
        Array.push_back(rand() % 100);
    }
    std::cout << "Array: " << std::endl; //вывод исходного массива
    for (int i = 0; i < n; i++){
        std::cout << Array.at(i) << " ";
    }
    std::cout << "\n";
}

void outTable(std::vector<std::vector<int> > v, int div_vec, int n){ //вывод таблицы
    std::cout << "\n";
    std::cout << "Table:" << "\n";
    for (int i = 0; i < int(v.size()); i++){
        std::cout << v.at(i).at(0) << " " << v.at(i).at(n/div_vec-1);
        std::cout << '\n';
    }
}

int main(){
    int countIter = 0;
    double start, end;
    int n = 0; //размер основного массива
    int div_vec = 0; //на сколько делин исходный массив
    std::cout << "Enter count: ";
    std::cin >> n;
    std::cout << "Enter div array: ";
    std::cin >> div_vec;
    std::vector<int> Array;
    randArray(Array, n); //заполнение исходного массива
    std::vector<std::vector <int> > v(divVec(Array, n, div_vec)); //разбиение исходного массива на части
    start = omp_get_wtime(); //начало сортировки
    for (int i = 0; i < div_vec; ++i){
        sortArray(v.at(i), int(n/div_vec));
    }
    std::cout << "\n";
    std::cout << "Array sort parts: " << std::endl; //вывод отсортированых частей вектора
    for (int k = 0; k < div_vec; ++k){
        for (int m = 0; m < (n / div_vec); ++m){
            std::cout << v.at(k).at(m) << " ";
        }
        std::cout << "\n";
    }
    outTable(v, div_vec, n);
    for(int i = 0; i < div_vec - 1; ++i){
        for(int j = i; j < div_vec; ++j){
            if(i == j){
                j++;
            }
            if ((v.at(i).at((n/div_vec - 1)) > v.at(j).at(0)) || (v.at(i).at(0) > v.at(j).at(0))
                    || (v.at(i).at(n/div_vec - 1) > v.at(j).at(n/div_vec - 1)) || (v.at(i).at(0) > v.at(j).at(n/div_vec - 1))){
                std::cout << "\n";
                std::cout << "two parts sort: " << "\n";
                std::cout << i + 1 << " whith " << j + 1 << "\n";
                combAndSortVec(v.at(i), v.at(j));
                countIter++;
                outTable(v, div_vec, n); //вывод таблицы
            }
        }
    }
    std::cout << "\n";
    std::cout << "Array sort: " << "\n"; //конечный отсортированный вектор
    end = omp_get_wtime();
    for (int k = 0; k < div_vec; ++k){
        for (int m = 0; m < (n / div_vec); ++m){
            std::cout << v.at(k).at(m) << " ";
        }
    }
    std::cout << "\n";
    std::cout << "Work took seconds: " <<  double(end - start) << "\n";
    std::cout << "Count Iterations: " << countIter <<  "\n";
}
