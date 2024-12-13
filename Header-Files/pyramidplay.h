#pragma once
#include <iostream>
#include <string>
#include "Pyramid.h"
using namespace std;


template <typename T>
// PlayGame Class
class PlayPyramidGame {
private:
    Player<T>* players[2];
    int numGames = 0;

    static int menu1() {
        cout << "[1] Play again.\n";
        cout << "[2] Exit.\n";
        return valid_choice(1, 2);
    }

    void setPlayer(int i) {
        string name;
        char symbol;
        if(i == 0) {
            symbol = 'X';
        }else {
            symbol = 'O';
        }

        cout << "Player " << symbol <<", enter your name: ";
        cin.ignore();
        getline(cin, name);


        int choice;
        cout << "Choose Player X type:\n";
        cout << "[1]-Human\n";
        cout << "[2]-Random Computer\n";
        choice = valid_choice(1,2);

        switch(choice) {
            case 1:
                players[i] = new Pyramidplayer<T>(name, symbol);
            break;
            case 2:
                players[i] = new RandomPyramidplayer<T>(symbol);
            break;
        }
    }

public:

    void startGame(Board<T>& board) {
        cout << "Welcome to the game!\n";
        for(int i = 0; i < 2; i++) {
            setPlayer(i);
        }

        GameManager<T>game(&board, players);
        game.run();
    }
};
