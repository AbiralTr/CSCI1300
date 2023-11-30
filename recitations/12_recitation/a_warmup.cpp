#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main() 
{
    srand(time(0));
    int random_number = rand();  
    cout << random_number << endl;
    return 0;
}