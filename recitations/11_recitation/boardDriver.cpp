#include "board.cpp"
#include <iostream>
#include <cstdlib>

using namespace std;



int main(){
    Board board;
    int input = 0;

    int rand_pos1 = (rand()/(double) RAND_MAX) * 82;
    int rand_pos2 = (rand()/(double) RAND_MAX) * 82;
    int rand_pos3 = (rand()/(double) RAND_MAX) * 82;

    Candy lolipop{"Lolipop"};
    Candy twizzler{"Twizzler"};
    Candy kitkat{"KitKat"};

    vector<Candy> store1supply = {lolipop, lolipop, lolipop};
    vector<Candy> store2supply = {twizzler, twizzler, twizzler};
    vector<Candy> store3supply = {kitkat, kitkat,kitkat};

    CandyStore store1("Lolipop Shop", store1supply, rand_pos1);
    CandyStore store2("Twizzler Store", store2supply, rand_pos2);
    CandyStore store3("KitKat Dealer", store3supply, rand_pos3);

    board.addCandyStore(rand_pos1);
    board.addCandyStore(rand_pos2);
    board.addCandyStore(rand_pos3);

    board.displayBoard();
    
    if(board.isPositionCandyStore(board.getPlayerPosition())){
            if(board.getPlayerPosition() == rand_pos1){
                store1.displayStock();
            } else if(board.getPlayerPosition() == rand_pos2){
                store2.displayStock();
            } else if(board.getPlayerPosition() == rand_pos3){
                store3.displayStock();
            }
        }
    while(true){
        cout << "You are at position: " << board.getPlayerPosition() << endl;
        cout << "How many tiles would you like to move? ";
        cout << "Stores are located at pos: " << rand_pos1 << ", " << rand_pos2 << ", " << rand_pos3 << "." << endl;
        cin >> input;
        system("cls");
        board.movePlayer(input);
        board.displayBoard();
        if(board.isPositionCandyStore(board.getPlayerPosition())){
            if(board.getPlayerPosition() == rand_pos1){
                store1.displayStock();
            } else if(board.getPlayerPosition() == rand_pos2){
                store2.displayStock();
            } else if(board.getPlayerPosition() == rand_pos3){
                store3.displayStock();
            }
        }

        input = 0;
    }

    /*
    int player_count = 0;
    string players[] = {};
    cout << "Welcome to the game of candyland. Please enter the number of participants:" << endl;
    cin >> player_count;
    for(int i = 0; i < player_count; i++){
        cout << "Enter player name:" << endl;
        cin >> players[i];
        cout << "Awesome! Here is a list of characters a player can select from:" << endl;
        
    }
    */

    return 0;
}