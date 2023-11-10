#include "Player.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

vector<Candy> readCandy(string file_name, vector<Candy> candies){
    string name;
    string description;
    double price = 0.0;
    string type;

    ifstream file(file_name);
    if(file.fail()){
        cout << "Failed to open file" << endl;
        return candies;
    }
    
    string line;
    while(getline(file, line)){
        if(line.length() == 0){
            continue;
        }
        Candy current_candy = Candy();
        string word;
        stringstream ss(line);
        vector<string> stats;
        while(getline(ss, word, '|')){
            stats.push_back(word);
        }

        current_candy.name = stats.at(0);
        current_candy.description = stats.at(1);
        current_candy.price = stod(stats.at(2));
        current_candy.candy_type = stats.at(3);
        
        candies.push_back(current_candy);
    }

    return candies;
}

void displayCandyVector(vector<Candy> candies){
    for(int i = 0; i < candies.size(); i++){
        cout << "Name: " << candies.at(i).name << ". Description: " << candies.at(i).description << ". Price: " << candies.at(i).price << ". " << "Type: " << candies.at(i).candy_type << endl;
    }
}

int main(){
    vector<Candy> myVector;
    string file_name;
    cout << "Enter file to read:" << endl;
    cin >> file_name;
    myVector = readCandy(file_name, myVector);
    cout << myVector.size() << endl;
    displayCandyVector(myVector);
    
    
}