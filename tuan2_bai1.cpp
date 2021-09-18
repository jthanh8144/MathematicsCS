#include <iostream>
using namespace std;

int a_mu_m_mod_n(long a, long m, int n) {
    long d = 1;
    a %= n;
    m %= n - 1;
    while (m > 0) {
        if (m % 2 != 0) {
            d = d * (a % n);
        }
        a = a * a % n;
        m /= 2;
    }
    return (int) d;
}

int main() {
    long a, m;
    int n;
    cout << "Nhap a = "; cin >> a; // 2004
    cout << "Nhap m = "; cin >> m; // 2004
    cout << "Nhap n = "; cin >> n; // 11
    cout << a << "^" << m << " mod " << n << " = " << a_mu_m_mod_n(a, m, n) << endl; //5
    return 0;
}