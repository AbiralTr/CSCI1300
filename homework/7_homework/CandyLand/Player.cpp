#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

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
            if(candy_array[i].name != "Empty"){
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
        if(_inventory[i].name == lower(candy_name)){
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
        std::cout << "Not enough candy!" << endl;
    } else{
        Candy player1bet;
        Candy player2bet;
        bool running = true;
        // Player 1 and 2 Setting their bets
        string player1betname = "";
        string player2betname = "";
        std::cout << "Player 1 Inventory" << endl;
        players[0].printInventory();
        bool findingCandy = true;
        while(findingCandy){
            std::cout << "Player 1: Select candy to bet" << endl;
            getline(cin, player1betname);
            player1bet = players[0].findCandy(lower(player1betname));
            if(player1bet.name == ""){
                bool loop = true;
                while(loop){
                    std::cout << "Invalid selection!" << endl;
                    getline(cin, player1betname);
                    player1bet = players[0].findCandy(lower(player1betname));
                    if(player1bet.name != ""){
                        findingCandy = false;
                        loop = false;
                    }
                }
            } else{
                findingCandy = false;
            }
        }

        std::cout << "Player 2 Inventory" << endl;
        players[1].printInventory();
        findingCandy = true;
        while(findingCandy){
            std::cout << "Player 2: Select candy to bet" << endl;
            getline(cin, player2betname);
            player2bet = players[1].findCandy(lower(player2betname));
            if(player2bet.name == ""){
                bool loop = true;
                while(loop){
                    std::cout << "Invalid selection!" << endl;
                    getline(cin, player2betname);
                    player2bet = players[1].findCandy(lower(player2betname));
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
            selecting = true;
            while(selecting){
                std::cout << "Player 2: Enter r, p, or s" << endl;
                cin >> player2selection;
                if(player2selection == 'r' || player2selection == 'p' || player2selection == 's'){
                    selecting = false;
                } else{
                    bool loop = true;
                    while(loop){
                        std::cout << "Invalid selection!" << endl;
                        cin >> player2selection;
                        if(player2selection == 'r' || player2selection == 'p' || player2selection == 's'){
                            selecting = false;
                            loop = false;
                        }
                    }
                }
            }

            if(player1selection != player2selection){
                running = false;
            } else{
                std::cout << "Tie! Play again" << endl;
            }
            
        }

        if(player1selection == 'r'){
            if(player2selection == 's'){
                std::cout << "Player 1 has won " << player2betname << " from player 2!" << endl;
                players[0].addCandy(player2bet);
                players[1].removeCandy(player2bet.name);
            } else if(player2selection == 'p'){
                std::cout << "Player 2 has won " << player1betname << " from player 1!" << endl;
                players[1].addCandy(player1bet);
                players[0].removeCandy(player1bet.name);
            }
        } else if(player1selection == 'p'){
            if(player2selection == 'r'){
                std::cout << "Player 1 has won " << player2betname << " from player 2!" << endl;
                players[0].addCandy(player2bet);
                players[1].removeCandy(player2bet.name);
            } else if(player2selection == 's'){
                std::cout << "Player 2 has won " << player1betname << " from player 1!" << endl;
                players[1].addCandy(player1bet);
                players[0].removeCandy(player1bet.name);
            }
        } else if(player1selection == 's'){
            if(player2selection == 'p'){
                std::cout << "Player 1 has won " << player2betname << " from player 2!" << endl;
                players[0].addCandy(player2bet);
                players[1].removeCandy(player2bet.name);
            } else if(player2selection == 'r'){
                std::cout << "Player 2 has won " << player1betname << " from player 1!" << endl;
                players[1].addCandy(player1bet);
                players[0].removeCandy(player1bet.name);
            }
        }
    }
    
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

int main(){
    Player player1 = Player();
    Player player2 = Player();
    Player players[2] = {player1, player2};

    bool running = true;
    cout << "Select from the following options:" << endl;
    cout << "1. Load Candy" << endl;
    cout << "2. Display player stats" << endl;
    cout << "3. Edit player stats" << endl;
    cout << "4. play rock-paper-scissors" << endl;
    cout << "5. Exit" << endl;

    string input_string;
    int input = 0;
    vector<Candy> availableCandy;
    string file_name;
    bool loop = false;
    bool valid = false;

    while(running){
        
        cin >> input;
        switch(input){
            case 1:
                cout << "Enter file to read:" << endl;
                cin >> file_name;
                readCandy(file_name, availableCandy);
                cout << "Select from the following options:" << endl;
                cout << "1. Load Candy" << endl;
                cout << "2. Display player stats" << endl;
                cout << "3. Edit player stats" << endl;
                cout << "4. play rock-paper-scissors" << endl;
                cout << "5. Exit" << endl;
                break;
            case 2:
                cout << "Which player's stats do you want to display? Choose 1 or 2:" << endl;
                cin >> input; // Might break (using same input var)
                switch(input){
                    case 1:
                        cout << "Player 1 stats:" << endl;
                        cout << "Stamina: " << player1.getStamina() << endl;
                        cout << "Gold: " << fixed << setprecision(2) << player1.getGold() << endl;
                        cout << "Effect: " << player1.getEffect() << endl;
                        player1.printInventory();
                        break;
                    case 2:
                        cout << "Player 2 stats:" << endl;
                        cout << "Stamina: " << player2.getStamina() << endl;
                        cout << "Gold: " << fixed << setprecision(2) << player2.getGold() << endl;
                        cout << "Effect: " << player2.getEffect() << endl;
                        player2.printInventory();
                        break;
                    default:
                        cout << "Invalid input!" << endl;
                        break;
                }
                cout << "Select from the following options:" << endl;
                cout << "1. Load Candy" << endl;
                cout << "2. Display player stats" << endl;
                cout << "3. Edit player stats" << endl;
                cout << "4. play rock-paper-scissors" << endl;
                cout << "5. Exit" << endl;
                break;
            case 3:
                cout << "Which player's stats do you want to edit? Choose 1 or 2:" << endl;
                cin >> input; // Might break (using same input var)
                switch(input){
                    case 1: // Editting Player 1 Stats
                        cout << "Editing Player 1 stats:" << endl;
                        cout << "1. Edit Stamina" << endl;
                        cout << "2. Edit Gold" << endl;
                        cout << "3. Edit Effect" << endl;
                        cout << "4. Add Candy" << endl;
                        cout << "5. Remove Candy" << endl;
                        cin >> input;
                        switch(input){
                            case 1:
                                cout << "Editing stamina. Enter a value between 1 and 10:" << endl;
                                cin >> input;
                                if(input > 0 && input < 11){
                                    player1.setStamina(input);
                                } else{
                                    loop = true;
                                    while(loop){
                                        cout << "Invalid input!" << endl;
                                        cin >> input;
                                        if(input > 0 && input < 11){
                                            loop = false;
                                            player1.setStamina(input);
                                        }
                                    }
                                    
                                }
                                break;
                            case 2:
                                cout << "Editing gold. Enter a value between 0 and 1000:" << endl;
                                cin >> input;
                                if(input > 0 && input < 1000.1){
                                    player1.setGold(input);
                                } else{
                                    loop = true;
                                    while(loop){
                                        cout << "Invalid input!" << endl;
                                        cin >> input;
                                        if(input > -1 && input < 1000.1){
                                            loop = false;
                                            player1.setGold(input);
                                        }
                                    }
                                    
                                }
                                break;
                            case 3:
                                cout << "Editing Effect. Enter the name of an effect as a string" << endl;
                                cin >> input_string;
                                player1.setEffect(input_string);
                                break;
                            case 4:
                                if(availableCandy.size() != 0){
                                    cout << "Adding candy. Enter one of the following options:" << endl;
                                    displayCandyVector(availableCandy);
                                    getline(cin, input_string);
                                    for(int i = 0; i < availableCandy.size(); i++){
                                        if(valid){
                                            continue;
                                        } else{
                                            if(availableCandy.at(i).name == lower(input_string)){
                                                valid = true;
                                                player1.addCandy(availableCandy.at(i));
                                            }
                                        }
                                    }
                                } else{
                                    cout << "Cannot add candy! Read a candy file first" << endl;
                                }
                                break;
                            case 5:
                                cout << "Removing Candy. Enter the name of a candy in player 1's inventory:" << endl;
                                player1.printInventory();
                                getline(cin, input_string);
                                if(!player1.removeCandy(input_string)){
                                    loop = true;
                                    while(loop){
                                        cout << "Invalid input!" << endl;
                                        getline(cin, input_string);
                                        if(player1.removeCandy(input_string)){
                                            loop = false;
                                        }
                                    }
                                }
                                break;
                            default:
                                cout << "Invalid input!" << endl;
                                break;
                        }
                        break;
                    case 2: // Editting Player 2 Stats
                        cout << "Editing Player 2 stats:" << endl;
                        cout << "1. Edit Stamina" << endl;
                        cout << "2. Edit Gold" << endl;
                        cout << "3. Edit Effect" << endl;
                        cout << "4. Add Candy" << endl;
                        cout << "5. Remove Candy" << endl;
                        cin >> input;
                        switch(input){
                            case 1:
                                cout << "Editing stamina. Enter a value between 1 and 10:" << endl;
                                cin >> input;
                                if(input > 0 && input < 11){
                                    player2.setStamina(input);
                                } else{
                                    loop = true;
                                    while(loop){
                                        cout << "Invalid input!" << endl;
                                        cin >> input;
                                        if(input > 0 && input < 11){
                                            loop = false;
                                            player2.setStamina(input);
                                        }
                                    }
                                    
                                }
                                break;
                            case 2:
                                cout << "Editing gold. Enter a value between 0 and 1000:" << endl;
                                cin >> input;
                                if(input > 0 && input < 1000.1){
                                    player2.setGold(input);
                                } else{
                                    loop = true;
                                    while(loop){
                                        cout << "Invalid input!" << endl;
                                        cin >> input;
                                        if(input > -1 && input < 1000.1){
                                            loop = false;
                                            player2.setGold(input);
                                        }
                                    }
                                    
                                }
                                break;
                            case 3:
                                cout << "Editing Effect. Enter the name of an effect as a string" << endl;
                                cin >> input_string;
                                player2.setEffect(input_string);
                                break;
                            case 4:
                                if(availableCandy.size() != 0){
                                    cout << "Adding candy. Enter one of the following options:" << endl;
                                    displayCandyVector(availableCandy);
                                    getline(cin, input_string);
                                    for(int i = 0; i < availableCandy.size(); i++){
                                        if(valid){
                                            continue;
                                        } else{
                                            if(availableCandy.at(i).name == lower(input_string)){
                                                valid = true;
                                                player2.addCandy(availableCandy.at(i));
                                            }
                                        }
                                    }
                                } else{
                                    cout << "Cannot add candy! Read a candy file first" << endl;
                                }
                                break;
                            case 5:
                                cout << "Removing Candy. Enter the name of a candy in player 2's inventory:" << endl;
                                player2.printInventory();
                                getline(cin, input_string);
                                if(!player2.removeCandy(input_string)){
                                    loop = true;
                                    while(loop){
                                        cout << "Invalid input!" << endl;
                                        getline(cin, input_string);
                                        if(player2.removeCandy(input_string)){
                                            loop = false;
                                        }
                                    }
                                }
                                break;
                            default:
                                cout << "Invalid input!" << endl;
                                break;
                        }
                        break;
                    default:
                        cout << "Invalid input!" << endl;
                        break;
                    valid = false;
                    cout << "Select from the following options:" << endl;
                    cout << "1. Load Candy" << endl;
                    cout << "2. Display player stats" << endl;
                    cout << "3. Edit player stats" << endl;
                    cout << "4. play rock-paper-scissors" << endl;
                    cout << "5. Exit" << endl;
                }
                cout << "Select from the following options:" << endl;
                cout << "1. Load Candy" << endl;
                cout << "2. Display player stats" << endl;
                cout << "3. Edit player stats" << endl;
                cout << "4. play rock-paper-scissors" << endl;
                cout << "5. Exit" << endl;
                input = 0;
                break;
            case 4:
                break;
            case 5:
                running = false;
                break;
            default:
                cout << "Invalid input!" << endl;
                cout << "Select from the following options:" << endl;
                cout << "1. Load Candy" << endl;
                cout << "2. Display player stats" << endl;
                cout << "3. Edit player stats" << endl;
                cout << "4. play rock-paper-scissors" << endl;
                cout << "5. Exit" << endl;
                break;
        }
    }

}