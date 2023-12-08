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
        current_candy.effect_type = stats.at(2);
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
    vector<Candy> loadedCharacterCandies;
    loadedCharacterCandies = loadCandies("files/candies.txt", loadedCharacterCandies);

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
            if(candyLine[i] == ','){
                candyArr[index] = candyName;
                index++;
                candyName = "";
            } else{
                candyName += candyLine[i];
            }
        }

        for(int i = 0; i < index; i++){
            Candy current_candy{candyArr[i]};
            for(int i = 0; i < loadedCharacterCandies.size(); i++){
                if(current_candy.name == loadedCharacterCandies.at(i).name){
                    current_candy = loadedCharacterCandies.at(i);
                }
            }
            candies[i] = current_candy;
        }   
        Player current_player = Player(name, stamina, gold, "", candies, sizeof(candies));
        loadedVector.push_back(current_player);
    }
    return loadedVector;
}

vector<hiddenTreasure> loadHiddenTreasures(string file_name, vector<hiddenTreasure> treasureVector){
    string answer;
    string riddle;
    vector<hiddenTreasure> loadedVector;

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
        riddle = stats.at(0);
        answer = stats.at(1);
 
        hiddenTreasure current_treasure = hiddenTreasure(riddle, answer);
        
        srand(time(0));
        int type_rand = (rand()%4);
        current_treasure.setType(type_rand);
        loadedVector.push_back(current_treasure);

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

void printCandyStore(vector<Candy> candies, int range){
    for(int i = 0; i < range; i++){
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
    while(player_count < 2 || player_count > 4){
        cout << "At least 2 players required, at most 4" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> player_count;
    }
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
                printCandyStore(loaded_candies, 4);
                cout << "Select a valid candy:" << endl;
                while(!candySelected){
                    input = "";
                    getline(cin, input);
                    for(int j = 0; j < 4; j++){
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
    int tiles_moved = 0;

    bool atCandyStore = false;
    int atCandyStoreIndex = -1;

    Board board = Board();
    board.setPlayers(selected_characters);

    int rand1, rand2, rand3;
    srand(time(0));
    rand1 = (rand() % 27) + 1;
    rand2 = (rand() % 54) + 28;
    rand3 = (rand() % 82) + 55;
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

    int hiddenPos1 = (rand() % 27);
    int hiddenPos2 = (rand() % 54) + 28;
    int hiddenPos3 = (rand() % 82) + 55;
    int hiddenPosArr[] = {hiddenPos1, hiddenPos2, hiddenPos3};
    vector<hiddenTreasure> loaded_treasures;
    loaded_treasures = loadHiddenTreasures("files/riddles.txt", loaded_treasures);
    for(int i = 0; i < loaded_treasures.size(); i++){
        loaded_treasures.at(i).setPos(hiddenPosArr[i]);
        board.addTreasure(loaded_treasures.at(i).getPos(),loaded_treasures.at(i));
    }
    

    while(gameRunning){
        string selection_input;
        int turn_input = 0;
        bool foundCandy = false;
        int calamityChance = 0;
        int calamityRand = 0;

        bool onSameTile = false;
        int firstPlayerIndex = 0;
        int secondPlayerIndex = 0;

        board.displayBoard();
        if(selected_characters.at(turn).getLostTurn()){
            cout << "Unfortunately, " << players[turn] << " lost this turn from last round." << endl;
            selected_characters.at(turn).setLostTurn(false);
            turn++;
            if(turn == player_count){
                round += 1;
                turn = 0;
                atCandyStore = false;
            }
            continue;
        }
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
        Card pulled_card;
        switch(turn_input){
            case 1:
                if(selected_characters.at(turn).getStamina() < 5){
                    cout << players[turn] << " does not have the minimum amount of stamina (5) required to move!" << endl;
                    selected_characters.at(turn).setStamina(selected_characters.at(turn).getStamina() + 3);
                    turn++;
                } else{
                    pulled_card = board.drawCard(turn);
                    tiles_moved = pulled_card.tiles_moved;
                    selected_characters.at(turn).setStamina(selected_characters.at(turn).getStamina()-5);
                    cout << "You pulled a " << pulled_card.name << " card!";
                    if(pulled_card.isDouble){
                        if(pulled_card.color == "purple"){
                            cout << " You advance to the second purple tile." << endl;
                        } else if(pulled_card.color == "green"){
                            cout << " You advance to the second green tile." << endl;
                        } else if(pulled_card.color == "blue"){
                            cout << " You advance to the second blue card." << endl;
                        }
                    } else{
                        if(pulled_card.color == "purple"){
                            cout << " You advance to the next purple tile." << endl;
                        } else if(pulled_card.color == "green"){
                            cout << " You advance to the next green tile." << endl;
                        } else if(pulled_card.color == "blue"){
                            cout << " You advance to the next blue card." << endl;
                        }
                    }
                    if(board.getTile(board.getPlayerPosition(turn)).isSpecial){
                        Tile current_tile = board.getTile(board.getPlayerPosition(turn));
                        cout << "You landed on a " << current_tile.tile_type << endl;
                        if(current_tile.tile_type == "Shortcut"){
                            cout << "You moved forward 4 tiles!" << endl;
                            board.movePlayer(4, turn);
                        } else if(current_tile.tile_type == "Ice Cream"){
                            cout << "You get an extra turn!" << endl;
                            selected_characters.at(turn).setExtraTurn(true);
                        } else if(current_tile.tile_type == "Gumdrop Forest"){
                            cout << "You were pushed back by the beauty of the Gumdrop Forest..." << endl;
                            board.movePlayer(-1*4, turn);
                            int goldLost = (rand() % 10) + 5;
                            selected_characters.at(turn).setGold(selected_characters.at(turn).getGold() - goldLost);
                            if(selected_characters.at(turn).getGold() < 0){
                                selected_characters.at(turn).setGold(0);
                            }
                        } else if(current_tile.tile_type == "Gingerbread House"){
                            cout << "You were transported back to your previous position " << tiles_moved << " tiles back" << endl; 
                            board.movePlayer(-1*tiles_moved, turn);
                            for(int i = 0; i < 4; i++){
                                if(!foundCandy){
                                    if(selected_characters.at(turn).getCandy(i).candy_type == "immunity"){
                                        selected_characters.at(turn).removeCandy(selected_characters.at(turn).getCandy(i).name);
                                        cout << "Also, you lost one of your immunity candies..." << endl;
                                        foundCandy = true;
                                    }
                                }
                            }
                        }
                    } else{
                        calamityChance = (rand()%10);
                        if(calamityChance < 4){
                            cout << "You have triggered a Calamity!" << endl;
                            calamityRand = (rand()%100);
                            if(calamityRand <= 30){
                                int goldLost = (rand()%10)+5;
                                cout << "Candy Bandit Calamity: Oh no! You have been robbed of " << goldLost  << " gold!"<< endl;
                                selected_characters.at(turn).setGold(selected_characters.at(turn).getGold()-goldLost);
                                if(selected_characters.at(turn).getGold() < 0){
                                    selected_characters.at(turn).setGold(0);
                                }
                            } else if(calamityRand > 30 && calamityRand <= 65){
                                cout << "Lollipop Labyrinth Calamity: Oh dear! You got lost in the lollipop labyrinth! But you can recover the damage by playing Rock, Paper, Scissors See Rock Paper Scissors. If you win, you get the lost turn back." << endl;
                                if(playRockPaperScissors(selected_characters.at(turn))){
                                    cout << "You were able to escape and got your turn next back" << endl;
                                } else{
                                    cout << "You were not able to escape and lost your next turn" << endl;
                                    selected_characters.at(turn).setLostTurn(true);
                                }
                            } else if(calamityRand > 65 && calamityRand <= 80){
                                cout << "Candy Avalanche Calamity: Watch out! A candy avalanche has struck! But you can recover the damage by playing Rock, Paper, Scissors See Rock Paper Scissors. If you win, you get the lost resources back." << endl;
                                if(playRockPaperScissors(selected_characters.at(turn))){
                                    cout << "You were able to escape and got your stamina back" << endl;
                                } else{
                                    int staminaLost = (rand()%10)+5;
                                    cout << "You were not able to escape and lost " << staminaLost << " stamina!" << endl;
                                    selected_characters.at(turn).setStamina(selected_characters.at(turn).getStamina()-staminaLost);
                                    if(selected_characters.at(turn).getStamina() == 0){
                                        selected_characters.at(turn).setStamina(0);
                                    }
                                }
                            } else if(calamityRand > 80){
                                cout << "Sticky Taffy Calamity: Oops! You are stuck in a sticky taffy trap!" << endl;
                                bool stuck = true;
                                for(int i = 0; i < 3; i++){
                                    if(selected_characters.at(turn).getCandy(i).candy_type == "magical" || stuck){
                                        cout << "However, you can use your " << selected_characters.at(turn).getCandy(i).name << " to get out of it and recover your turn, would you like to use it?(y/n)" << endl;
                                        string confirm_input;
                                        cin >> confirm_input;
                                        if(confirm_input == "y"){
                                            cout << "You used one of your magic candies. You regain your next turn." << endl;
                                            stuck = false;
                                            selected_characters.at(turn).removeCandy(selected_characters.at(turn).getCandy(i).name);
                                            selected_characters.at(turn).setLostTurn(false);
                                        } else{
                                            cout << "You failed to use your magic candy. You lose your next turn." << endl;
                                            selected_characters.at(turn).setLostTurn(true);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    for(int i = 0; i < selected_characters.size(); i++){
                        if(board.getPlayerPosition(turn) == board.getPlayerPosition(i) && players[turn] != players[i]){
                            onSameTile = true;
                            firstPlayerIndex = i;
                            secondPlayerIndex = turn;
                        }
                    }
                    if(onSameTile){
                        bool unProtected = true;
                        cout << players[turn] << " landed on the same tile as " << players[firstPlayerIndex] << "!" << endl;
                        if(selected_characters.at(turn).findCandy("Robbers Repel").name == "Robbers Repel"){
                            cout << players[firstPlayerIndex] << " could have stolen gold from " << players[turn] << " however, you have Robbers Repel! Would you like to use it?(y/n)" << endl;
                            cin >> selection_input;
                            if(selection_input == "y"){
                                unProtected = false;
                                cout << "Robbers Repel Expended! Opposing player moved backwards one" << endl;
                                board.movePlayer(-1, firstPlayerIndex);
                                selected_characters.at(turn).removeCandy("Robbers Repel");
                            } else{
                                cout << players[turn] << " chose not to use Robbers Repel" << endl;
                            }
                        }
                        if(unProtected){
                            int goldLost = (rand()%30)+5;
                            cout << players[firstPlayerIndex] << " has stolen " << goldLost <<  " gold from " << players[turn] << " and pushed them back tile" << endl;
                            board.movePlayer(-1, turn);
                            selected_characters.at(turn).setGold(selected_characters.at(turn).getGold() - goldLost);
                            selected_characters.at(firstPlayerIndex).setGold(selected_characters.at(firstPlayerIndex).getGold() + goldLost);
                            if(selected_characters.at(turn).getGold() < 0){
                                selected_characters.at(turn).setGold(0);
                            }
                        }   
                    }
                    
                    
                    if(board.getPlayerPosition(turn) == hiddenPos1){
                        cout << "You have discovered hidden treasure!\nSolve this riddle to get a reward!" << endl;
                        board.getTreasure(0).setSolver(selected_characters.at(turn));
                        cout << board.getTreasure(0).getRiddle() << endl;
                        string answer;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        getline(cin, answer);
                        cout << answer << " " << board.getTreasure(0).getAnswer();
                        if(answer == board.getTreasure(0).getAnswer()){
                            cout << "That is correct!" << endl;
                            cout << "The reward is " << board.getTreasure(0).getType() << endl;
                            board.getTreasure(0).reward();
                        }
                    } else if(board.getPlayerPosition(turn) == hiddenPos2){
                        cout << "You have discovered hidden treasure!\nSolve this riddle to get a reward!" << endl;
                        board.getTreasure(1).setSolver(selected_characters.at(turn));
                        cout << board.getTreasure(1).getRiddle() << endl;
                        string answer;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        getline(cin, answer);
                        if(answer == board.getTreasure(1).getAnswer()){
                            cout << "That is correct!" << endl;
                            cout << "The reward is " << board.getTreasure(1).getType() << endl;
                            board.getTreasure(1).reward();
                        }
                    } else if(board.getPlayerPosition(turn) == hiddenPos3){
                        cout << "You have discovered hidden treasure!\nSolve this riddle to get a reward!" << endl;
                        board.getTreasure(2).setSolver(selected_characters.at(turn));
                        cout << board.getTreasure(2).getRiddle() << endl;
                        string answer;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        getline(cin, answer);
                        if(answer == board.getTreasure(2).getAnswer()){
                            cout << "That is correct!" << endl;
                            cout << "The reward is " << board.getTreasure(2).getType() << endl;
                            board.getTreasure(2).reward();
                        }
                    }
                    
                    int hailstormChance = (rand()%100);
                    if(hailstormChance < 5){
                        for(int i = 0; i < selected_characters.size() ; i++){
                            int random_tiles = (rand()%10)+1;
                            board.movePlayer(-random_tiles, i);
                        }
                    }

                    cout << "\nHere is an updated board:" << endl;
                    board.displayBoard();
                    if(!selected_characters.at(turn).getExtraTurn()){
                        turn++;
                    } else{
                        cout << "Extra Turn!!!" << endl;
                        selected_characters.at(turn).setExtraTurn(false);
                    }
                }
                break;
            case 2:
                cout << "Here is your Inventory of candies:" << endl;
                selected_characters.at(turn).printInventory();
                cout << "Which candy would you like to eat?" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                getline(cin, candy_input);
                if(selected_characters.at(turn).findCandy(candy_input).name == candy_input){ 
                    int value = selected_characters.at(turn).eatCandy(candy_input);
                    selected_characters.at(turn).removeCandy(candy_input);
                    cout << players[turn] << " ate " << candy_input << endl; 
                    if(value < 0){
                        cout << "Who do you want to deal this damage to?" << endl;
                        string selected_player;
                        getline(cin, selected_player);
                        for(int i = 0; i < player_count; i++){
                            if(players[i] == selected_player){
                                cout << " delt " << value << " stamina damage to " << players[i] << endl;
                                selected_characters.at(i).setStamina(selected_characters.at(i).getStamina() + value);
                                if(selected_characters.at(i).getStamina() == 0){
                                    selected_characters.at(i).setStamina(0);
                                }
                            }
                        }
                    }
                    candy_input = "";
                    if(!selected_characters.at(turn).getExtraTurn()){ 
                        turn++;
                    } else{
                        selected_characters.at(turn).setExtraTurn(false);
                    }
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
            case 4:
                if(atCandyStore){
                    printCandyStore(board.getCandyStore(atCandyStoreIndex).getCandyList(), 3);
                    cout << "What would you like to buy?" << endl;
                    bool candyFound = false;
                    int candyIndex = 0;
                    while(!candyFound){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        getline(cin, selection_input);
                        for(int i = 0; i < board.getCandyStore(atCandyStoreIndex).getCandyList().size(); i++){
                            if(selection_input == board.getCandyStore(atCandyStoreIndex).getCandyList().at(i).name){
                                candyFound = true;
                                candyIndex = i;
                            }
                        }
                    }
                    if(selected_characters.at(turn).getGold() >= board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex).price){
                        if(selected_characters.at(turn).getCandyAmount() == 4){
                            cout << "Insufficient Space, would you like to exchange a candy for this one?" << endl;
                            string confirm;
                            cin >> confirm;
                            if(confirm == "y"){
                                selected_characters.at(turn).printInventory();
                                cout << "Which candy would you like to replace?" << endl;
                                string replaced_candy;
                                bool found_replaced_candy = false;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                getline(cin, replaced_candy);
                                for(int i = 0; i < 4; i++){
                                    if(found_replaced_candy){
                                        continue;
                                    }
                                    if(replaced_candy == selected_characters.at(turn).getCandy(i).name){
                                        found_replaced_candy = true;
                                        selected_characters.at(turn).removeCandy(replaced_candy);
                                    }
                                }
                                if(found_replaced_candy){
                                    cout << "Successfully Purchased and Stored " << board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex).name << endl;
                                    selected_characters.at(turn).setGold(selected_characters.at(turn).getGold() - board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex).price);
                                    selected_characters.at(turn).addCandy(board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex));
                                }
                            } else{
                                cout << "Your pockets are too full of good stuff! Maybe next time!" << endl;
                            }
                        } else {
                            cout << "Successfully Purchased and Stored " << board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex).name << endl;
                            selected_characters.at(turn).setGold(selected_characters.at(turn).getGold() - board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex).price);
                            selected_characters.at(turn).addCandy(board.getCandyStore(atCandyStoreIndex).getCandyList().at(candyIndex));
                        }
                    } else{
                        cout << "Insufficient Funds." << endl;
                    }

                    atCandyStore = false;
                    atCandyStoreIndex = -1;
                } else{
                    cout << "Invalid Input, please enter 1, 2, or 3." << endl;
                }
                break;
            case 8: // Remove after Testing
                gameRunning = false; 
                break;
            default:
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input, please enter 1, 2, or 3." << endl;
                break;
        }
        cout << "Press any key to continue" << endl;
        cin >> turn_input;
        cin.clear();
        cin.ignore(1000, '\n');
        system("cls"); // "cls for Windows, clear for MacOS"

        if(turn == player_count){
            round += 1;
            turn = 0;
            atCandyStore = false;
        }
        if(board.getPlayerPosition(turn) == 82){
            gameRunning = false;
            string winner = players[turn];
        } 
    }

    cout << players[turn] << " has won the game!" << endl;
    cout << "Performance Statistics have been written in the win file!" << endl;
    ofstream winfile("windata.txt");
    winfile << "Winner: " << players[turn] << endl;
    winfile << "Character used: " << selected_characters.at(turn).getName() << endl;
    winfile << "Total Gold: " << selected_characters.at(turn).getGold() << endl;
    winfile << "Candies Remaining: " << selected_characters.at(turn).getCandy(0).name << ", " << selected_characters.at(turn).getCandy(1).name << ", " << selected_characters.at(turn).getCandy(2).name << ", " << selected_characters.at(turn).getCandy(3).name << endl;

    return 0;
}