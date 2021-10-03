#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

MatrixXd Nhap() {
    int n;
    cout << "Nhap n = "; cin >> n;
    MatrixXd A(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A(" << i << ", " << j << ") = "; cin >> A(i, j);
        }
    }
    return A;
}

MatrixXd Cholesky(MatrixXd a) {
    int n = a.rows();
    MatrixXd result(n, n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < i; k++) {
            double value = a(i, k);
            for (int j = 0; j < k; j++) {
                value -= result(i, j) * result(k, j);
            }
            result(i, k) = value / result(k, k);
        }
        double t = a(i, i);
        for (int j = 0; j < i; j++) {
            t -= result(i, j) * result(i, j);
        }
        result(i, i) = sqrt(t);
    }
    return result;
}

void RunCholesky(MatrixXd a) {
    int n = a.rows();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (a(i, j) != a(j, i)) {
                cout << endl << "Ma tran khong phai la ma tran doi xung nen khong the phan ra theo Cholesky!" << endl;
                return;
            }
        }
    }
    EigenSolver<MatrixXd> es(a);
    MatrixXd D = es.pseudoEigenvalueMatrix();
    for (int i = 0; i < n; i++) {
        if (D(i, i) < 0) {
            cout << endl << "Ma tran khong the phan ra theo Cholesky!" << endl;
            return;
        }
    }
    cout << endl << "L:" << endl;
    cout << Cholesky(a);
}

int main() {
    MatrixXd a = Nhap();
    RunCholesky(a);
    return 0;
}