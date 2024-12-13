#pragma once
#include <iostream>
#include <string>
#include "Numeric.h"
using namespace std;

template <typename T>
class PlayNumericGame {
private:
    Player<T>* players[2];

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
        //cout << "[3]-Smart Computer (AI)\n";
        choice = valid_choice(1,2);

        switch(choice) {
            case 1:
                players[i] = new Numericplayer<T>(name, symbol);
            break;
            case 2:
                players[i] = new RandomNumericplayer<T>(symbol);
            break;
            /*case 3:
                players[i] = new X_O_MinMax_Player<char>('X');
            players[i]->setBoard(B);
            break;*/
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
