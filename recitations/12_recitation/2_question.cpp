#include<iostream>
#include<cstdlib>

using namespace std;

int hanoi(int n){
    if (n == 0) { 
        return n;
    } 
    return 2*hanoi(n-1)+1;
}

int main(){
    int input = 0;
    cout << "Enter the number of disks: " << endl;
    cin >> input;
    int answer = 0;
    answer = hanoi(input);
    cout << "The minimum number of moves is: " << answer << endl;
    return 0;
}