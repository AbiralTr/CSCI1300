#include <iostream>
#include "Planet.h"

using namespace std;

const double pi = 3.14159265358979323846;

Planet::Planet(std::string name, double radius){
    _planet_name = name;
    _planet_radius = radius;
}
string Planet::getName(){
    return _planet_name;
}
void Planet::setName(string n){
    _planet_name = n;
}
double Planet::getRadius(){
    return _planet_radius;
}
void Planet::setRadius(double radius){
    _planet_radius = radius;
}
double Planet::getVolume(){
    return (4*pi*_planet_radius*_planet_radius*_planet_radius)/3;
};
