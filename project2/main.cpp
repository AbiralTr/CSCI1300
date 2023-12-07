#include "board.cpp"
#include "candy.cpp"
#include "player.cpp"
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

vector<Candy> loadCandies(string file_name, vector<Candy> candyVector){
    string name;
    string description;
    double price = 0.0;
    string type;
    vector<Candy> loadedVector;
    int value = 0;

    ifstream file(file_name);
    if(file.fail()){
        cout << "Failed to open file" << endl;
        return loadedVector;
    }
    
    string line;
    while(getline(file, line)){
        if(line.length() == 0){
            continue;
        }
        Candy current_candy = Candy();
        string stat;
        stringstream ss(line);
        vector<string> stats;
        while(getline(ss, stat, '|')){
            stats.push_back(stat);
        }

        current_candy.name = stats.at(0);
        current_candy.description = stats.at(1);
        current_candy.candy_type = stats.at(4);
        current_candy.value = stoi(stats.at(3));
        current_candy.price = stod(stats.at(5));
        
        loadedVector.push_back(current_candy);
    }
    return loadedVector;
}

vector<Player> loadCharacters(string file_name, vector<Player> playerVector){
    string name;
    int stamina = 0;
    double gold = 0.0;
    Candy candies[4];
    vector<Player> loadedVector;

    ifstream file(file_name);
    if(file.fail()){
        cout << "Failed to open file" << endl;
        return loadedVector;
    }
    string line;
    while(getline(file, line)){
        if(line.length() == 0){
            continue;
        }
        string word;
        stringstream ss(line);
        vector<string> stats;
        while(getline(ss, word, '|')){
            stats.push_back(word);
        }
        name = stats.at(0);
        stamina = stoi(stats.at(1));
        gold = stod(stats.at(2));
        string candyLine = stats.at(3);
        string candyName;
        int index = 0;
        string candyArr[4];
        for(int i = 0; i < candyLine.length(); i++){
            if(candyLine[i] == ',' || i == candyLine.length()){
                candyArr[index] = candyName;
                index++;
                candyName = "";
            } else{
                candyName += candyLine[i];
            }
        }
        for(int i = 0; i < index; i++){
            Candy current_candy{candyArr[i]};
            candies[i] = current_candy;
        }   
        Player current_player = Player(name, stamina, gold, "", candies, sizeof(candies));
        loadedVector.push_back(current_player);
    }
    return loadedVector;
}

void printCharacters(vector<Player> characters){
    for(int i = 0; i < characters.size(); i++){
        cout << "Name: " << characters.at(i).getName() << endl;
        cout << "Stamina: " << characters.at(i).getStamina() << endl;
        cout << "Gold: " << characters.at(i).getGold() << endl;
        cout << "Candies: " << endl;
        characters.at(i).printInventory();
        cout << "------------------------------" << endl;
    }
}

void printCandyStore(vector<Candy> candies){
    for(int i = 0; i < candies.size(); i++){
        cout << "Name: " << candies.at(i).name << endl;
        cout << "Description: " << candies.at(i).description << endl;
        cout << "Type: " << candies.at(i).candy_type << endl;
        cout << "Type Value: " << candies.at(i).value << endl;
        cout << "Price: " << candies.at(i).price << endl;
        cout << "------------------------------" << endl;
    }
}

