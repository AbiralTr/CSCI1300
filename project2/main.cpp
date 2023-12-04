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
    int value = 0;

    ifstream file(file_name);
    if(file.fail()){
        cout << "Failed to open file" << endl;
        return candyVector;
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
        current_candy.candy_type = stats.at(2);
        current_candy.value = stoi(stats.at(3));
        current_candy.price = stod(stats.at(3));
        
        candyVector.push_back(current_candy);
    }
    return candyVector;
}

vector<Player> loadCharacters(string file_name, vector<Player> playerVector){
    string name;
    int stamina = 0;
    double gold = 0.0;
    Candy candies[] = {};

    ifstream file(file_name);
    if(file.fail()){
        cout << "Failed to open file" << endl;
        return playerVector;
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
        ss.clear();
        ss.str("");
        ss.str(candyLine);
        int index = 0;
        while(getline(ss, candyName, ',')){
            Candy current_candy{candyName};
            candies[index] = current_candy;
            index++;
        }
        
        Player current_player = Player(name, stamina, gold ,"", candies, 4);
        playerVector.push_back(current_player);
    }

    return playerVector;
}

int main(int argc, char *argv[]){
    vector<Candy> loaded_candies;
    vector<Player> loaded_characters;

    loaded_candies = loadCandies("files/candies.txt", loaded_candies);
    loaded_characters = loadCharacters("files/characters.txt", loaded_characters);

    std::cout << "hi" << std::endl;

    string players[] = {}; 
    int player_count = 0;

    cout << "Welcome to the game of candyland. Please enter the number of participants:" << endl;
    cin >> player_count;
    for(int i = 0; i < player_count; i++){
        cout << "Enter player name:" << endl;
        cin >> players[i];
        cout << "Awesome! Here is a list of characters a player can select from:" << endl;
        for(int i = 0; i < loaded_characters.size(); i++){
            cout << loaded_characters.at(i).getName() << endl;
        }
    }


    return 0;
}