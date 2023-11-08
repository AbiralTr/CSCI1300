#include "Aquarium.cpp"

using namespace std;

int findFishAmongAquariums(Aquarium aquariums[], int length, string fish_name){
    int aquariumSize = 0;  
    bool foundFish = false;
    int index = -1;
    for(int i = 0; i < length; i++){
        if(!foundFish){
            for(int j = 0; j < aquariums[i].getAvailableFish().size(); j++){
                if(aquariums[i].getAvailableFish().at(j).name == fish_name){
                    foundFish = true;
                    index = i;
                }
            }
        } else{
            break;
        }
    }

    return index;
}

int findAquariumWithMostFish(Aquarium aquariums[], int length){
    int maxCount = 0;
    int index = 0; 
    for(int i = 0; i < length-1; i++){
        if(aquariums[i+1].getSelectedFish().size() > aquariums[i].getSelectedFish().size()){
            index = i+1;
            maxCount = aquariums[i+1].getSelectedFish().size();
        } else{
            index = i;
            maxCount = aquariums[i].getSelectedFish().size();
        }
    }
    return index;
}

int main(){
    Aquarium aquarium1 = Aquarium();
    aquarium1.loadFish("aquarium1.txt");
    Aquarium aquarium2 = Aquarium();
    aquarium1.loadFish("aquarium2.txt");
    Aquarium aquarium3 = Aquarium();
    aquarium1.loadFish("aquarium3.txt");

    Aquarium aquariums[3] = {aquarium1, aquarium2, aquarium3};

    // fish is in aquarium2.txt (index 1)
    cout << findFishAmongAquariums(aquariums, 3, "Halfmoon Betta") << endl;

    // highest count - should output index 0 or 1 (which both contains 15 fish count)
    cout << findAquariumWithMostFish(aquariums, 3) << endl;

    return 0;
}

// recitation 10: 1a: The issue is that the command line does not include .\AquariumDriver.cpp
// recitation 10: 1b: The command line is: g++ -Werror -Wall -Wpedantic -std=c++17 .\Aquarium.cpp .\AquariumDriver.cpp


