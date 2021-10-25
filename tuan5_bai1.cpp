#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

struct point {
    double x, y;
};

int n;
point *a;
point x, y;
double d_min = 1E20; 

bool cmp_x(const point a, const point b) {
    return a.x < b.x;
}

bool cmp_y(const point a, const point b) {
    return a.y < b.y;
}

void distance(const point &a, const point &b) {
    double dist = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
    if (dist < d_min) {
        d_min = dist;
        x = a;
        y = b;
    }
}

void find(int l, int r) {
    if (r <= l) return;
    if (r == l + 1) {
        distance(a[l], a[r]);
        if (cmp_y(a[l], a[r]) == false) swap(a[l], a[r]);
        return;
    }

    int m = (l + r) / 2;
    double midx = a[m].x;
    find(l, m);
    find(m+1, r);

    static point *t = new point [2*n];
    merge(a+l, a+m+1, a+m+1, a+r+1, t, cmp_y);
    copy(t, t+r-l+1, a+l);
    int tm = 0;
    for (int i = l; i <= r; i++) {
        if (abs(a[i].x - midx) < d_min) {
            for (int j = tm-1; j >= 0 && t[j].y > a[i].y - d_min; j--) {
                distance(a[i], t[j]);
            }
            t[tm++] = a[i];
        }
    }
}

int main() {
    cout << "Nhap so diem n = ";
    cin >> n;
    a = new point[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a, a+n, cmp_x);
    find(0, n-1);
    cout << "Khoang cach nho nhat la " << d_min
        << " giua hai diem (" << x.x << ", " << x.y << ") va (" << y.x << ", " << y.y << ")";
    return 0;
}

/*
Thuật toán:
B1: Sắp xếp N điểm theo x rồi thành 2 tập hợp bằng đường thẳng x = a
B2: Gọi đệ quy tìm cặp điểm gần nhất cho tập bên trái và tập bên phải. Sau khi gọi đệ quy có được khoảng cách giữa cặp điểm gần nhất là D.
B3: Sắp xếp theo y rồi tìm khoảng cách ngắn nhất giữa một điểm thuộc tập bên trái và một điểm thuộc tập bên phải. Chỉ cần xét những điểm có |x_i - a| < D vì các điểm bên ngoài khoảng đó chắc chắn sẽ có khoảng cách lớn hơn D.
*/