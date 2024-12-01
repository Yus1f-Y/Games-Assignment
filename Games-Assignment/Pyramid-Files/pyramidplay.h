#pragma once
#include <iostream>
#include <string>
#include "Pyramid.h"
using namespace std;


template <typename T>
// PlayGame Class
class PlayPyramidGame {
private:
    Player<T>* firstPlayer = nullptr;
    Player<T>* secondPlayer = nullptr;
    int numGames = 0;

    static int menu1() {
        cout << "[1] Play VS a friend.\n";
        cout << "[2] Play VS computer.\n";
        return valid_choice(1, 2);
    }

    static int menu2() {
        cout << "[1] Play again.\n";
        cout << "[2] Exit.\n";
        return valid_choice(1, 2);
    }

    void setPlayers(bool vsComputer) {
        string name1, name2;
        char symbol1, symbol2;

        // Set up Player 1
        cout << "Player 1, enter your name: ";
        cin.ignore();
        getline(cin, name1);
        cout << "Choose your symbol:\n[1] 'X'\n[2] 'O'\n";
        symbol1 = (valid_choice(1, 2) == 1) ? 'X' : 'O';

        firstPlayer = new Pyramidplayer<T>(name1, symbol1);

        // Set up Player 2
        if (vsComputer) {
            symbol2 = (symbol1 == 'X') ? 'O' : 'X';
            secondPlayer = new RandomPyramidplayer<T>(symbol2);
        } else {
            cout << "Player 2, enter your name: ";
            cin.ignore();
            getline(cin, name2);
            symbol2 = (symbol1 == 'X') ? 'O' : 'X';
            secondPlayer = new Pyramidplayer<T>(name2, symbol2);
        }
    }

    static void announceWinner(Player<T>* winner) {
        cout << "The winner is " << winner->getname() << "!\n";
    }



public:

    void startGame(Board<T>& board) {
        while (true) {

            cout << "Welcome to the game!\n";
            bool vsComputer;
            if(menu1() == 1) {
                vsComputer = false;
            }else {
                vsComputer = true;
            }

            setPlayers(vsComputer);


            Player<T>* players[2];
            players[0] = firstPlayer;
            players[1] = secondPlayer;

            GameManager<T>game(&board, players);
            game.run();

            if (menu2() == 2) {
                cout << "Goodbye!\n";
                break;
            }
        }
    }

    ~PlayPyramidGame() {
        delete firstPlayer;
        delete secondPlayer;
    }
};
