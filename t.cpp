#include <iostream>
#include <tuple>
using namespace std;

tuple<int, int> test() {
    return {1, 2};
}

int main()
{
    // tuple<int, int> a = test();
    // cout << get<0>(a) << " " << get<0>(a);
    int n = 3;
    double a = 1 / (double) n + 2;
    cout << a;
    return 0;
}