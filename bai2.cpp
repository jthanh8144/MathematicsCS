#include <Eigen>
using namespace Eigen;

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

/*
Điều kiện phân rã Cholesky:
- Ma trận vuông
- Ma trận đối xứng
- Ma trận xác định dương
*/