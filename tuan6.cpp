#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

double sum_matrix_p(MatrixXd a) {
    double temp = 0;
    for (int i = 0; i < a.rows(); i++) {
        for (int j = 0; j < a.cols(); j++) {
            temp += a(i, j) * a(i, j);
        }
    }
    return temp;
}

void gradient_descent(MatrixXd x, MatrixXd y, int loop = 20000, double esilon = 0.001) {
    int n = x.cols();
    MatrixXd w(n, 1);
    for (int i = 0; i < n; i++) {
        w(i, 0) = 0;
    }

    int index = 0;
    double bias = 0;
    double cost = 0;
    for (int i = 0; i < loop; i++) {
        index = i;
        MatrixXd y_pred = x * w;
        for (int k = 0; k < y_pred.rows(); k++) {
            for (int j = 0; j < y_pred.cols(); j++) {
                y_pred(k, j) += bias;
            }
        }
        cost = sum_matrix_p(y_pred - y.transpose()) / (double) n ;
        if (cost < esilon) {
            break;
        }
        MatrixXd dw = (1 / (double) n) * (x.transpose() * (y_pred - y.transpose()));
        double db = 1 / (double) n * (y_pred - y.transpose()).sum();
        w -= dw * esilon;
        bias -= db * esilon;
    }
    cout << "Epoch: " << index << endl << "Weight: " << endl << w << endl
        << "Bias: " << bias << endl << "Cost: " << cost << endl;
}

int main() {
    MatrixXd x(4, 5);
    x << 1, 2, 3, 4, 5, 0, 2, 4, 6, 8, 1, 3, 5, 7, 9, 5, 10, 15, 20, 25;
    MatrixXd y(1, 4);
    y << 15, 20, 25, 75;
    gradient_descent(x, y);
    return 0;
}