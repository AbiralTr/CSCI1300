#include "board.cpp"
#include "candy.cpp"
#include "player.cpp"
#include <iostream>
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
                    for(int i = 0; i < loaded_candies.size(); i++){
                        if(loaded_candies.at(i).name == input){
                            candySelected = true;
                            valid = true;
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
    Board board = Board();
    board.setPlayers(selected_characters);
    while(gameRunning){
        int turn_input = 0;
        board.displayBoard();
        cout << "Round " << round << endl;
        cout << "Turn " << turn+1 << " (" << players[turn] << ")" << endl;
        cout << "It's " << players[turn] << " turn\nPlease select a menu option:" << endl;
        cout << "1 ) Draw Card\n2 ) Eat Candy\n3 ) View Stats" << endl;
        cin >> turn_input;
        switch(turn_input){
            case 1:
                board.drawCard(players[turn]);
                turn++;
                break;
            case 2:
                cout << "Here is your Inventory of candies: " << endl;
                board.getPlayer(turn).printInventory();
                turn++;
                break;
            case 3:
                cout << "Player Name: " << players[turn] << endl;
                cout << "Character Name: " << selected_characters.at(turn).getName() << endl;
                cout << "Stamina: " << selected_characters.at(turn).getStamina() << endl;
                cout << "Gold: " << selected_characters.at(turn).getGold() << endl;
                cout << "Candies: " << endl;
                selected_characters.at(turn).printInventory();
                cout << "------------------------------" << endl;
            default:    
                break;
        }
        if(turn == player_count){
            round += 1;
            turn = 0;
        }
    }

    return 0;
}