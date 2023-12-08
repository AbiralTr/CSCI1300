#pragma once

#include <string>
#include <vector>

using namespace std;

// Candy Struct to be used in Candy Store
struct Candy{
    string name = "Empty";
    string description;
    double price = 0;
    string effect_type;
    string candy_type;
    int value = 0;
};

// Candy Store Class
class CandyStore{
    private:
        string _store_name = "";
        int _position = 0;
        vector<Candy> _candy_list;
    public:
        // Constructors
        CandyStore();
        CandyStore(string name, vector<Candy> list, const int CANDY_LIST_SIZE, int position);

        // Getters
        string getName();
        int getPosition();
        vector<Candy> getCandyList();

        //Setters
        void setName(string s);
        void setPosition(int i);
        void setList(vector<Candy> list);
        void displayStock();
};
