#include <iostream>
#include <math.h>

using namespace std;

long double Cost(long double x) {
    return pow((exp(x) + 3*x - 10), 2) + x*x;
}

long double Grad(long double x) {
    return 2*exp(x*x) + (6*x-14) * exp(x) + 20*x -60;
}

long double NAG(long double x0, long double alpha = 0.1, long double beta = 0.9, long double esilon = 1e-4, long double loop = 10000) {
    long double x = x0;
    long double v = 0;
    int i;
    for (i = 0; i < loop; i++) {
        long double v_new = beta * v + alpha * Grad(x);
        long double x_new = x - v_new;
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
    long double x0 = 1.5;
    long double x_min = NAG(x0, 0.9, 0.1, 1e-5, 100);
    cout << "Gia tri nho nhat cua ham so la: " << Cost(x_min) << " tai diem x = " << x_min << endl;
    return 0;
}