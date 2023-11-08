#pragma once
#include <math.h>

using namespace std;

class Planet{
    private:
        string _planet_name;
        double _planet_radius = 0.0;
    public:
        Planet(){};
        Planet(string name, double radius);
        string getName();
        void setName(string name);
        double getRadius();
        void setRadius(double radius);
        double getVolume();

};