#include "board.cpp"
#include "Player.cpp"
#include "candy.cpp"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){

    // Testing the creation of a single piece of candy
    Candy chocolate{"Chocolate", "A bar of chocolate", 2.75, "Buff", 4};
    cout << "This is the information of a candy we just created:" << endl;
    cout << "Name: " << chocolate.name << "\nDescription: " << chocolate.description << "\nPrice: " << chocolate.price << "\nType: " << chocolate.candy_type << "\nValue: " << chocolate.value << endl;

    // Testing the creation of a Candy Store
    CandyStore chocolateStore;
    chocolateStore.setName("Coco's Candy Store");
    chocolateStore.setPosition(65);
    vector<Candy> chocolateList = {chocolate, chocolate, chocolate}; // Creating a vector full of "Chocolate" to insert into the stock of our Chocolate candy store
    chocolateStore.setList(chocolateList);
    cout << "\nThis is the information of the candy store we just created:" << endl;
    cout << "Name: " << chocolateStore.getName() << "\nPosition: " << chocolateStore.getPosition() << endl;
    cout << "Displaying Stock by iterating through the vector directly:\n" << endl;
    for(int i = 0; i < chocolateStore.getCandyList().size(); i++){
        cout << "Candy struct @ index " << i << ": " << chocolateStore.getCandyList().at(i).name << endl;
    }
    cout << "\nDisplaying Stock with a function:\n" << endl;
    chocolateStore.displayStock();
    
    // Testing the creation of a Player Object
    Player testplayer = Player();
    testplayer.setName("Peter");
    testplayer.setStamina(20);
    testplayer.setGold(150);
    testplayer.setEffect("Super Boosted");
    Candy array[] = {chocolate, chocolate}; // Creating an inventory to start the player off with
    testplayer.setInventory(array, 2);
    testplayer.setOwner("Peter's Owner");
    cout << "\nThis is the information of the player we just created:" << endl;
    cout << "Name: " << testplayer.getName() << "\nOwner: " << testplayer.getOwner() << "\nStamina: " << testplayer.getStamina() << "\nGold: " << testplayer.getGold() << "\nEffect: " << testplayer.getEffect() << "\nInventory:" << endl;
    testplayer.addCandy(chocolate);
    cout << "Candy Amount: " << testplayer.getCandyAmount() << endl;
    testplayer.printInventory();
    Player testplayer2 = Player("Rigby", 15, 227, "Mega Looted", array, 2); // Create another Player
    Player players[] = {testplayer, testplayer2};
    cout << "\nPlaying Rock Paper Scissors with Peter and Rigby:" << endl;
    playRockPaperScissors(players);

    // Testing the Board
    cout << "\nTesting the Board:" << endl;
    Board board = Board();
    vector<Player> playerVector = {testplayer, testplayer2};
    board.setPlayers(playerVector);
    board.addCandyStore(chocolateStore.getPosition(), chocolateStore);
    CandyStore sweetStore = CandyStore();
    cout << "Choose a starting player position: ";
    int starting_position = 0;
    cin >> starting_position;
    board.setPlayerPosition(starting_position, 0);
    board.displayBoard();
    int player_move_input = 1;
    while(player_move_input != 0){
        cout << "Choose how you want to move(0 to exit): ";
        cin >> player_move_input;
        if(player_move_input == 0){
            continue;
        }
        board.movePlayer(player_move_input, 0);
        board.displayBoard();
        if(board.isPositionCandyStore(board.getPlayerPosition(0))){
            if(board.getPlayerPosition(0) == board.getCandyStore(0).getPosition()){
                cout << "You have arrived @ " << board.getCandyStore(0).getName() << endl;
                board.getCandyStore(0).displayStock();
            } else if(board.getPlayerPosition(0) == board.getCandyStore(1).getPosition()){
                cout << "You have arrived @ " << board.getCandyStore(1).getName() << endl;
                board.getCandyStore(1).displayStock();
            } else if(board.getPlayerPosition(0) == board.getCandyStore(2).getPosition()){
                cout << "You have arrived @ " << board.getCandyStore(2).getName() << endl;
                board.getCandyStore(2).displayStock();
            }
        }
    }
}