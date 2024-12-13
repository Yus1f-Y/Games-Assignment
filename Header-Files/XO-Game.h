#pragma once

#include <iostream>
#include "BoardGame_Classes.h"
#include <random>
using namespace std;

template <typename T>
class XOTTTBoard : public Board<T>{

public:

    char winsymbol = ' ';

    char turns[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };


    void display_board() {

        cout << " ----------------------------------------------\n";

        cout << " |(0,0) " << turns[0][0] << " |(0,1) " << turns[0][1] << " |(0,2) " << turns[0][2] << " |\n";

        cout << " ----------------------------------------------\n";

        cout << " |(1,0) " << turns[1][0] << " |(1,1) " << turns[1][1] << " |(1,2) " << turns[1][2] << " |\n";

        cout << " ----------------------------------------------\n";

        cout << " |(2,0) " << turns[2][0] << " |(2,1) " << turns[2][1] << " |(2,2) " << turns[2][2] << " |\n";

        cout << " ----------------------------------------------\n";
    }

    void displayrow(int i) {
        cout << " |(" << i << ",0) " << turns[i][0] << " |(" << i << ",1) " << turns[i][1] << " |(" << i << ",2) " << turns[i][2] << " |";
    }

    bool is_win() {

        bool check = false;
        for(int i = 0; i < 3; i++) {
            if( turns[i][0] == turns[i][1] && turns[i][1] == turns[i][2] && turns[i][1] != ' ' ||
                turns[0][i] == turns[1][i] && turns[1][i] == turns[2][i] && turns[1][i] != ' ') {
                check = true;
            }
        }

        if( turns[2][0] == turns[1][1] && turns[1][1] == turns[0][2] && turns[1][1] != ' ' ||
            turns[0][0] == turns[1][1] && turns[1][1] == turns[2][2] && turns[1][1] != ' '  ){
            check = true;
        }

        return check;
    }

    bool is_draw() {
        if (is_win()) {
            return false;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (turns[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    bool update_board(int x, int y, T symbol) {
        if (turns[x][y] == ' ') {
            turns[x][y] = symbol;
            if(is_win()) {
                FillWithChar(symbol);
                winsymbol = symbol;
            }
            if(is_draw()) {
                FillWithChar('D');
                winsymbol = 'D';
            }
            return true;
        }
        return false;
    }

    bool game_is_over() {
        return (is_win() || is_draw());
    }

    void FillWithChar(char c) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                turns[i][j] = c;
            }
        }
    }

    void ResetBoard() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                turns[i][j] = ' ';
            }
        }
    }
};