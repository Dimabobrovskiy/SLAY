#include <iostream>
#include <vector>
#include "TridiagonalMatrix.h"


int main() {

  int size;
  std::cout << "Введите размер матрицы: ";
  std::cin >> size;

  TridiagonalMatrix matrix(size);
  matrix.MatrixInput();

  std::vector<double> rhs(size);
  std::cout << "Введите правую часть системы (через пробел, " << size << " элементов): ";
  for (int i = 0; i < size; ++i) {
    std::cin >> rhs[i];
  }

  std::vector<double> solution = matrix.solve(rhs);

  std::cout << "Решение: ";
  for (double x : solution) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  return 0;
}
