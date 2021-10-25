#include <iostream>
#include <math.h>

using namespace std;

double Cost(double x) {
    return pow(2 * exp(x) - 2 / exp(x), 2);
}

double Grad(double x) {
    return 8 * (exp(x) + exp(-x)) * (exp(x) - exp(-x));
}

double GradientDescent(double x0, double alpha, double esilon = 1e-3, double loop = 1000) {
    double x = x0;
    for (int i = 0; i < loop; i++) {
        x = x - alpha * Grad(x);
        if (fabs(Grad(x)) < esilon) {
            break;
        }
    }
    return x;
}

int main() {
    double x0 = 0, alpha = 0.001;
    double x_min = GradientDescent(x0, alpha);
    cout << "Gia tri nho nhat cua ham so la: " << Cost(x_min) << " tai diem x = " << x_min << endl;
    return 0;
}