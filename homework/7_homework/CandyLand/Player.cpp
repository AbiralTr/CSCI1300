#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(){

}

Player::Player(int stamina, double gold, std::string effect, Candy candy_array[], const int CANDY_ARRAY_SIZE){
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
            if(candy_array[i].name != "Empty" && candy_array[i].price != 0){
                _candy_amount++;
            }
            _inventory[i] = candy_array[i];
        }
    }
}

void Player::printInventory(){
    std::cout << "|[" << _inventory[0].name << "]|[" << _inventory[1].name << "]|" << std::endl;
    std::cout << "|[" << _inventory[2].name << "]|[" << _inventory[3].name << "]|" << std::endl; 
}

Candy Player::findCandy(std::string candy_name){
    Candy foundCandy{""};
    bool found = false;
    for(int i = 0; i < 4; i ++){
        if(!found){
            if(_inventory[i].name == candy_name){
                found = true;
                foundCandy = _inventory[i];
            }
        }
    }

    return foundCandy;
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
    for(int i = 4; i > -1; i=i-1){
        if(_inventory[i].name == candy_name){
            Candy emptyCandy{"Empty", "", 0};
            _inventory[i] = emptyCandy;
            _candy_amount = _candy_amount - 1;
            return true;
        }
    }

    return false;
}

int Player::getCandyAmount(){
    return _candy_amount;
}

void Player::setStamina(int i)
{
    _stamina = i;
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

void playRockPaperScissors(Player players[2]){
    Candy player1bet;
    Candy player2bet;
    bool running = true;
    while(running){
        string bet = "";
        cout << "Player 1 Inventory" << endl;
        players[0].printInventory();
        bool findingCandy = true;
        while(findingCandy){
            cout << "Player 1: Select candy to bet" << endl;
            getline(cin, bet);
            player1bet = players[0].findCandy(bet);
            if(player1bet.name == ""){
                cout << "Invalid selection!" << endl;
            } else{
                findingCandy = false;
            }
        }

        bet = "";
        cout << "Player 2 Inventory" << endl;
        players[1].printInventory();
        findingCandy = true;
        while(findingCandy){
            cout << "Player 2: Select candy to bet" << endl;
            getline(cin, bet);
            player2bet = players[1].findCandy(bet);
            if(player2bet.name == ""){
                cout << "Invalid selection!" << endl;
            } else{
                findingCandy = false;
            }
        }
        
    }
}

int main(){
    Candy brown{"brown candy"};
    Candy striped{"striped candy"};
    Candy player1array[3] = {brown, striped, striped};
    Candy player2array[3] = {brown, striped, striped};
    Player player1 = Player(10, 100, "ballsy", player1array, 3);
    Player player2 = Player(15, 200, "oh lawd", player2array, 3);
    Player players[2] = {player1,player2};
    playRockPaperScissors(players);
}