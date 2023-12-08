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

// Tile Struct to be used in Board
struct Tile
{
    string color;
    bool isSpecial;
    string tile_type;
};

// Card Struct to be used in Board
struct Card{
    string name;
    bool isDouble;
    int tiles_moved;
    string color;
};

// Hidden Treasure Class to be used in Board Class
class hiddenTreasure{
    private:
        string type;
        string riddle;
        string answer;
        int position;
        Player solver;
    public:
        // Constructors
        hiddenTreasure();
        hiddenTreasure(string riddle, string answer);
        // Getters
        string getType();
        string getRiddle();
        string getAnswer();
        int getPos();
        // Setters
        void setRiddle(string r);
        void setSolver(Player p);
        void setPos(int p);
        void setType(int t);
        void reward();
};

// Board Class
class Board{
    private:
        const static int _BOARD_SIZE = 83;
        Tile _tiles[_BOARD_SIZE];
        const static int _MAX_CANDY_STORE = 3;
        int _candy_store_position[_MAX_CANDY_STORE];
        int _hidden_treasure_position[3];
        int _candy_store_count;
        vector<Player> _players;
        CandyStore _candy_stores[_MAX_CANDY_STORE];
        vector<hiddenTreasure> _hidden_treasures;

    public:
        // Constructor
        Board(); 
        // Essential Functions (Display and Functionality)
        void resetBoard();
        void displayTile(int);
        void displayBoard();
        bool movePlayer(int tile_to_move_forward, int player_index);
        Card drawCard(int index);
        // Getters
        Player getPlayer(int index);
        int getBoardSize() const;
        int getCandyStoreCount() const;
        CandyStore getCandyStore(int index);
        int getPlayerPosition(int);
        bool isPositionCandyStore(int); 
        Tile getTile(int position);
        hiddenTreasure getTreasure(int index);
        // Setters
        void addTreasure(int pos, hiddenTreasure h);
        bool setPlayerPosition(int, int);
        void setPlayers(vector<Player> players);
        bool addCandyStore(int, CandyStore);
};

