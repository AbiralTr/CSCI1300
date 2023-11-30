#pragma once

#include <string>
#include <vector>

using namespace std;

struct Candy{
    string name = "Empty";
    string description;
    double price = 0;
    string candy_type;
    int value = 0;
};

class CandyStore{
    private:
        string _store_name = "";
        int _position = 0;
        vector<Candy> _candy_list;
    public:
        CandyStore();
        CandyStore(string name, vector<Candy> list, const int CANDY_LIST_SIZE, int position);

        string getName();
        int getPosition();
        vector<Candy> getCandyList();

        void setName(string s);
        void setPosition(int i);
        void setList(vector<Candy> list);
        void displayStock();
};
