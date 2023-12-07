#pragma once
#include <string>
#include "candy.h"
#include "board.h"

class Player{
    private:
        string _owner = "";
        string _name = "";
        const static int _MAX_CANDY_AMOUNT = 4;
        int	_stamina = 0;
        double _gold = 0;
        std::string _effect = "";
        Candy _inventory[_MAX_CANDY_AMOUNT];
        int	_candy_amount = 0;
        int _position = 0;
    public:
        Player();
        Player(string name, int stamina, double gold, std::string effect, Candy candy_array[], const int CANDY_ARRAY_SIZE);
        int getCandyAmount();
        void setStamina(int i);
        string getName();
        int getStamina();
        void setGold(double i);
        double getGold();
        void setEffect(std::string s);
        std::string getEffect();
        void printInventory();
        Candy findCandy(std::string candy_name);
        bool addCandy(Candy candy);
        bool removeCandy(std::string candy_name);  
        void setOwner(string name);
        string getOwner();
        void setName(string name);
        void setInventory(Candy array[], const int CANDY_ARRAY_SIZE);
        int getPosition();
        void setPosition(int pos);
        void eatCandy(string name);
};