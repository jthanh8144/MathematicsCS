#include <iostream>
#include <algorithm>
#include <Eigen/Eigenvalues>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

void svd(MatrixXd A) {
    EigenSolver<MatrixXd> es1(A * A.transpose());
    MatrixXd U = es1.pseudoEigenvectors();
    EigenSolver<MatrixXd> es2(A.transpose() * A);
    MatrixXd V = es2.pseudoEigenvectors();

    MatrixXd temp;
    if (A.rows() > A.cols()) {
        temp = es2.pseudoEigenvalueMatrix();
    } else {
        temp = es1.pseudoEigenvalueMatrix();
    }
    MatrixXd S(1, temp.cols());
    for (int i = 0; i < temp.rows(); i++) {
        S(0, i) = sqrt(temp(i, i));
    }
    cout << endl << "U:" << endl << U << endl;
    cout << "S: " << endl << S << endl;
    cout << "V:" << endl << V.transpose() << endl;
}

int main() {
    int n, m;
    cout << "Nhap n = "; cin >> n;
    cout << "Nhap m = "; cin >> m;
    MatrixXd A(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "A(" << i << ", " << j << ") = "; cin >> A(i, j);
        }
    }
    svd(A);
    return 0;
}