#include "board.h"
#include "candy.h"
#include "player.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        /*
        Create rand that creates  20% chance of there being a special tile,
        if there is a special tile,
        have another random with 25% chance of any of the 4 types
        */
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
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
    cout << target.color << " ";

    if(position == _candy_store_position[0] || position == _candy_store_position[1] || position == _candy_store_position[2]){
        cout << "!";
    } else{
        cout << " ";
    }
    for(int i = 0; i < _players.size(); i++){
        if(position ==  _players.at(i).getPosition()){
            cout << i+1;
        }
    }
    
    cout << " " << RESET;
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
    int new_player_position = tile_to_move_forward + _players.at(index).getPosition();
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _players.at(index).setPosition(new_player_position);
    return true;
}

int Board::drawCard(string player){
    string colors[3] = {"Magenta", "Green", "Blue"};
    int tiles_moved = 0;
    /*
    Create rand object between 0 and 2 (inclusive)
    Return the rand: 0 = Magenta, 1 = Green, 2 = Blue
    The player connected to the function will then move to the nearest tile that corresponds with the color they drew
    */
    return tiles_moved;
}