#include "Planet.cpp"

using namespace std;

int maxRadius(Planet planet_array[], const int PLANET_ARRAY_SIZE){
    if(PLANET_ARRAY_SIZE == 0){
        return -1;
    }
    double radi[PLANET_ARRAY_SIZE];

    for(int i = 0; i < PLANET_ARRAY_SIZE; i++){
        radi[i] = planet_array[i].getRadius();
    }

    int index = -1;
    double max = 0.0;
    for(int i = 0; i < PLANET_ARRAY_SIZE; i ++){
        if(radi[i] > max){
            max = radi[i];
            index = i;
        }
    }
    
    return index;
}

int main(){
    Planet Mars = Planet("Mars", 23390);
    Planet Earth = Planet("Earth",6378);
    Planet planets[2] = {Earth, Mars};
    cout << maxRadius(planets, 2) << endl;
}