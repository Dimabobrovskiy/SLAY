#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void printVector(const vector<double>& vec) {
    for (const auto& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// Метод простой итерации
vector<double> simpleIteration(const vector<vector<double>>& A, const vector<double>& b, double eps, int maxIter) {
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> x_new(n, 0.0);
    int iter = 0;

    auto start = high_resolution_clock::now();

    while (iter < maxIter) {
        for (int i = 0; i < n; ++i) {
            x_new[i] = b[i];
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    x_new[i] -= A[i][j] * x[j];
                }
            }
            x_new[i] /= A[i][i];
        }

        double diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += abs(x_new[i] - x[i]);
        }

        x = x_new;
        iter++;

        if (diff < eps) {
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Simple Iteration: " << iter << " iterations, " << duration.count() << " microseconds" << endl;

    return x;
}

// Метод Якоби
vector<double> jacobi(const vector<vector<double>>& A, const vector<double>& b, double eps, int maxIter) {
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> x_new(n, 0.0);
    int iter = 0;

    auto start = high_resolution_clock::now();

    while (iter < maxIter) {
        for (int i = 0; i < n; ++i) {
            x_new[i] = b[i];
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    x_new[i] -= A[i][j] * x[j];
                }
            }
            x_new[i] /= A[i][i];
        }

        double diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += abs(x_new[i] - x[i]);
        }

        x = x_new;
        iter++;

        if (diff < eps) {
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Jacobi: " << iter << " iterations, " << duration.count() << " microseconds" << endl;

    return x;
}

// Метод Гаусса-Зейделя
vector<double> gaussSeidel(const vector<vector<double>>& A, const vector<double>& b, double eps, int maxIter) {
    int n = A.size();
    vector<double> x(n, 0.0);
    int iter = 0;

    auto start = high_resolution_clock::now();

    while (iter < maxIter) {
        vector<double> x_new = x;
        for (int i = 0; i < n; ++i) {
            x_new[i] = b[i];
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    x_new[i] -= A[i][j] * x_new[j];
                }
            }
            x_new[i] /= A[i][i];
        }

        double diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += abs(x_new[i] - x[i]);
        }

        x = x_new;
        iter++;

        if (diff < eps) {
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Gauss-Seidel: " << iter << " iterations, " << duration.count() << " microseconds" << endl;

    return x;
}

int main() {

    vector<vector<double>> A = {{10, -1, 2},
                                {-1, 11, -1},
                                {2, -1, 10}};
    vector<double> b = {6, 25, -11};

    double eps = 1e-6;
    int maxIter = 1000;

    vector<double> x_si = simpleIteration(A, b, eps, maxIter);
    vector<double> x_jacobi = jacobi(A, b, eps, maxIter);
    vector<double> x_gs = gaussSeidel(A, b, eps, maxIter);

    cout << "Simple Iteration Solution: ";
    printVector(x_si);

    cout << "Jacobi Solution: ";
    printVector(x_jacobi);

    cout << "Gauss-Seidel Solution: ";
    printVector(x_gs);

    return 0;
}