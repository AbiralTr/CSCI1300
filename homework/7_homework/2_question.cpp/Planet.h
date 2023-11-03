#pragma once
#include <math.h>

class Planet{
    private:
        std::string _planet_name;
        double _planet_radius = 0.0;
    public:
        Planet(){};
        Planet(std::string name, double radius){
            _planet_name = name;
            _planet_radius = radius;
        };

        std::string getName(){
            return _planet_name;
        }

        void setName(std::string name){
            _planet_name = name;
        }

        double getRadius(){
            return _planet_radius;
        }

        void setRadius(double radius){
            _planet_radius = radius;
        }


};