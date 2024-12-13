#pragma once

#include <iostream>
#include "BoardGame_Classes.h"
#include <random>
using namespace std;

template <typename T>
class FourBYFourTTTBoard : public Board<T>{

public:
    FourBYFourTTTBoard() {
        this->rows = 4;
        this->columns = 4;
    }
    char turns[4][4] = {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    };

    void display_board() {

        cout << " -----------------------------------\n";

        cout << " |(3,0) " << turns[3][0] << " |(3,1) " << turns[3][1] << " |(3,2) " << turns[3][2] << " |(3,3) " << turns[3][3] << " |\n";

        cout << " -----------------------------------\n";

        cout << " |(2,0) " << turns[2][0] << " |(2,1) " << turns[2][1] << " |(2,2) " << turns[2][2] << " |(2,3) " << turns[2][3] << " |\n";

        cout << " -----------------------------------\n";

        cout << " |(1,0) " << turns[1][0] << " |(1,1) " << turns[1][1] << " |(1,2) " << turns[1][2] << " |(1,3) " << turns[1][3] << " |\n";

        cout << " -----------------------------------\n";

        cout << " |(0,0) " << turns[0][0] << " |(0,1) " << turns[0][1] << " |(0,2) " << turns[0][2] << " |(0,3) " << turns[0][3] << " |\n";

        cout << " -----------------------------------\n";
    }

    bool is_win() {

        bool check = false;
        for(int i = 0; i < 4; i++) {
            if( turns[i][0] == turns[i][1] && turns[i][1] == turns[i][2] && turns[i][1] != ' ' ||
                turns[i][1] == turns[i][2] && turns[i][2] == turns[i][3] && turns[i][2] != ' ' ||
                turns[0][i] == turns[1][i] && turns[1][i] == turns[2][i] && turns[1][i] != ' ' ||
                turns[1][i] == turns[2][i] && turns[2][i] == turns[3][i] && turns[2][i] != ' '  ) {
                check = true;
            }
        }

        if( turns[2][0] == turns[1][1] && turns[1][1] == turns[0][2] && turns[1][1] != ' ' ||
            turns[3][1] == turns[2][2] && turns[2][2] == turns[1][3] && turns[2][2] != ' ' ||
            turns[3][0] == turns[2][1] && turns[2][1] == turns[1][2] && turns[2][1] != ' ' ||
            turns[2][1] == turns[1][2] && turns[1][2] == turns[0][3] && turns[1][2] != ' ' ||
            turns[1][0] == turns[2][1] && turns[2][1] == turns[3][2] && turns[2][1] != ' ' ||
            turns[0][1] == turns[1][2] && turns[1][2] == turns[2][3] && turns[1][2] != ' ' ||
            turns[0][0] == turns[1][1] && turns[1][1] == turns[2][2] && turns[1][1] != ' ' ||
            turns[1][1] == turns[2][2] && turns[2][2] == turns[3][3] && turns[2][2] != ' ' ){
            check = true;
        }

        if(check) {
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    turns[i][j] = ' ';
                }
            }
        }

        return check;
    }

    bool is_draw() {
        if (is_win()) {
            return false;
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (turns[i][j] == ' ') {
                    return false;
                }
            }
        }

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                turns[i][j] = ' ';
            }
        }
        return true;
    }

    bool update_board(int x, int y, T symbol) {
        if (turns[x][y] == ' ') {
            turns[x][y] = symbol;
            return true;
        }

        return false;
    }

    bool game_is_over() {

        if (is_win() || is_draw()) {

        }
        return false;
    }

};

template <typename T>
class FourBYFourTTTplayer : public Player<T>{
public:
    FourBYFourTTTplayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;
    }

};

template <typename T>
class FourBYFourTTTrandomplayer : public Player<T>{
public:
    FourBYFourTTTrandomplayer(T symbol) : Player<T>(symbol) {}

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        x = rand() % 4;
        y = rand() % 4;
    }

};