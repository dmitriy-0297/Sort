#ifndef PART_H
#define PART_H

struct Part {
  int beg = 0; // индекс первого элемента
  int len = 0; // длина интервала
  Part() {}
  Part(int b, int l) : beg(b), len(l) {}
};

#endif // PART_H
