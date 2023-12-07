#pragma once

#include <iostream>
#include "candy.h"
#include "player.h"
#include <vector>
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Tile
{
    string color;
    string tile_types[4] = {"Shortcut", "Ice Cream", "Gumdrop", "Gingerbread"};
    string tile_type;
};

class Board{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    vector<Player> _players;
    CandyStore _candy_stores[_MAX_CANDY_STORE];

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    bool setPlayerPosition(int, int);
    void setPlayers(vector<Player> players);
    Player getPlayer(int index);
    int getBoardSize() const;
    int getCandyStoreCount() const;
    CandyStore getCandyStore(int index);
    int getPlayerPosition(int);
    int drawCard(int index);

    bool calamityCheck(); // Psuedo-code
    bool riddle(int index); //Psuedo-code

    bool addCandyStore(int, CandyStore);
    bool isPositionCandyStore(int); 

    bool movePlayer(int tile_to_move_forward, int player_index);
};