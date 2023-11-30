#include<iostream>
#include<cstdlib>

using namespace std;

int fib(int num){
    int sequence_number = 0;
    if(num == 0){
        sequence_number = 0;
    } else if(num == 1){
        sequence_number = 1;
    } else{
        sequence_number = fib(num-1) + fib(num-2);
    }
    return sequence_number;
}

int main(){
    cout << fib(0) << endl;
    cout << fib(1) << endl;
    cout << fib(2) << endl;
    cout << fib(3) << endl;
    cout << fib(4) << endl;
    cout << fib(5) << endl;
    cout << fib(6) << endl;
    cout << fib(7) << endl;
    return 0;
}