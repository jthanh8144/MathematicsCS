#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int ExtendedEuclidAlgo( int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    else {
        int x1, y1;
        int gcd = ExtendedEuclidAlgo(b, a % b, x1, y1); 
        x = y1;
        y = x1 - floor(a / b) * y1;
        return gcd;
    }
}
int linearCongruence(int A, int B, int N) {
    A = A % N;
    B = B % N;
    int u = 0, v = 0;
    int d = ExtendedEuclidAlgo(A, N, u, v);
    if (B % d != 0) {
        cout << -1 << endl;
        return 0;
    }
    int x0 = (u * (B / d)) % N;
    if (x0 < 0) x0 += N;
    return ((x0 + 0 * (N / d)) % N);
}
void run(int a1, int a2, int a3, int b1, int b2, int b3) {
    int M = b1*b2*b3;
    double M1 = M / b1;
    double M2 = M / b2;
    double M3 = M / b3;
    cout << M1*linearCongruence(M1, a1, b1) + M2*linearCongruence(M2, a2, b2) + M3*linearCongruence(M3, a3, b3);
}
int main()
{
    int a1 = 2, b1 = 5; 
    int a2 = 5, b2 = 6; 
    int a3 = 2, b3 = 7;
    run(a1, a2, a3, b1, b2, b3);
    return 0;
}