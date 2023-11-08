#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Aquarium.h"

using namespace std;

Aquarium::Aquarium(){
    _aquarist_name = "";
    _gallons_used = 0;
    _tank_size_gallons = 12;
}

Aquarium::Aquarium(string name){
    _aquarist_name = name;
    _gallons_used = 0;
    _tank_size_gallons = 12;
}

Aquarium::Aquarium(string name, int tanksize){
    _aquarist_name = name;
    _gallons_used = 0;
    _tank_size_gallons = tanksize;

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

vector<Fish> Aquarium::getSelectedFish()
{
    return _selected_fish;
}

void Aquarium::displayFish(){
    int len = _selected_fish.size();
    for (int i = 0; i < len; i++)
    {
        // Fill the below line to cout the name and the gallons_required of the current fish.
        cout << _selected_fish.at(i).name << " " << _selected_fish.at(i).gallons_required << endl;
    }
}

bool Aquarium::loadFish(string filename)
{
    ifstream reader(filename);
    string line = "";
    if (reader.is_open())
    {
        while (getline(reader, line))
        {
            string fish_name, gal_req;
            stringstream ss(line);
            Fish current_fish;
            int gals = 0;
            getline(ss, fish_name, ',');
            while(getline(ss, gal_req)){
                gals = stoi(gal_req);
            }
            current_fish.name = fish_name;
            current_fish.gallons_required = gals;
            _available_fish.push_back(current_fish);
        }
        return true;
    }
    return false;
}

vector<Fish> Aquarium::getAvailableFish(){
    return _available_fish;
}

bool Aquarium::removeFish(string fish_name){
    for(int i = 0; i < _selected_fish.size(); i++){
        if(_selected_fish.at(i).name == fish_name){
            _selected_fish.erase(_selected_fish.begin()+i);
            return true;
        }
    }
    
    return false;
}

int Aquarium::getTankSizeGallons(){
    return _tank_size_gallons;
}

void Aquarium::setTankSizeGallons(int i){
    _tank_size_gallons = i;
}

int Aquarium::addFish(string fish_name){
    int size = _available_fish.size();
    bool isAvailable = true;
    int index = 0;
    for(int i = 0; i < size; i++){
        if(_available_fish.at(i).name == fish_name){
            isAvailable = false;
            index = i;
        }
    }

    if(isAvailable && _available_fish.at(index).gallons_required < (_tank_size_gallons - _gallons_used)){
        return 1;
    } else if(isAvailable){
        return 0;
    } else{
        return -1;
    }
}