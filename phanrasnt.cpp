#include <iostream>
using namespace std;

void PhanRa(int n) {
    cout << n << " = ";
    int dem;
    for(int i = 2; i <= n; i++){
        dem = 0;
        while(n % i == 0){
            ++dem;
            n /= i;
        }
        if(dem){
            cout << i;
            if(dem > 1) cout << "^" << dem;
            if(n > i){
                cout << " * ";
            }
        }
    }
}

int main() {
    int n = 26000;
    PhanRa(n);
    return 0;
}