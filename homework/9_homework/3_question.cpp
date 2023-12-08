#include <iostream>
#include <cmath>

using namespace std;

int main(){
    char pass_type;
    double budget = 0;
    int add_ons = 0;
    double price = 0;

    cout << "Enter the desired pass type (S for Student, P for Professional, V for VIP, K for Speaker):" << endl;
    cin >> pass_type;
    switch(pass_type){
        case 'S':
            price += 35.5;
            break;
        case 'P':
            price += 75.25;
            break;
        case 'V':
            price += 150.75;
            break;
        case 'K':
            price += 200.5;
            break;
        default:
            break;
    }
    cout << "Enter the number of workshop add-ons:" << endl;
    cin >> add_ons;
    price += add_ons*50;
    cout << "Enter your budget:" << endl;
    cin >> budget;
    if(budget >= price){
        budget -= price;
        cout << "Pass purchase successful! Pass type: " << pass_type << ", Workshops: " << add_ons << ", Total cost: $" << price << ", Remaining budget: $" << budget << endl;
    } else{
        cout << "Pass purchase failed. Insufficient funds." << endl;
    }

    return 0;
}
