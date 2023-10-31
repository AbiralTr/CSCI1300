#include <iostream>
#include <vector>
#include "Aquarium.h"

using namespace std;

Aquarium::Aquarium(){
    _aquarist_name = "";
    _gallons_used = 0;
}

Aquarium::Aquarium(string name){
    _aquarist_name = name;
}

void Aquarium::setAquaristName(string s){
            _aquarist_name = s;
        }

string Aquarium::getAquaristName(){
    return _aquarist_name;
}

void Aquarium::setGallonsUsed(int i){
    _gallons_used = i;
}

int Aquarium::getGallonsUsed(){
    return _gallons_used;
}

bool Aquarium::loadFish(string file_name){
    ifstream file(file_name);
    if(!file.is_open()){
        return false;
    }
    string line;
    string fish_name;
    int gallons_required = 0;
    bool name_acquired = false;
    while(getline(file, line)){
        for(int i = 0; i < line.length(); i++){
            if(!name_acquired){
                if(line[i] == ','){
                    name_acquired = true;
                } else{
                    fish_name += line[i];
                }
            } else{
                gallons_required = line[i];
            }
        }
    }

    return true;
}

bool Aquarium::removeFish(string fish_name){
    for(int i = 0; i < _fish.size(); i++){
        cout << _fish.at(i).name << ", " << fish_name;
        if(_fish.at(i).name == fish_name){
            _fish.erase(_fish.begin()+i);
            return true;
        }
    }
    
    return false;
}

int main(){
    //create an aquarium object
    Aquarium marias_fish("maria");

    //load fish
    marias_fish.loadFish("fish_15.txt");

    //remove fish that has not been selected
    cout << marias_fish.removeFish("Butterfly Koi") << endl;

    // remove fish that has been selected
    cout << marias_fish.removeFish("Rose Petal Betta") << endl;

}