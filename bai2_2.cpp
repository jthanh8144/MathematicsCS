#include <iostream>
#include <Eigen/Eigenvalues>
#include <Eigen/Core>
using namespace Eigen;
using namespace std;

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
