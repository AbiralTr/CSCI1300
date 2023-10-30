#include <iostream>
#include <vector>

using namespace std;

// Define the struct for Person.
struct Fish{

    string name;
    int gallons_required;

};

void displayFish(vector<Fish> fish_vector){
    for(Fish f : fish_vector){
        cout << f.name << endl;
    }
}

int main()
{
    Fish fish1 = {"Guppy One", 200};
    Fish fish2 = {"Guppy Two", 250};
    Fish fish3 = {"Guppiest", 10};

    vector<Fish> myFish = {fish1, fish2, fish3};

    displayFish(myFish);
    
    return 0;
}