#pragma once
// 04_Cinema.cpp
// ONE responsibility: the theatre — owns its screens (composition).
#include <vector>
#include <string>
#include "03_Screen.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen*> screens;   // COMPOSITION: Cinema owns Screens

public:
    Cinema(string name) : name(name) {}

    ~Cinema() {
        for (Screen* s : screens) delete s;
    }

    void addScreen(Screen* screen) { screens.push_back(screen); }
    vector<Screen*>& getScreens() { return screens; }
    string getName() const { return name; }
};
