#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    int ducks= 0;
    double price;
    double discount = 0;
    cout << "How many ducks would you like to order?" << endl;
    cin >> ducks;
    if(ducks < 0){
        cout << "Please enter a non-negative input." << endl;
        return 0;
    }

    if(ducks <= 20){
        discount = 0.0;
    } else if(ducks > 20 && ducks <= 100){
        discount = 0.1;
    } else if(ducks > 100 && ducks <= 500){
        discount = 0.2;
    } else if(ducks > 500){
        discount = .5;
    }
    
    price = ducks*.5;
    price -= price*discount;
    cout << "Your total is $" << price << endl;

    return 0;
}
