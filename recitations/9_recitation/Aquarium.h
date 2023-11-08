#pragma once

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Fish{

    string name;
    int gallons_required;

};

class Aquarium{
    private:
        string _aquarist_name;
        int _gallons_used;
        vector<Fish> _fish;
        vector<Fish> _available_fish;
        vector<Fish> _selected_fish;
        int _tank_size_gallons;
    public:
        Aquarium();
        Aquarium(string name);
        Aquarium(string name, int tanksize);

        void displayFish();
        void setAquaristName(string s);
        string getAquaristName();
        void setGallonsUsed(int i);
        int getGallonsUsed();
        vector<Fish> getSelectedFish();
;        bool loadFish(string file_name);
        bool removeFish(string fish_name);
        int getTankSizeGallons();
        void setTankSizeGallons(int i);
        int addFish(string fish_name);
        
};