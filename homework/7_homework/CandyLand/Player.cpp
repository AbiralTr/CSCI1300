#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>

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
    if(players[0].getCandyAmount() == 0 || players[1].getCandyAmount() == 0){
        cout << "Not enough candy!" << endl;
    } else{
        Candy player1bet;
        Candy player2bet;
        bool running = true;
        // Player 1 and 2 Setting their bets
        string player1betname = "";
        string player2betname = "";
        cout << "Player 1 Inventory" << endl;
        players[0].printInventory();
        bool findingCandy = true;
        while(findingCandy){
            cout << "Player 1: Select candy to bet" << endl;
            getline(cin, player1betname);
            player1bet = players[0].findCandy(player1betname);
            if(player1bet.name == ""){
                cout << "Invalid selection!" << endl;
                bool loop = true;
                while(loop){
                    getline(cin, player2betname);
                    player2bet = players[1].findCandy(player2betname);
                    if(player2bet.name != ""){
                        findingCandy = false;
                        loop = false;
                    }
                }
            } else{
                findingCandy = false;
            }
        }

        cout << "Player 2 Inventory" << endl;
        players[1].printInventory();
        findingCandy = true;
        while(findingCandy){
            cout << "Player 2: Select candy to bet" << endl;
            getline(cin, player2betname);
            player2bet = players[1].findCandy(player2betname);
            if(player2bet.name == ""){
                cout << "Invalid selection!" << endl;
                bool loop = true;
                while(loop){
                    getline(cin, player2betname);
                    player2bet = players[1].findCandy(player2betname);
                    if(player2bet.name != ""){
                        findingCandy = false;
                        loop = false;
                    }
                }
            } else{
                findingCandy = false;
            }
        }
        // Game Starts
        char player1selection;
        char player2selection;
        while(running){
            bool selecting = true;
            while(selecting){
                cout << "Player 1: Enter r, p, or s" << endl;
                cin >> player1selection;
                if(player1selection == 'r' || player1selection == 'p' || player1selection == 's'){
                    selecting = false;
                } else{
                    cout << "Invalid selection!" << endl;
                    bool loop = true;
                    while(loop){
                        cin >> player1selection;
                        if(player1selection == 'r' || player1selection == 'p' || player1selection == 's'){
                            selecting = false;
                            loop = false;
                        }
                    }
                }
            }
            selecting = true;
            while(selecting){
                cout << "Player 2: Enter r, p, or s" << endl;
                cin >> player2selection;
                if(player2selection == 'r' || player2selection == 'p' || player2selection == 's'){
                    selecting = false;
                } else{
                    cout << "Invalid selection!" << endl;
                    bool loop = true;
                    while(loop){
                        cin >> player1selection;
                        if(player1selection == 'r' || player1selection == 'p' || player1selection == 's'){
                            selecting = false;
                            loop = false;
                        }
                    }
                }
            }

            if(player1selection != player2selection){
                running = false;
            } else{
                cout << "Tie! Play again" << endl;
            }
            
        }

        if(player1selection == 'r'){
            if(player2selection == 's'){
                cout << "Player 1 has won " << player2betname << " from player 2!" << endl;
                players[0].addCandy(player2bet);
                players[1].removeCandy(player2bet.name);
            } else if(player2selection == 'p'){
                cout << "Player 2 has won " << player1betname << " from player 1!" << endl;
                players[1].addCandy(player1bet);
                players[0].removeCandy(player1bet.name);
            }
        } else if(player1selection == 'p'){
            if(player2selection == 'r'){
                cout << "Player 1 has won " << player2betname << " from player 2!" << endl;
                players[0].addCandy(player2bet);
                players[1].removeCandy(player2bet.name);
            } else if(player2selection == 's'){
                cout << "Player 2 has won " << player1betname << " from player 1!" << endl;
                players[1].addCandy(player1bet);
                players[0].removeCandy(player1bet.name);
            }
        } else if(player1selection == 's'){
            if(player2selection == 'p'){
                cout << "Player 1 has won " << player2betname << " from player 2!" << endl;
                players[0].addCandy(player2bet);
                players[1].removeCandy(player2bet.name);
            } else if(player2selection == 'r'){
                cout << "Player 2 has won " << player1betname << " from player 1!" << endl;
                players[1].addCandy(player1bet);
                players[0].removeCandy(player1bet.name);
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