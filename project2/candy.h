#include <string>
#include <vector>

using namespace std;

struct Candy{
    string name;
    string description;
    double price;
    string candy_type;
    int value;
};

class CandyStore{
    private:
        string _store_name = "";
        int _position = 0;
        vector<Candy> _candy_list;
    public:
        CandyStore();
        CandyStore(string name, vector<Candy> list, int position);

        string getName();
        vector<Candy> getCandyList();

        void setName(string s);
        void setList(vector<Candy> list);
        void displayStock();
};
