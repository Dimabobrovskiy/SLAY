#include <iostream>
#include <vector>
#include <stdexcept>

class TridiagonalMatrix {
 private:
  int n; // Размер матрицы
  std::vector<double> sub;  // Нижняя диагональ (длина n-1)
  std::vector<double> main; // Главная диагональ (длина n)
  std::vector<double> super; // Верхняя диагональ (длина n-1)

 public:
 
  TridiagonalMatrix(int size) : n(size), sub(size - 1), main(size), super(size - 1) {}

  // Ввод элементов матрицы от пользователя
  void MatrixInput() {
    std::cout << "Введите элементы верхней диагонали (через пробел, " << n - 1 << " элементов): ";
    for (int i = 0; i < n - 1; ++i) {
      std::cin >> super[i];
    }

    std::cout << "Введите элементы главной диагонали (через пробел, " << n << " элементов): ";
    for (int i = 0; i < n; ++i) {
      std::cin >> main[i];
    }

    std::cout << "Введите элементы нижней диагонали (через пробел, " << n - 1 << " элементов): ";
    for (int i = 0; i < n - 1; ++i) {
      std::cin >> sub[i];
    }
  }

  // Решение системы методом прогонки
  std::vector<double> solve(const std::vector<double> &rhs) {
    if (rhs.size() != n) {
      throw std::invalid_argument("RHS vector size does not match matrix size");
    }

    std::vector<double> modified_main = main;
    std::vector<double> modified_rhs = rhs;

    // Прямой ход
    for (int i = 1; i < n; ++i) {
      double m = sub[i - 1] / modified_main[i - 1];
      modified_main[i] -= m * super[i - 1];
      modified_rhs[i] -= m * modified_rhs[i - 1];
    }

    // Обратный ход
    std::vector<double> solution(n);
    solution[n - 1] = modified_rhs[n - 1] / modified_main[n - 1];

    for (int i = n - 2; i >= 0; --i) {
      solution[i] = (modified_rhs[i] - super[i] * solution[i + 1]) / modified_main[i];
    }

    return solution;
  }
};

