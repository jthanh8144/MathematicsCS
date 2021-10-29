#include <iostream>
#include <math.h>

using namespace std;

double Cost(double x) {
    return x*x + 10*sin(x);
}

double Grad(double x) {
    return 2*x + 10*cos(x);
}

double NAG(double x0, double alpha = 0.1, double beta = 0.9, double esilon = 1e-4, double loop = 10000) {
    double x = x0;
    double v = 0;
    int i;
    for (i = 0; i < loop; i++) {
        double v_new = beta * v + alpha * Grad(x - beta*v);
        double x_new = x - v_new;
        if (fabs(x - x_new) < esilon) {
            break;
        }
        x = x_new;
        v = v_new;
    }
    cout << "So lan lap: " << i << endl;
    return x;
}

int main() {
    double x0 = 5;
    double x_min = NAG(x0);
    cout << "Gia tri nho nhat cua ham so la: " << Cost(x_min) << " tai diem x = " << x_min << endl;
    return 0;
}