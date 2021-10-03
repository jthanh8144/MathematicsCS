#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

MatrixXd outer(VectorXd a, VectorXd b) {
    int m = a.size();
    int n = b.size();
    MatrixXd t(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            t(i, j) = a[i] * b[j];
        }
    }
    return t;
}

double EigenValue(MatrixXd a, MatrixXd v) {
    MatrixXd t = a * v;
    for (int i = 0; i < a.rows(); i++) {
        t(i, 0) /= v(i, 0);
    }
    return t(0, 0);
}

MatrixXd svdDominantEigen(MatrixXd a, double epsilon = 0.01) {
    int n = a.rows();
    int m = a.cols();
    int k = min(n, m);
    MatrixXd v;
    v.setOnes(1, k);
    v = v / sqrt(k);
    if (n > m) {
        a = a.transpose() * a;
    } else {
        a = a * a.transpose();
    }
    double ev = EigenValue(a, v);
    MatrixXd vNew;
    while (true) {
        MatrixXd av = a * v;
        vNew = av / av.norm();
        double evNew = EigenValue(a, vNew);
        if (abs(ev - evNew) < epsilon) {
            break;
        }
        v = vNew;
        ev = evNew;
    }
    return vNew;
}

void svd(MatrixXd a, double epsilon = 1e-10) {
    int n = a.rows();
    int m = a.cols();
    int k = min(n, m);
    
}

int main() {
    // VectorXd a(3), b(3);
    // a[0] = 1;
    // a[1] = 2;
    // a[2] = 3;
    // b[0] = 3;
    // b[1] = 4;
    // b[2] = 5;
    // cout << outer(a, b);

    int n;
    cout << "Nhap n = "; cin >> n;
    MatrixXd A(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A(" << i << ", " << j << ") = "; cin >> A(i, j);
        }
    }
    MatrixXd b(n, 1);
    for (int i = 0; i < n; i++) {
        cout << "b(" << i << ", 0) = "; cin >> b(i, 0);
    }
    cout << EigenValue(A, b);
    return 0;
}