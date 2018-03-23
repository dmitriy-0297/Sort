#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include "sort_std.h"

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

std::vector<std::vector<int> > divVec(std::vector<int> arr, int n, int div_vec, char out){ // создание v[vec]
    std::vector<std::vector<int> > v;
    if (n % div_vec){ //если деление на части нецелочисленно
        intDivVec(arr, v, n, div_vec); //добвляем целочисленную часть
        int intDivPart = int(v.size()) * int(v.at(0).size()) ; //size части вектора которая целовисленно делиться
        std::vector<int> vec;
        v.push_back(vec);
        for(int i = intDivPart; i < n; ++i){
            v.at(div_vec).push_back(arr.at(i));
        }
        if(out == 'y'){
            std::cout << '\n';
            std::cout << "Vector[vector]: " << std::endl;
            for (int i = 0; i < div_vec; ++i){
                for (int j = 0; j < (n/div_vec); ++j){
                    std::cout << v.at(i).at(j) << " ";
                }
                std::cout << "\n";
            }
        }
    }else{ //деление на части целочисленно
        intDivVec(arr, v, n, div_vec); //добвляем целочисленную часть
        if(out == 'y'){
            std::cout << '\n';
            std::cout << "Vector[vector]: " << std::endl; //выводим вектор векторов
            for (int i = 0; i < int(v.size()); ++i){
                for (int j = 0; j < int(v.at(i).size()); ++j){
                    std::cout << v.at(i).at(j) << " ";
                }
                std::cout << "\n";
            }
        }
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
    char out;//узнаем у пользователя стоит ли выводить промежуточные результаты или нет
    std::cout << "Output table and sort parts? (y/n): ";
    std::cin >> out;
    if (out != 'y' && out != 'n'){
        std::cout << "Error input n/y ..." << std::endl;
        return 0;
    }
    int countIter = 0;
    double start, end; //переменные для замера времени
    int n = 0; //размер основного массива
    int div_vec = 0; //на сколько делин исходный массив
    std::cout << "Enter size array: ";
    std::cin >> n;
    std::cout << "Enter count parts for div array: ";
    std::cin >> div_vec;
    std::vector<int> Array;
    randArray(Array, n); //заполнение исходного массива
    std::vector<std::vector <int> > v(divVec(Array, n, div_vec, out)); //разбиение исходного массива на части
    start = omp_get_wtime(); //начало сортировки
    for (int i = 0; i < int(v.size()); ++i){ //сортируем каждую часть массива
        sortArray(v.at(i));
    }
    if(out == 'y'){
        std::cout << "\n";
        std::cout << "Array sort parts: " << std::endl; //вывод отсортированых частей вектора
        for (int k = 0; k < int(v.size()); ++k){
            for (int m = 0; m < int(v.at(k).size()); ++m){
                std::cout << v.at(k).at(m) << " ";
            }
            std::cout << "\n";
        }
        outTable(v); //вывод таблицы
    }
    for(int i = 0; i < int(v.size()) - 1; ++i){
        for(int j = i; j < int(v.size()); ++j){
            if(i == j){
                j++;
            }
            #pragma omp paralle //раралелим проверку
            if ((v.at(i).at((n/div_vec - 1)) > v.at(j).at(0)) || (v.at(i).at(0) > v.at(j).at(0)) //условие для проверки, отсортирован ли массив
                    || (v.at(i).at(n/div_vec - 1) > v.at(j).at(n/div_vec - 1)) || (v.at(i).at(0) > v.at(j).at(n/div_vec - 1))){
                if (out == 'y'){
                    std::cout << "\n";
                    std::cout << "two parts sort: " << "\n"; //вывод номеров строк таблицы, которы будут отсортированны между собой
                    std::cout << i + 1 << " whith " << j + 1 << "\n";
                }
                combAndSortVec(v.at(i), v.at(j)); //вызов функции сортировки для 2 частей массива
                countIter++;
                if (out == 'y'){
                    outTable(v); //вывод таблицы
                }
            }
        }
    }
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
