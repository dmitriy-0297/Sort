#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include <cmath>
#include "sort.h"

void intDivVec(std::vector<int> arr, std::vector<std::vector<int> > &v, int n, int div_vec){ //функция для добавления
    // в vec[vec] целочисленной части от деления массива
    int sizeIntParts = (n/div_vec)*div_vec; //ближайшее число кратное div_vec
    for (int i = 0; i < div_vec; ++i){
        std::vector<int> vec;
        v.push_back(vec);
    }
    for(int k = 0; k < sizeIntParts; ++k){
        for(int i = 0; i < div_vec; ++i){
            for(int j = 0; j < (n / div_vec); ++j){
                v.at(i).push_back(arr[k]);
                ++k;
            }
        }
    }
}

std::vector<std::vector<int> > divVec(std::vector<int> arr, int n, int div_vec){ // создание v[vec]
    std::vector<std::vector<int> > v;
    if (n % div_vec){ //если деление на части нецелочисленно
        intDivVec(arr, v, n, div_vec); //добвляем целочисленную часть
        int intDivPart = int(v.size()) * int(v.at(0).size()) ; //size части вектора которая целовисленно делиться
        std::vector<int> vec;
        v.push_back(vec);
        for(int i = intDivPart; i < n; ++i){
            v.at(div_vec).push_back(arr.at(i));
        }
    }else{ //деление на части целочисленно
        intDivVec(arr, v, n, div_vec); //добвляем целочисленную часть
    }
    return v;
}

void combAndSortVec(std::vector<int>& v_1, std::vector<int>& v_2){ //сортировка 2 частей массива
    std::vector<int> v;
    int vecSize = v_1.size();
    for(int i = 0; i < int(v_1.size()); i++){
        v.push_back(v_1[i]);
    }
    for(int i = 0; i < int(v_2.size()); i++){
        v.push_back(v_2[i]);
    }
    sortArray(v);
    v_1.clear();
    v_2.clear();
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

void outTable(std::vector<std::vector<int> > v){ //вывод таблицы в, где строке 1 элемент части массива и последний
    std::cout << "\n";
    std::cout << "Table:" << "\n";
    for (int i = 0; i < int(v.size()); i++){
        std::cout << v.at(i).at(0) << " " << v.at(i).at(int(v.at(i).size())-1);
        std::cout << '\n';
    }
}

int main(){
    int countIter = 0;
    double start, end; //переменные для замера времени
    int n = 0; //размер основного массива
    int div_vec = 0; //на сколько делин исходный массив
    int sizeParts = 0; //размер одной части
    std::cout << "Enter size array: ";
    std::cin >> n;
    std::cout << "Enter size parts ";
    std::cin >> sizeParts;
    div_vec = n/sizeParts;
    std::vector<int> Array;
    randArray(Array, n); //заполнение исходного массива
    std::vector<std::vector <int> > v(divVec(Array, n, div_vec)); //разбиение исходного массива на части
    #pragma omp parallel for //паралелим сортировку всех частей по отдельности
    for (int i = 0; i < int(v.size()); ++i){ //сортируем каждую часть массива
        sortArray(v.at(i));
    }

    start = omp_get_wtime(); //начало сортировки
    int flag = 0;
    for(int t = 0; t < int(log(n) / log(2)) * int(log(n) / log(2)); t++){ //основной цикл
        countIter++;
      for(int i = 0; i < int(v.size()) - 2; i++){ //вызов первого этапа сортировки
           combAndSortVec(v.at(i), v.at(i + 2));
       }

        std::vector<int> numbers; //вызов второго этапа сортировки
        for(int i = 0; i < int(v.size()); i++){
            numbers.push_back(i);
        }
        int j = int(numbers.size()-1);
        for(int i = 0; i < int(numbers.size()) + 1; i++){
            if(i < j){
            combAndSortVec(v.at(i), v.at(j));
            numbers.erase(numbers.begin() + i - 1);
            j--;
            }
            if(i < j){
            numbers.erase(numbers.begin() + j - 1);
            j--;
          }
        }

        for(int i = 0; i < int(v.size()) - 1; i++){ //вызов третьего этапа сортировки
            combAndSortVec(v.at(i), v.at(i + 1));
        }
      } //сортировка закончена

    end = omp_get_wtime();

    std::cout << "\n";
    std::cout << "Array sort: " << "\n"; //конечный отсортированный вектор
    for (int k = 0; k < int(v.size()); ++k){
        for (int m = 0; m < int(v.at(k).size()); ++m){
            std::cout << v.at(k).at(m) << " ";
        }
    }
    std::cout << "\n";
    std::cout << "Work took seconds: " <<  double(end - start) << "\n";//вывод времени работы программы
    std::cout << "Count Iterations: " << countIter <<  "\n";//вывод количества итераций до полной сортировки исходного массива
}
