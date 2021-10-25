#include <iostream>
#include <algorithm>
using namespace std;

struct point {
    double x, y;
    void operator-= (point p) {
        this->x -= p.x; 
        this->y -= p.y; 
    }
};

point origin;
int n;
point *a;

// Kiểm tra góc AOB dương hay âm (kiểm tra B thuộc nửa mặt phẳng bờ OA nào)
bool bag(point O, point A, point B) {
    A -= O;
    B -= O;
    return A.x * B.y > A.y * B.x;
}

bool cmp(point A, point B) {
    if (A.y == B.y) {
        return A.x < B.x;
    } else {
        return A.y < B.y;
    }
}

bool cmp_bag(point A, point B) {
    return bag(origin, A, B); 
}

void graham() {
    sort(a + 1, a + n + 1, cmp);
    origin = a[1];
    sort(a + 2, a + n + 1, cmp_bag);
    a[0] = a[n];
    a[n + 1] = a[1];
    int j = 1;
    for (int i = 1; i <= n + 1; i++) { 
        while (j > 2 && !bag(a[j - 2], a[j - 1], a[i])) j--;
        a[j++] = a[i];
    }
    n = j - 2;
}

int main() {
    cout << "Nhap n = ";
    cin >> n;
    a = new point [n+2];
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    graham();
    for (int i = 1; i <= n; i++) {
        cout << a[i].x << "\t" << a[i].y << endl;
    }
    return 0;
}

/*
Thuật toán:
- Tìm một điểm chắc chắn thuộc về bao lồi (điểm có x nhỏ nhất) làm tâm O (origin)
- Sắp xếp các điểm còn lại theo góc. Góc của điểm A là góc tạo bởi tia OA và phương ngang.
- Dùng một stack có tính chất bag (bao) của ba điểm liên tiếp theo thứ tự. Lần lượt chèn các điểm theo thứ tự đã sắp xếp trước đó từ đỉnh số 1 đến đỉnh n + 1 (với a[n + 1] = a[1]) và kiểm tra tính bag của stack đó. 
- Sau khi kết thúc vòng lặp ta thu được stack chứa các điểm thuộc bao lồi
*/