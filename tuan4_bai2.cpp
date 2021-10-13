#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// --------------- helper ---------------
VectorXd M_k_toV(MatrixXd a, int k) {
    int n = a.cols();
    VectorXd t(n);
    for (int i = 0; i < n; i++) {
        t(i) = a(k, i);
    }
    return t;
}

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

void Append(MatrixXd &a, MatrixXd b, int k) {
    // thêm mt b vào hàng k của a
    int col = a.cols();
    for (int i = 0; i < col; i++) {
        a(k, i) = b(0, i);
    }
}

// --------------- main ---------------
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
    v.setOnes(k, 1);
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

    MatrixXd s(k, 1);
    MatrixXd u(m, n);
    MatrixXd v(k, k);

    for (int i = 0; i < k; i++) {
        MatrixXd t = a;
        for (int j = 0; j < i; j++) {
            t -= s(j, 0) * outer(M_k_toV(u, j), M_k_toV(v, j));
        }
        MatrixXd ut;
        MatrixXd vt;
        double sigma;
        if (n > m) {
            vt = svdDominantEigen(t, epsilon);
            MatrixXd uUnnormalized = a * vt;
            sigma = uUnnormalized.norm();
            ut = uUnnormalized / sigma;
        } else {
            ut = svdDominantEigen(t, epsilon);
            MatrixXd vUnnormalized = a.transpose() * ut;
            sigma = vUnnormalized.norm();
            vt = vUnnormalized / sigma;
        }
        MatrixXd st(1, 1);
        st(0, 0) = sigma;
        Append(s, st, i);
        Append(u, ut.transpose(), i);
        Append(v, vt.transpose(), i);
    }

    s = s.transpose();
    cout << endl << "S: " << endl << s << endl;
    cout << "U_T: " << endl << u.transpose() << endl;
    cout << "V: " << endl << v << endl;
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