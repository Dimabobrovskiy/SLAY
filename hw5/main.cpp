#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция для умножения матрицы на вектор
vector<double> matrixVectorMultiply(const vector<vector<double>>& A, const vector<double>& x) {
    int n = A.size();
    vector<double> result(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

// Функция для сложения двух векторов
vector<double> vectorAdd(const vector<double>& a, const vector<double>& b) {
    int n = a.size();
    vector<double> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

// Функция для умножения вектора на скаляр
vector<double> vectorScalarMultiply(const vector<double>& v, double scalar) {
    int n = v.size();
    vector<double> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = v[i] * scalar;
    }
    return result;
}

// Чебышёвское ускорение для МПИ
vector<double> chebyshevAcceleration(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& x0, int n_iter, double lambda_min, double lambda_max) {
    vector<double> x = x0;
    for (int k = 1; k <= n_iter; ++k) {
        double tau_k = 2.0 / (lambda_max + lambda_min + (lambda_max - lambda_min) * cos((2 * k - 1) * M_PI / (2 * n_iter)));
        vector<double> residual = vectorAdd(b, vectorScalarMultiply(matrixVectorMultiply(A, x), -1.0));
        x = vectorAdd(x, vectorScalarMultiply(residual, tau_k));
    }
    return x;
}

int main() {
    // Пример матрицы A и вектора b
    vector<vector<double>> A = {{4, 1}, {1, 3}};
    vector<double> b = {1, 2};
    vector<double> x0 = {0, 0}; // Начальное приближение

    double lambda_min = 2; // Минимальное собственное значение
    double lambda_max = 5; // Максимальное собственное значение
    int n_iter = 10; // Количество итераций

    vector<double> x_cheb = chebyshevAcceleration(A, b, x0, n_iter, lambda_min, lambda_max);

    cout << "Решение с чебышёвским ускорением:" << endl;
    for (double val : x_cheb) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}