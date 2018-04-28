#include "timsort.h"

void merge(std::vector<int> &inputArray, std::vector<Part> &parts, bool isXY, std::vector<int> &tmp) {
  Part f = parts[parts.size() - dy]; //берет предпоследний элемент
  Part s = isXY ? parts[parts.size() - dx] : parts[parts.size() - dz]; // берет одного из соседов предпоследнего элемента
  if (f.beg > s.beg) {
      std::swap(f, s);
  }
  int posF = 0, posS = s.beg, pos = f.beg - 1;

  int lstF = f.len, lstS = s.beg + s.len;
  copy(inputArray.begin() + f.beg + posF, inputArray.begin() + f.beg + lstF, tmp.begin()); // запись предпоследнего в tmp

  int fAmount = 0, sAmount = 0; //длина подпоследовательности
  for (size_t i = 0; posF < lstF && posS < lstS; ++i) { //пока какая-нибудь из частей не дойдет до конца
    if (tmp[posF] < inputArray[posS]) { //если
      inputArray[++pos] = tmp[posF++];
      ++fAmount;
      sAmount = 0;
      if (fAmount == 7) {
          if (*(tmp.begin() + lstF) > inputArray[posS]) {
            copy(tmp.begin() + posF, tmp.begin() + lstF, inputArray.begin() + pos + 1);
            pos += lstF - posF;
            posF += lstF - posF;
          }
        std::vector<int>::iterator it = upper_bound(tmp.begin() + posF, tmp.begin() + lstF, inputArray[posS]);
        copy(tmp.begin() + posF, it, inputArray.begin() + pos + 1);
        pos += it - (tmp.begin() + posF);
        posF += it - (tmp.begin() + posF);
      }
    }
    else {
      inputArray[++pos] = inputArray[posS++];
      fAmount = 0;
      ++sAmount;
      if (sAmount == 7) {
          if (*(inputArray.begin() + lstS) > tmp[posF]) {
            copy(inputArray.begin() + posS, inputArray.begin() + lstS, inputArray.begin() + pos + 1);
            pos += lstS - posS;
            posS += lstS - posS;
          }
        std::vector<int>::iterator it = upper_bound(inputArray.begin() + posS, inputArray.begin() + lstS, tmp[posF]);
        copy(inputArray.begin() + posS, it, inputArray.begin() + pos + 1);
        pos += it - (inputArray.begin() + posS);
        posS += it - (inputArray.begin() + posS);
      }
    }
  }
  copy(tmp.begin() + posF, tmp.begin() + lstF, inputArray.begin() + pos + 1);
}

void tryMerge(std::vector<int> &inputArray, std::vector<Part> &parts, std::vector<int> &tmp, bool isMerge)  {
    for (int i = 0; parts.size() > 1; ++i) {
    int x = parts[parts.size() - dx].len;
    int y = parts.size() < 2 ? 0 : parts[parts.size() - dy].len;
    int z = parts.size() < 3 ? 0 : parts[parts.size() - dz].len;
    if (parts.size() >= 3 && z <= x + y) {
      if (z < x) {
        merge(inputArray, parts, false, tmp);
        parts[parts.size() - dz].len += parts[parts.size() - dy].len;
        parts[parts.size() - dy] = parts[parts.size() - dx];
        parts.pop_back();
      } else {
        merge(inputArray, parts, true, tmp);
        parts[parts.size() - dy].len += parts[parts.size() - dx].len;
        parts.pop_back();
      }
    } else if (isMerge || y <= x) {
      merge(inputArray, parts, true, tmp);
      parts[parts.size() - dy].len += parts[parts.size() - dx].len;
      parts.pop_back();
    } else {
      break;
    }
  }
}

void timsort(std::vector<int> &inputArray, std::vector<Part>& parts, std::vector<int>& tmp, int partSize) {
  int inputArrSize = inputArray.size();
  int i;
  #pragma omp parallel for proc_bind(spread) private(i)
  for (i = 0; i < inputArrSize; i += partSize)  {
    std::sort(inputArray.begin()+i,inputArray.begin() + i + std::min(partSize, inputArrSize - i));
  }
  int j;
 #pragma omp parallel for proc_bind(spread) private(j)
  for (j = 0; j < inputArrSize; j += partSize)  {
#pragma omp critical
      {
    parts.push_back(Part(j, std::min(partSize, inputArrSize - j)));
    tryMerge(inputArray, parts, tmp);
      }
  }
  for (int ii = 0; parts.size() != 1; ++ii) {
    tryMerge(inputArray, parts, tmp, true);
  }
}
