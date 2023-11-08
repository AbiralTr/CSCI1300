#pragma once

#include <string>


class Planet{
    private:
        std::string _planet_name;
        double _planet_radius = 0.0;
    public:
        Planet(){};
        Planet(std::string name, double radius);
        std::string getName();
        void setName(std::string name);
        double getRadius();
        void setRadius(double radius);
        double getVolume();

};