#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main() 
{
    srand(time(NULL));
    int random_number = 0;
    random_number = rand() % 32 + 1;
    cout << "Number generated is " << random_number << endl;
    return 0;
}