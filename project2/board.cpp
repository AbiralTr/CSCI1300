#include "board.h"
#include "candy.h"
#include "player.h"
#include <cstdlib>
#include <time.h>
#include <random>

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{   
    srand(time(0));
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++){
        int specialChance = (rand()%4);

        current_color = COLORS[i % COLOR_COUNT];
        if(specialChance == 0){
            new_tile = {current_color, true};
            int specialType = (rand()%4);
            switch(specialType){
                case 0:
                    new_tile.tile_type = "Shortcut";
                    break;
                case 1:
                    new_tile.tile_type = "Ice Cream";
                    break;
                case 2:
                    new_tile.tile_type = "Gumdrop Forest";
                    break;
                case 3:
                    new_tile.tile_type = "Gingerbread House";
                    break;
            }
        } else{
            new_tile = {current_color, false ,"regular tile"};
        }
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, false, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color;

    cout << "  ";
    
    for(int i = 0; i < _players.size(); i++){
        if(position ==  _players.at(i).getPosition()){
            cout << i+1;
        }
    }
    cout << " " << RESET;
}

Tile Board::getTile(int position){
    return _tiles[position];
}

void Board::setPlayers(vector<Player> players){
    _players = players;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position, int player_index)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _players.at(player_index).setPosition(new_position);
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

CandyStore Board::getCandyStore(int index){
    return _candy_stores[index];
}

int Board::getPlayerPosition(int index)
{
    return _players.at(index).getPosition();
}

bool Board::addCandyStore(int position, CandyStore candystore)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_stores[_candy_store_count] = candystore;
    _candy_store_count++;
    
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

Player Board::getPlayer(int index){
    return _players.at(index);
}

bool Board::calamityCheck(){

    bool calamity;
    /*
    Creates a Rand between 1-10 (inclusive)
    1-4 = Calamity Happens, 5-10, Calamity does NOT happen
    Creates another rand to choose which calamity occurs

    Returns true if Calamity happens
    */
   return calamity;
}

bool Board::riddle(int index){
    bool answer_correct;
    /*
    Attaches to whichever player chooses to accept the riddle via index
    opens "riddles.txt" for a number of riddles,
    creates rand to randomly choose any line from the file that represents a riddle

    Returns true if the player got it correct, rewards accordingly using the index to decide which player to reward
    */
   return answer_correct;
}

bool Board::movePlayer(int tile_to_move_forward, int index)
{
    int new_player_position =  _players.at(index).getPosition() + tile_to_move_forward;
    if(new_player_position < 0){
        return false;
    } else if(new_player_position >= _BOARD_SIZE){
        new_player_position = 82;
    }
    _players.at(index).setPosition(new_player_position);
    return true;
}

