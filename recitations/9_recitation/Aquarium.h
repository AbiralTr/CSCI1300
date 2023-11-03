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
    public:
        Aquarium();
        Aquarium(string name);

        void setAquaristName(string s);
        string getAquaristName();
        void setGallonsUsed(int i);
        int getGallonsUsed();
        bool loadFish(string file_name);
        bool removeFish(string fish_name);
};