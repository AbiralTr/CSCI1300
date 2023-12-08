#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int x = 0;
    double sigmoid = 0;
    cout << "Enter a value for x:" << endl;
    cin >> x;
    sigmoid = 1 / (1 + exp(-x));
    cout << "The sigmoid value for x=" << x << " is " << sigmoid << endl;

    return 0;
}
