#include <iostream>

struct Dog{
    std::string name;
    int age;
    std::string favorite_toy;
};

void printDog(Dog dog){
    std::cout << "Name: " << dog.name << ". Age: " << dog.age << ". Favorite Toy: " << dog.favorite_toy << "." << std::endl;
}

int main(){
    Dog spot = {"spot", 5, "tennis ball"};
    Dog lassie = {"lassie", 3 ,"frisbee"};

    printDog(spot);
    printDog(lassie);
    return 0;
}