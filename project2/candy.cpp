#include "candy.h"
#include <iostream>

using namespace std;

CandyStore::CandyStore(){

}

CandyStore::CandyStore(string name, vector<Candy> list, const int CANDY_LIST_SIZE){
    _store_name = name;
    _candy_list.resize(CANDY_LIST_SIZE);
    _candy_list = list;
}

string CandyStore::getName(){
    return _store_name;
}

vector<Candy> CandyStore::getCandyList()
{
    return _candy_list;
}

void CandyStore::setName(string s){
    _store_name = s;
}

void CandyStore::setList(vector<Candy> list){
    _candy_list = list;
}

int CandyStore::getPosition(){
    return _position;
}

void CandyStore::setPosition(int i){
    _position = i;
}

void CandyStore::displayStock(){
    cout << _store_name << "stock:" << endl;
    for(int i = 0; i < _candy_list.size(); i++){
        cout << _candy_list.at(i).name << endl;
    }
}