Card Board::drawCard(int index){
    srand(time(0));
    string name;
    bool isDouble = false;
    string color;
    int tiles_moved = 0;
    int pull = (rand()%6) + 1;
    int current_position = getPlayer(index).getPosition()+1;
    int tile_ratio = current_position % 3;
    switch(pull){
        case 1:
            name = "Matrix Magenta";
            color = "purple";
            switch(tile_ratio){
                case 0: // blue
                    tiles_moved = 1;
                    movePlayer(1, index);
                    getPlayer(index).setPosition(current_position+1);
                    break;
                case 1: // purple
                    tiles_moved = 3;
                    movePlayer(3, index);
                    getPlayer(index).setPosition(current_position+3);
                    break;
                case 2: // green
                    tiles_moved = 2;
                    movePlayer(2, index);
                    getPlayer(index).setPosition(current_position+2);
                    break;
            }
            break;
        case 2:
            name = "Emerald Green";
            color = "green";
            switch(tile_ratio){
                case 0: // blue
                    tiles_moved = 2;
                    movePlayer(2, index);
                    getPlayer(index).setPosition(current_position+2);
                    break;
                case 1: // purple
                    tiles_moved = 1;
                    movePlayer(1, index);
                    getPlayer(index).setPosition(current_position+1);
                    break;
                case 2: // green
                    movePlayer(3, index);
                    tiles_moved = 3;
                    getPlayer(index).setPosition(current_position+3);
                    break;
            }
            break;
        case 3:
            name = "Beaten Blue";
            color = "blue";
            switch(tile_ratio){
                case 0: // blue
                    movePlayer(3, index);
                    tiles_moved = 3;
                    getPlayer(index).setPosition(current_position+3);
                    break;
                case 1: // purple
                    movePlayer(2, index);
                    tiles_moved = 2;
                    getPlayer(index).setPosition(current_position+2);
                    break;
                case 2: // green
                    movePlayer(1, index);
                    tiles_moved = 1;
                    getPlayer(index).setPosition(current_position+1);
                    break;
            }
            break;
        case 4:
            name = "Metaphysical Magenta";
            isDouble = true;
            color = "purple";
            switch(tile_ratio){
                case 0: // blue
                    movePlayer(4, index);
                    tiles_moved = 4;
                    getPlayer(index).setPosition(current_position+4);
                    break;
                case 1: // purple
                    movePlayer(6, index);
                    tiles_moved = 6;
                    getPlayer(index).setPosition(current_position+6);
                    break;
                case 2: // green
                    movePlayer(5, index);
                    tiles_moved = 5;
                    getPlayer(index).setPosition(current_position+5);
                    break;
            }
            break;
        case 5:
            name = "Groundbreaking Green";
            isDouble = true;
            color = "green";
            switch(tile_ratio){
                case 0: // blue
                    movePlayer(5, index);
                    tiles_moved = 5;
                    getPlayer(index).setPosition(current_position+5);
                    break;
                case 1: // purple
                    movePlayer(4, index);
                    tiles_moved = 4;
                    getPlayer(index).setPosition(current_position+4);
                    break;
                case 2: // green
                    movePlayer(6, index);
                    tiles_moved = 6;
                    getPlayer(index).setPosition(current_position+6);
                    break;
            }
            break;
        case 6:
            name = "Black n Blue";
            isDouble = true;
            color = "blue";
                switch(tile_ratio){
                    case 0: // blue
                        movePlayer(6, index);
                        tiles_moved = 6;
                        getPlayer(index).setPosition(current_position+6);
                        break;
                    case 1: // purple
                        movePlayer(5, index);
                        tiles_moved = 5;
                        getPlayer(index).setPosition(current_position+5);
                        break;
                    case 2: // green
                        movePlayer(4, index);
                        tiles_moved = 4;
                        getPlayer(index).setPosition(current_position+4);
                        break;
                }
            break;
    }

    Card card{name, isDouble, tiles_moved, color};
    return card;
}

hiddenTreasure::hiddenTreasure(){

}

hiddenTreasure::hiddenTreasure(string r, string a){
    riddle = r;
    answer = a;

}

string hiddenTreasure::getRiddle(){
    return riddle;
}

string hiddenTreasure::getType(){
    return type;
}

int hiddenTreasure::getPos(){
    return position;
}

void hiddenTreasure::setRiddle(string r){
    riddle = r;
}

void hiddenTreasure::setSolver(Player p){
    solver = p;
}

void hiddenTreasure::setPos(int p){
    position = p;
}

string hiddenTreasure::getAnswer(){
    return answer;
}

void hiddenTreasure::setType(int t){
    switch(t){
        case 0:
            type = "Stamina Refill";
            break;
        case 1:
            type = "Gold Windfall";
            break;
        case 2:
            type = "Robber's Repel";
            break;
        case 3:
            type = "Candy Acquisition";
            break;
    }
}

void Board::addTreasure(int pos, hiddenTreasure h){
    _hidden_treasures.push_back(h);
}

hiddenTreasure Board::getTreasure(int index){
    return _hidden_treasures[index];
}

void hiddenTreasure::reward(){
    srand(time(0));
    if(type == "Stamina Refill"){
        int refill_amount = (rand()%30)+10;
        solver.setStamina(solver.getStamina()+refill_amount);
        if(solver.getStamina() > 100){
            solver.setStamina(100);
        }
    } else if(type == "Gold Windfall"){
        int gold_amount = (rand()%40)+20;
        solver.setGold(solver.getGold()+gold_amount);
        if(solver.getGold() > 100){
            solver.setGold(100);
        }
    } else if(type == "Robber's Repel"){
        Candy rr{"Robbers Repel"};
        cout << "You received Robbers Repel!" << endl;
        solver.addCandy(rr);
    } else if(type == "Candy Acquisition"){
        int chance = (rand()%10);
        if(chance > 3){
            Candy jellybean{"Jellybean of Vigor", "Restores 50 units of stamina", 0, "stamina" ,"magical", 50};
            cout << "You received the Jellybean of Vigor!" << endl;
            solver.addCandy(jellybean);
        } else{
            Candy truffle{"Treasure Hunter's Truffle", "Allows access to more hidden treasures", 0, "other" ,"magical", 1};
            cout << "You received the Treasure Hunter's Truffle!" << endl;
            solver.addCandy(truffle);
        }
    }
}