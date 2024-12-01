#pragma once

#include <iostream>
#include "XO-Game.h"
using namespace std;

template <typename T>
class UltimateTTTBoard {
public:

    XOTTTBoard<T> turns[3][3];
    bool End[3][3] = {};


    void display_board() {
        cout << endl;
        cout << " ///////////////////////////////////////////////////////////////////////////////////////////////\n";

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                for(int k = 0; k < 3; k++) {
                    turns[i][k].displayrow(j);
                    cout << "|||";
                }
                cout << "\n ---------------------------||||----------------------------||||----------------------------||||\n";

            }
            cout << " ///////////////////////////////////////////////////////////////////////////////////////////////\n";
        }
    }

    bool is_win() {

        bool check = false;
        for(int i = 0; i < 3; i++) {
            if( turns[i][0].winsymbol == turns[i][1].winsymbol && turns[i][1].winsymbol == turns[i][2].winsymbol && turns[i][1].winsymbol != ' ' ||
                turns[0][i].winsymbol == turns[1][i].winsymbol && turns[1][i].winsymbol == turns[2][i].winsymbol && turns[1][i].winsymbol != ' ') {
                check = true;
                }
        }

        if( turns[2][0].winsymbol == turns[1][1].winsymbol && turns[1][1].winsymbol == turns[0][2].winsymbol && turns[1][1].winsymbol != ' ' ||
            turns[0][0].winsymbol == turns[1][1].winsymbol && turns[1][1].winsymbol == turns[2][2].winsymbol && turns[1][1].winsymbol != ' '  ){
            check = true;
            }

        if(check) {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    turns[i][j].ResetBoard();
                }
            }
        }

        return check;
    }

    bool is_draw() {
        if (is_win()) {
            return false;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (turns[i][j].winsymbol == ' ') {
                    return false;
                }
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                turns[i][j].ResetBoard();
            }
        }
        return true;
    }

    bool update_board(int x1, int y1,T symbol) {
        cout << "Enter the values of the index inside the matrix we want to play in.\n";
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        int x2, y2;
        cin >> x2 >> y2;
        return(turns[x1][y1].update_board(x2, y2, symbol));
    }

    bool update_board_random(T symbol) {
        int x1, x2, y1, y2;
        x1 = rand() % 3;
        y1 = rand() % 3;
        x2 = rand() % 3;
        y2 = rand() % 3;
        return(turns[x1][y1].update_board(x2, y2, symbol));
    }

    bool game_is_over() {

        return (is_win() || is_draw());
    }
};

template <typename T>
class Ultimateplayer : public Player<T>{
public:
    Ultimateplayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x1, int& y1) {
        cout << "First for the index of the matrix you gonna play in.\n";
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x1 >> y1;
    }
};

template <typename T>
class Ultimaterandomplayer : public Player<T>{
public:
    Ultimaterandomplayer(T symbol) : Player<T>(symbol) {}

    void getmove(int& x1, int& y1) {
        cout << "\nPlease enter your move x and y (0 to 3) separated by spaces: ";
        x1 = rand() % 3;
        y1 = rand() % 3;
    }
};

