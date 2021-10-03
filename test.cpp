#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

void Eig() {
    int n;
    cout << "Nhap n = "; cin >> n;
    MatrixXd A(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A(" << i << ", " << j << ") = "; cin >> A(i, j);
        }
    }
    cout << endl << A << endl << endl;
    EigenSolver<MatrixXd> es(A);

    MatrixXd D = es.pseudoEigenvalueMatrix();
    MatrixXd V = es.pseudoEigenvectors();
    cout << "The pseudo-eigenvalue matrix D is:" << endl
         << D << endl;
    cout << "The pseudo-eigenvector matrix V is:" << endl
         << V << endl;
    // cout << "Finally, V * D * V^(-1) = " << endl
    //      << V * D * V.inverse() << endl;
}

void Nhap() {
    int n;
    cout << "Nhap n = "; cin >> n;
    // MatrixXd A(n, n);
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << "A(" << i << ", " << j << ") = "; cin >> A(i, j);
    //     }
    // }
    MatrixXd b(n, 1);
    for (int i = 0; i < n; i++) {
        cout << "b(" << i << ", 0) = "; cin >> b(i, 0);
    }
    cout << b << endl;
    cout << b / 1.2 << endl;
    // cout << A*b << endl;
    // cout << b*b.inverse();
}

int main() {
    // Eig();
    Nhap();
    // MatrixXd a;
    // a.setOnes(1, 3);
    // cout << a;
    return 0;
}