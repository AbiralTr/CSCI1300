#include <iostream>

using namespace std;

int main(){
    int quantum_shards = 0;
    int celestial_fragments = 0;
    int astral_essence = 0;
    int cosmic_dust = 0;
    int element_core = 0;
    // Input
    cout << "Enter the number of Element Core Particles: " << endl;
    cin >> element_core;
    if(element_core < 0){
        cout << "Invalid input. Please enter a non-negative integer.";
        return 0;
    }
    // Element Core to Cosmic Dust
    cosmic_dust = element_core / 2;
    element_core -= cosmic_dust * 2;
    // Cosmic Dust to Astral Essence
    astral_essence = cosmic_dust / 5;
    cosmic_dust -= astral_essence * 5;
    // Astral Essence to Celestial Fragments
    celestial_fragments = astral_essence / 18;
    astral_essence -= celestial_fragments * 18;
    // Celestial Fragements to Quantum Shards
    quantum_shards = celestial_fragments / 32;
    celestial_fragments -= quantum_shards * 32;
    cout << "Result:" << endl;
    cout << "Quantum Shards: " << quantum_shards << endl;
    cout << "Celestial Fragements: " << celestial_fragments << endl;
    cout << "Astral Essence: " << astral_essence << endl;
    cout << "Cosmic Dust: " << cosmic_dust << endl;
    cout << "Element Core: " << element_core << endl; 


    return 0;
}