#include <iostream>
#include <math.h>
using namespace std;

struct haiMaTran
{
    double **a;
    double **b;
    int n;
    haiMaTran(double **A, double **B, int N) {
        a = A;
        b = B;
        n = N;
    }
};

double **a;
int n;

void Nhap() {
    cout << "Nhap n = "; cin >> n;
    a = new double *[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = "; cin >> a[i][j];
        }
    }
}

void Xuat(double **a, int n) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "\t\t";
        }
        cout << endl;
    }
}

double det(double **a, int n) {
    int s;
    double d = 0;
    if (n == 1) return a[0][0];
    if (n == 2) return a[0][0]*a[1][1] - a[0][1]*a[1][0];
    for (int k = 0; k < n; k++) {
        double **sm = new double *[n];
        for (int i = 0; i < n; i++) {
            sm[i] = new double [n];
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

double PhanBuDS(double **a, int n, int row, int col) {
    double **b = new double *[n];
    for (int i = 0; i < n; i++) {
        b[i] = new double [n];
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

double** NghichDao(double **a, int n) {
    double d = det(a, n);
    if (d == 0) {
        cout << "Ma tran a khong co nghich dao!" << endl;
    }
    else {
        double **b = new double *[n];
        for (int i = 0;i < n; i++) {
            b[i] = new double [n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = PhanBuDS(a, n, i, j);
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                double t = b[i][j];
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

double** MTDV(int n) {
    double **a = new double *[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                a[i][j] = 1;
            } else {
                a[i][j] = 0;
            }
        }
    }
    return a;
}

double** diag(double **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                a[i][j] = 0;
            }
        }
    }
    return a;
}

double** multiple(double **a, double **b, int n) {
    double **t = new double *[n];
    for (int i = 0; i < n; i++) {
        t[i] = new double [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = 0;
            for (int k = 0; k < n; k++) {
                t[i][j] += a[i][k] * b[k][j];
            } // ủa có sai chi mô bây :) 
        }
    }
    return t;
}

double** multipleBySeft(double *arr, int n) { 
    double **t = new double *[n];
    for (int i = 0; i < n; i++) {
        t[i] = new double [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = arr[i]*arr[j];
        }
    }
    return t;
}

double** sub(double **a, double **b, int n) {
    double **t = new double *[n];
    for (int i = 0; i < n; i++) {
        t[i] = new double [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = a[i][j] - b[i][j];
        }
    }
    return t;
}

double norm(double *arr, int n) {
    double rs = 0;
    for (int i = 0; i < n; i++) { 
        rs += arr[i] * arr[i]; 
    }
    return sqrt(rs);
}

double** houseHolder(double *arr, int n) {
    double t = arr[0] + norm(arr, n) * (arr[0] / abs(arr[0]));
    double *u = new double [n];
    for (int i = 0; i < n; i++) {
        u[i] = arr[i] / t;
    }
    u[0] = 1;
    double **temp = multipleBySeft(u, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] *= (2 / pow(norm(u, n), 2)); 
        }
    }
    double **H = MTDV(n);
    return sub(H, temp, n);
}

haiMaTran QR(double **a, int n) {
    double **Q = MTDV(n);
    for (int i = 0; i < n-1; i++) {
        double **H = MTDV(n);
        double *t = new double [n - i];
        int index = 0;
        for (int j = i; j < n; j++) {
            t[index++] = a[j][i];
        }
        double **temp = houseHolder(t, n - i);
        for (int j = i; j < n; j++) {
            for (int k = i; k < n; k++) {
                H[j][k] = temp[j-i][k-i];
            }
        }
        Q = multiple(Q, H, n);
        a = multiple(H, a, n);
    }
    return haiMaTran(Q, a, n);
}

haiMaTran eig(double **a, int n) {
    double **pQ = MTDV(n);
    double **t = new double *[n];
    for (int i = 0; i < n; i++) {
        t[i] = new double [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = a[i][j];
        }
    }
    for (int i = 0; i < 100; i++) {
        double** Q = QR(t, n).a;
        double** R = QR(t, n).b;
        pQ = multiple(pQ, Q, n);
        t = multiple(R, Q, n);
    }
    return haiMaTran(t, pQ, n);
}

int main() {
    Nhap();
    cout << endl << "A: ";
    Xuat(a, n);
    haiMaTran t = eig(a, n);
    cout << endl << "V: ";
    Xuat(t.b, n);
    cout << endl << "diag(lamda): ";
    Xuat(diag(t.a, n), n);
    cout << endl << "V^(-1): ";
    Xuat(NghichDao(t.b, n), n);
    return 0;
}