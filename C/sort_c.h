#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAXL

void swap (int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

void sort(int *a, int n)
{
  int sh = 0, b = 0;
  for(int j = 0; j < n; j++)
  {
    b = 0;
    for (int i = 0; i < n; ++i)
    {
      if (i*2 + 2 + sh < n)
      {
        if (a[i+sh] > a[i*2 + 1 + sh] || a[i + sh] > a[i*2 + 2 + sh])
  {
    if (a[i*2+1+sh] < a[i*2+2+sh])
    {
      swap (&a[i+sh], &a[i*2+1+sh]);
      b = 1;
    }
    else if (a[i*2+2+sh] < a[i*2+1+sh])
    {
      swap (&a[i+sh],&a[i*2+2+sh]);
      b = 1;
    }
  }
      }
      else if (i * 2 + 1 + sh < n)
      {
        if (a[i+sh] > a[i*2+1+sh])
  {
    swap (&a[i+sh], &a[i*2+1+sh]);
    b=1;
  }
      }
    }
    if (!b) sh++;
    if (sh+2==n)
      break;
  }
}
