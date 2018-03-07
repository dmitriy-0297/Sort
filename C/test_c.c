#include "sort_c.h"
#include <stdio.h>

/*void divArrays(int *a, int n)
{
  int k = 0;
  int mrArray[20][50];
    for (int i = 0; i < 20; i++){
      for (int j = 0; j < 50; j++){
        mrArray[i][j] = a[k];
        k++;
      }
    }
  for (int i = 0; i < 20; i++){
    for (int j = 0; j < 50; j++){
      printf ("%d ", mrArray[i][j]);
    }
    printf("\n");
  }
}*/

int main()
{
  int n = 1000;
  int first = 0;
  int last = 0;
  int a[n], i, sh = 0, b = 0;
  for (i = 0; i < n; ++i)
    a[i] = rand() % 100;
  printf("Array: \n");
  for(i = 0; i < n; i++){
    printf ("%i%c", a[i], (i!=n-1)?' ':'\n');
  }
  /*printf("Array[][]: \n");
  divArrays(a,n);*/
  sort(a, n);
  first = a[0];
  last = a[n-1];
  printf("First element: %d\n", first);
  printf("Last element: %d\n", last);
  return 0;
}