int main(int argc, char *argv[]){
    vector<Candy> loaded_candies;
    vector<Player> loaded_characters;

    loaded_candies = loadCandies("files/candies.txt", loaded_candies);
    loaded_characters = loadCharacters("files/characters.txt", loaded_characters);
    vector<Player> selected_characters;
    
    int player_count = 0;

    cout << "Welcome to the game of candyland. Please enter the number of participants:" << endl;
    cin >> player_count;
    string players[player_count];
    for(int i = 0; i < player_count; i++){
        string input;
        bool pickedCharacter = false;
        cout << "Enter player name:" << endl;
        cin >> players[i];
        cout << "Awesome! Here is a list of characters a player can select from:" << endl;
        printCharacters(loaded_characters);
        cout << "The selected character is: " << endl;
        cin >> input;
        while(!pickedCharacter){
            for(int i = 0; i < loaded_characters.size(); i++){
                if(input == loaded_characters.at(i).getName()){
                    pickedCharacter = true;
                    selected_characters.push_back(loaded_characters.at(i));
                    loaded_characters.erase(loaded_characters.begin()+i);
                }
            }

            if(!pickedCharacter){
                cout << "Invalid Selection, please select a valid character:" << endl;
                cin >> input;
            }
        }
        
        cout << "Do you want to visit the candy store?(y/n)" << endl;
        bool valid = false;
        bool candySelected = false;
        while(!valid){
            cin >> input;
            if(input == "y"){
                printCandyStore(loaded_candies);
                cout << "Select a valid candy:" << endl;
                while(!candySelected){
                    input = "";
                    getline(cin, input);
                    for(int j = 0; j < loaded_candies.size(); j++){
                        if(loaded_candies.at(j).name == input){
                            if(selected_characters.at(i).getGold() >= loaded_candies.at(j).price){
                                cout << players[i] << " has purchased " << loaded_candies.at(j).name << endl;
                                selected_characters.at(i).setGold(selected_characters.at(i).getGold()-loaded_candies.at(j).price);
                                selected_characters.at(i).addCandy(loaded_candies.at(j));
                                candySelected = true;
                                valid = true;
                            } else {
                                cout << "You don't have enough gold!" << endl;
                            }
                            
                        }
                    }
                }
            } else if(input == "n"){
                valid = true;
            } else{
                cout << "Invalid Input, please enter a valid input:" << endl;
            }
        }
        
    }

    bool gameRunning = true;
    int turn = 0;
    int round = 1;

    bool atCandyStore = false;
    int atCandyStoreIndex = -1;

    Board board = Board();
    board.setPlayers(selected_characters);

    int rand1, rand2, rand3;
    srand(time(0));
    rand1 = (rand() % 30-5) + 10;
    rand2 = (rand() % 55-31) + 31;
    rand3 = (rand() % 75-56) + 56;
    cout << rand1 << ":" << rand2 << ":" << rand3 << endl;
    vector<Candy> candymart_candy;
    candymart_candy = loadCandies("files/candymartcandies.txt", candymart_candy);
    CandyStore candymart = CandyStore("Candy Mart", candymart_candy, 3, rand1);
    vector<Candy> sweetshop_candy;
    sweetshop_candy = loadCandies("files/sweetshopcandies.txt", sweetshop_candy);
    CandyStore sweetshop = CandyStore("Sweet Shop", sweetshop_candy, 3, rand2);
    vector<Candy> cavitycave_candy;
    cavitycave_candy = loadCandies("files/candymartcandies.txt", cavitycave_candy);
    CandyStore cavitycave = CandyStore("Cavity Cave", cavitycave_candy, 3, rand3);
    board.addCandyStore(candymart.getPosition(), candymart);
    board.addCandyStore(sweetshop.getPosition(), sweetshop);
    board.addCandyStore(cavitycave.getPosition(), cavitycave);
    while(gameRunning){
        string selection_input;
        int turn_input = 0;
        board.displayBoard();
        cout << "Round " << round << endl;
        cout << "Turn " << turn+1 << " (" << players[turn] << ")" << endl;
        cout << "It's " << players[turn] << " turn\nPlease select a menu option:" << endl;
        cout << "1 ) Draw Card\n2 ) Eat Candy\n3 ) View Stats" << endl;
        if(board.getPlayerPosition(turn) == rand1 || board.getPlayerPosition(turn) == rand2 || board.getPlayerPosition(turn) == rand3){
            atCandyStore = true;
            cout << "4 ) You have landed in front of a candy store, enter?" << endl;
            if(board.getPlayerPosition(turn) == board.getCandyStore(0).getPosition()){
                atCandyStoreIndex = 0;
            } else if(board.getPlayerPosition(turn) == board.getCandyStore(1).getPosition()){
                atCandyStoreIndex = 1;
            } else if(board.getPlayerPosition(turn) == board.getCandyStore(2).getPosition()){
                atCandyStoreIndex = 2;
            }
        }
        string candy_input = "";
        cin >> turn_input;
        switch(turn_input){
            case 1:
                board.drawCard(turn);
                turn++;
                break;
            case 2:
                cout << "Here is your Inventory of candies:" << endl;
                selected_characters.at(turn).printInventory();
                cout << "Which candy would you like to eat?" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, candy_input);
                if(selected_characters.at(turn).findCandy(candy_input).name == candy_input){ 
                    selected_characters.at(turn).eatCandy(candy_input);
                    selected_characters.at(turn).removeCandy(candy_input);
                    cout << players[turn] << " ate " << candy_input << endl; 
                    candy_input = "";
                    turn++;
                } else{
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "That candy does not exist!" << endl;
                }
                break;
            case 3:
                cout << "Player Name: " << players[turn] << endl;
                cout << "Character Name: " << selected_characters.at(turn).getName() << endl;
                cout << "Stamina: " << selected_characters.at(turn).getStamina() << endl;
                cout << "Gold: " << selected_characters.at(turn).getGold() << endl;
                cout << "Candies: " << endl;
                selected_characters.at(turn).printInventory();
                cout << "------------------------------" << endl;
                break;
            case 4: // Remove Later after testing
                if(atCandyStore){
                    printCandyStore(board.getCandyStore(atCandyStoreIndex).getCandyList());
                    cout << "What would you like to buy?" << endl;
                    getline(cin, candy_input);
                    for(int i = 0; i < 3; i++){
                        if(board.getCandyStore(atCandyStoreIndex).getCandyList().at(i).name == candy_input ){
                            if(board.getCandyStore(atCandyStoreIndex).getCandyList().at(i).price <= selected_characters.at(turn).getGold()){
                                if(selected_characters.at(turn).getCandyAmount() < 4){
                                    selected_characters.at(turn).setGold(selected_characters.at(turn).getGold() - board.getCandyStore(atCandyStoreIndex).getCandyList().at(i).price);
                                    turn++;
                                } else{
                                    cout << "You do not have sufficient room, would you like to swap one of your candies for this candy?" << endl;
                                    cin >> selection_input;
                                    if(selection_input == "y"){
                                        cout << "Choose one to swap out" << endl;
                                        getline(cin, candy_input); // Continue here 
                                    }
                                }
                            } else{
                                cout << "Insufficient funds." << endl;
                            }
                            
                        }
                    }
                    atCandyStore = false;
                    atCandyStoreIndex = -1;
                } else{
                    cout << "Invalid Input, please enter 1, 2, or 3." << endl;
                }
                break;
            default:
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input, please enter 1, 2, or 3." << endl;
                break;
        }
        if(turn == player_count){
            round += 1;
            turn = 0;
        }
    }
    return 0;
}