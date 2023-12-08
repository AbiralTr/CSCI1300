#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

Player::Player(){
    _inventory[_MAX_CANDY_AMOUNT];
}

Player::Player(string name, int stamina, double gold, std::string effect, Candy candy_array[], const int CANDY_ARRAY_SIZE){
    _name = name;
    _stamina = stamina;
    _gold = gold;
    _candy_amount = 0;
    _effect = effect;
    _inventory[_MAX_CANDY_AMOUNT];
    if(CANDY_ARRAY_SIZE > _MAX_CANDY_AMOUNT){
        _candy_amount = _MAX_CANDY_AMOUNT;
        for(int i = 0; i < _MAX_CANDY_AMOUNT; i++){
            _inventory[i] = candy_array[i];
        }
    } else{
        for(int i = 0; i < CANDY_ARRAY_SIZE; i++){
            if(candy_array[i].name != "Empty"){
                _candy_amount++;
            }
            _inventory[i] = candy_array[i];
        }
    }
}

void Player::setExtraTurn(bool b){
    if(b){
        _extra_turn = true;
    } else{
        _extra_turn = false;
    }
}

void Player::setLostTurn(bool b){
    if(b){
        _lost_turn = true;
    } else{
        _lost_turn = false;
    }
}

string lower(string s){
    string lowered_string = s;
    for(int i = 0; i < s.length(); i++){
        lowered_string[i] = tolower(lowered_string[i]);
    }
    return lowered_string;
}


Candy Player::findCandy(std::string candy_name){
    Candy foundCandy{""};
    bool found = false;
    for(int i = 0; i < 4; i ++){
        if(!found){
            if(lower(_inventory[i].name) == lower(candy_name)){
                found = true;
                foundCandy = _inventory[i];
            }
        }
    }

    return foundCandy;
}

int Player::eatCandy(string name){
    int index = 0;
    int value = 0;
    bool found = false;
    for(int i = 0; i < 4; i ++){
        if(_inventory[i].name == name){
            index = i;
            found = true;
        }
    }
    if(found){
        if(_inventory[index].effect_type == "stamina"){
            if(_inventory[index].candy_type == "poison"){
                value = _inventory[index].value;
                cout << "This candy deals " << -_inventory[index].value << " stamina damage" << endl;
            } else{
                _stamina += _inventory[index].value;
                value = _inventory[index].value;
                cout << "You gained " << _inventory[index].value << " stamina" << endl;
            }
        } else{
            cout << "You have gained the effect " << _inventory[index].description << endl;
            _effect = _inventory[index].description;
        }
        removeCandy(name);
    }

    return value;
}

Candy Player::getCandy(int i){
    return _inventory[i];
}

bool Player::getExtraTurn(){
    return _extra_turn;
}

void Player::giveCandy(Player p, Candy c){
    p.eatCandy(c.name);
}

bool Player::getLostTurn(){
    return _lost_turn;
}

bool Player::addCandy(Candy candy){
    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++){
        if(_inventory[i].name == "Empty" && _inventory[i].price == 0){
            _inventory[i] = candy;
            _candy_amount++;
            return true;
        }
    }
    return false;
}

bool Player::removeCandy(std::string candy_name){
    for(int i = 3; i > -1; i=i-1){
        if(lower(_inventory[i].name) == lower(candy_name)){
            Candy emptyCandy{"Empty", "", 0};
            _inventory[i] = emptyCandy;     
            _candy_amount = _candy_amount - 1;

            Candy tempArray[4];
            int index = 0;
            for(int j = 0; j < 4; j++){
                if(_inventory[j].name != "Empty"){
                    tempArray[index] = _inventory[j];
                    index++;
                }
            }
            
            for(int k = 0; k < 4; k++){
                _inventory[k] = tempArray[k];
            }

            return true;
        }
    }
    return false;
}

void Player::setInventory(Candy array[], const int CANDY_ARRAY_SIZE){
    if(CANDY_ARRAY_SIZE > _MAX_CANDY_AMOUNT){
        _candy_amount = _MAX_CANDY_AMOUNT;
        for(int i = 0; i < _MAX_CANDY_AMOUNT; i++){
            _inventory[i] = array[i];
        }
    } else{
        for(int i = 0; i < CANDY_ARRAY_SIZE; i++){
            if(array[i].name != "Empty"){
                _candy_amount++;
            }
            _inventory[i] = array[i];
        }
    }
}

