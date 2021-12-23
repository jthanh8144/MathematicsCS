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

/*
Điều kiện phân rã:
- Là ma trận vuông, không suy biến 
- Là ma trận vuông đối xứng, không suy biến 
- Là ma trận phân rã bởi cholesky 
- Là bất kỳ mà trận thực

Thuật toán: 
B1: Nhập m, n, ma trận A(m x n) 
B2: Tính chỉ số riêng của ma trận A.AT : ʎ1, ʎ2 , …, ʎn - Lấy oi = √ʎ𝑖 
B3: Tính vector riêng của A.AT 
B4: Xây dựng ma trận D (m x n) với trị riêng là đường chéo của ma trận 
B5: Xây dựng ma trận U (m x m) là ma trận trực giao từ vector riêng trái 
B6: Xây dựng ma trận V (n x n) là ma trận trực giao từ vector riêng phải 
B7: Chuyển vị ma trận V ð A(m x n) = U(m x m) x D(m x n) x V(n x n)T
*/