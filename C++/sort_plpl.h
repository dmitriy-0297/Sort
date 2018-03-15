#include <iostream>
#include <vector>

void iswap (int *n1, int *n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void sortArray (std::vector<int>& v, int n) {
	// ----------- Сортировка ------------
	// Сортирует по возрастанию. Чтобы получить сортировку по убыванию,
	// поменяйте знаки сравнения в строчках, помеченных /*(знак)*/
    unsigned sh = 0u; // Смещение
    bool b;
    do {
	    b = false;
	    for (unsigned i = 0u; i < n; ++i) {
	        if (i * 2 + 2 + sh < n) {
		        if ((v[i + sh] > /*<*/ v[i * 2 + 1 + sh]) || (v[i + sh] > /*<*/ v[i * 2 + 2 + sh])) {
		            if (v[i * 2 + 1 + sh] < /*>*/ v[i * 2 + 2 + sh]) {
			            iswap(&v[i + sh], &v[i * 2 + 1 + sh]);
			            b = true;
		            } else if (v[i * 2 + 2 + sh] < /*>*/ v[i * 2 + 1 + sh]) {
		                iswap(&v[i + sh], &v[i * 2 + 2 + sh]);
		                b = true;
		            }
		        }
		        // Дополнительная проверка для последних двух элементов;
                // с её помощью можно отсортировать пирамиду
                // состоящую всего лишь из трёх элементов
		        if (v[i * 2 + 2 + sh] < /*>*/ v[i * 2 + 1 + sh]) {
			        iswap(&v[i * 2 + 1 + sh], &v[i * 2 + 2 + sh]);
                    b = true;
			    }
	        } else if (i * 2 + 1 + sh < n) {
	            if (v[i + sh] > /*<*/ v[ i * 2 + 1 + sh]) {
	                iswap(&v[i + sh], &v[i * 2 + 1 + sh]);
	                b = true;
	            }
	        }
	    }
	    if (!b)
            ++sh; // Смещение увеличивается, когда на текущем этапе сортировать больше нечего
    } while (sh + 2 < n); // Конец сортировки
}
