#include <iostream>
using namespace std;

float **a;
int n;

void Nhap() {
    cout << "Nhap n = "; cin >> n;
    a = new float *[n];
    for (int i = 0; i < n; i++) {
        a[i] = new float [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = "; cin >> a[i][j];
        }
    }
}

void Xuat(float **a, int n) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "\t\t";
        }
        cout << endl;
    }
}

float det(float **a, int n) {
    int s, d = 0;
    if (n == 1) return a[0][0];
    if (n == 2) return a[0][0]*a[1][1] - a[0][1]*a[1][0];
    for (int k = 0; k < n; k++) {
        float **sm = new float *[n];
        for (int i = 0; i < n; i++) {
            sm[i] = new float [n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 1;j < n; j++) {
                if (i < k) sm[i][j-1] = a[i][j];
                else if (i > k) sm[i-1][j-1] = a[i][j];
            }
        }
        if (k % 2 == 0) s = 1;
        else s = -1;

        d += a[k][0]*s*det(sm, n - 1);
    }
    return d;
}

float PhanBuDS(float **a, int n, int row, int col) {
    float **b = new float *[n];
    for (int i = 0; i < n; i++) {
        b[i] = new float [n];
    }
    int x = -1, y;
    for (int i = 0; i < n; i++) {
        if (i == row)
            continue;
        x++;
        y = -1;
        for (int j = 0; j < n; j++) {
            if (j == col)
                continue;
            y++;
            b[x][y] = a[i][j];
        }
    }
    if ((row + col) % 2 == 0)
        return det(b, n - 1);
    return -det(b, n - 1);
}

float** NghichDao(float **a, int n) {
    float d = det(a, n);
    if (d == 0) {
        cout << "Ma tran a khong co nghich dao!" << endl;
    }
    else {
        float **b = new float *[n];
        for (int i = 0;i < n; i++) {
            b[i] = new float [n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = PhanBuDS(a, n, i, j);
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                float t = b[i][j];
                b[i][j] = b[j][i];
                b[j][i] = t;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] /= d;
            }
        }
        return b;
    }
    return nullptr;
}

// Éo biết làm thêm nên dừng ở đây :3

int main() {
    Nhap();
    Xuat(a, n);
    cout << "det(a) = " << det(a, n) << endl;
    Xuat(NghichDao(a, n), n);
    return 0;
}