void Player::setOwner(string name){
    _owner = name;
}

string Player::getOwner(){
    return _owner;
}

string Player::getName(){
    return _name;
}

int Player::getCandyAmount(){
    return _candy_amount;
}

void Player::setStamina(int i)
{
    _stamina = i;
}

void Player::setName(string name){
    _name = name;
}

int Player::getStamina(){
    return _stamina;
}

void Player::setGold(double i){
    _gold = i;
}

double Player::getGold(){
    return _gold;
}

void Player::setEffect(std::string s){
    _effect = s;
}

std::string Player::getEffect(){
    return _effect;
}

void Player::printInventory(){
    std::cout << "|[" << _inventory[0].name << "]|[" << _inventory[1].name << "]|" << std::endl;
    std::cout << "|[" << _inventory[2].name << "]|[" << _inventory[3].name << "]|" << std::endl; 
}

bool playRockPaperScissors(Player player){
    srand(time(0));
    int computerRand = (rand()%3);
    char player1selection;
    char computerSelection;
    if(computerRand == 0){
        computerSelection = 'r';
    } else if(computerRand == 1){
        computerSelection = 'p';
    } else if(computerRand == 2){
        computerSelection = 's';
    }
    
    bool running = true;
    while(running){
        bool selecting = true;
        while(selecting){
            std::cout << "Player 1: Enter r, p, or s" << endl;
            cin >> player1selection;
            if(player1selection == 'r' || player1selection == 'p' || player1selection == 's'){
                selecting = false;
            } else{
                bool loop = true;
                while(loop){
                    std::cout << "Invalid selection!" << endl;
                    cin >> player1selection;
                    if(player1selection == 'r' || player1selection == 'p' || player1selection == 's'){
                        selecting = false;
                        loop = false;
                    }
                }
            }
        }

        if(player1selection != computerSelection){
            running = false;
        } else{
            std::cout << "Tie! Play again" << endl;
        }
        
    }

    if(player1selection == 'r'){
        if(computerSelection == 's'){
            std::cout << "Player has won" << endl;
            return true;
        } else if(computerSelection == 'p'){
            std::cout << "Computer has won" << endl;
            return false;
        }
    } else if(player1selection == 'p'){
        if(computerSelection == 'r'){
            std::cout << "Player has won" << endl;
            return true;
        } else if(computerSelection == 's'){
            std::cout << "Computer has won" << endl;
            return false;
        }
    } else if(player1selection == 's'){
        if(computerSelection == 'p'){
            std::cout << "Player has won" << endl;
            return true;
        } else if(computerSelection == 'r'){
            std::cout << "Computer has won" << endl;
            return false;
        }
    }

    return false;
}

vector<Candy> readCandy(string file_name, vector<Candy> candies){
    string name;
    string description;
    double price = 0.0;
    string type;

    ifstream file(file_name);
    if(file.fail()){
        cout << "Failed to open file" << endl;
        return candies;
    }
    
    string line;
    while(getline(file, line)){
        if(line.length() == 0){
            continue;
        }
        Candy current_candy = Candy();
        string word;
        stringstream ss(line);
        vector<string> stats;
        while(getline(ss, word, '|')){
            stats.push_back(word);
        }

        current_candy.name = stats.at(0);
        current_candy.description = stats.at(1);
        current_candy.price = stod(stats.at(2));
        current_candy.candy_type = stats.at(3);
        
        candies.push_back(current_candy);
    }

    return candies;
}

void displayCandyVector(vector<Candy> candies){
    for(int i = 0; i < candies.size(); i++){
        cout << "Name: " << candies.at(i).name << ". Description: " << candies.at(i).description << ". Price: " << fixed << setprecision(2) << candies.at(i).price << ". " << "Type: " << candies.at(i).candy_type << endl;
    }
}

void Player::setPosition(int pos){
    _position = pos;
}

int Player::getPosition(){
    return _position;
}



