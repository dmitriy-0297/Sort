#ifndef SORT_H
#define SORT_H
#include <vector>
#include <iostream>
#include <iterator>
typedef std::vector<int>::iterator Iter;


Iter get_midpoint(std::vector<int> &vect)
{
  std::vector<int>::iterator it = vect.begin();
  int middle = 0;
  if(vect.size() % 2 == 0) {
    middle =  vect.size() / 2;
  } else {
    middle = (vect.size() - 1) / 2;
  }
  std::advance(it, middle);
  return it;
}

std::vector<int> merge(std::vector<int> & first_vect, std::vector<int> & second_vect)
{
  std::vector<int> sorted_vect;
  auto first_it = first_vect.begin(),
        second_it = second_vect.begin();

  while(first_it != first_vect.end() && second_it != second_vect.end())
  {
      if(*first_it < *second_it)
      {
        sorted_vect.push_back(*first_it);
        first_it++;
      } else
      {
        sorted_vect.push_back(*second_it);
        second_it++;
      }
  }

  sorted_vect.insert(sorted_vect.end(), first_it, first_vect.end());
  sorted_vect.insert(sorted_vect.end(), second_it, second_vect.end());

  return sorted_vect;
}

std::vector<int> mergesort(std::vector<int> &unsorted_vector)
{
  Iter middle = unsorted_vector.begin();
  std::vector<int> sorted_vect, first_half, second_half, first_temp, second_temp;
  if(unsorted_vector.size() == 1)
  {
    return unsorted_vector;
  }
  else
  {
    middle = get_midpoint(unsorted_vector);
    first_temp.insert(first_temp.begin(), unsorted_vector.begin(), middle);
    second_temp.insert(second_temp.begin(), middle, unsorted_vector.end());
    first_half = mergesort(first_temp);
    second_half = mergesort(second_temp);
    sorted_vect = merge(first_half, second_half);
    return sorted_vect;
  }
}
#endif // SORT_H
