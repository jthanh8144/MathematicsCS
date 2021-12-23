#include <iostream>
using namespace std;

#define ll long long

void Bai1() {
    ll n, mu;
    cout << "Nhap n = "; cin >> n;
    for (int i = 2; i*i <= n; i++) {
        mu = 0;
        while (n % i == 0) {
            mu++;
            n /= i;
        }
        if (mu != 0) {
            cout << i << "^" << mu << " ";
        }
        if (n == 0) break;
    }
}

void Bai2() {
    ll n;
    cout << "Nhap n = "; cin >> n;
    for (int i = 0; i <= n; i++) {
        ll sum = 0;
        for (int j = 1; j < n; j++) {
            if (i % j == 0) sum += j;
        }
        if (sum == i) cout << i << " ";
    }   
}

void Bai() {
    cout << "10 = 2x5 = 1x10";
    cout << "   = (1 + 1)(4 + 1) = (9 + 1)";
    cout << "<=> p1^1 + p2^4  |  p^9";
    cout << "T(10) min <=> n = 3^1 + 2^4  |  2^9";
    cout << "T(10) min <=> n = 3^1 + 2^4";
}

void Bai3() {
    ll n;
    cout << "Nhap n = "; cin >> n;
    bool a[100000];
    for (int i = 2; i < n; i++) a[i] = true;

    for (int i = 2; i*i <= n; i++) {
        if (a[i] == true) {
            for (int j = i*2; j <= n; j += i) {
                a[j] = false;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == true) cout << i << " ";
    }
}

int gcd(ll m, ll n) {
    if (n == 0) return m;
    return gcd(n, m % n);
}

void Bai4() {
    ll m, n;
    cout << "Nhap m = "; cin >> m;
    cout << "Nhap n = "; cin >> n;
    cout << "gcd(" << m << ", " << n << ") = " << gcd(m, n);
}

int main() {
    // Bai1();
    // Bai2();
    // Bai();
    // Bai3();
    // Bai4();
    return 0;
}