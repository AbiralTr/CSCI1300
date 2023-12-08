#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    long int n = 0;
    cout << "Enter a positive intger:" << endl;
    cin >> n;
    if(n <= 0){
        cout << "Please enter a non-negative integer." << endl;
        return 0;
    }

    while(n != 1){
        if(n % 2 == 0){ // Even
            n = floor(sqrt(n));
            cout << n << endl;
            
        } else{ // Odd
            n = floor(pow(sqrt(n),3));
            cout << n << endl;
        }
    }

    return 0;
}
