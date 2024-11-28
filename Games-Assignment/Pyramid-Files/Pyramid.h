#pragma once
#pragma once

#include <iostream>
#include "GameClassesBoard.h"
#include <random>
using namespace std;

template <typename T>
class PyramidBoard : public Board<T>{

public:
    PyramidBoard() {
        this->rows = 3;
        this->columns = 5;
    }
    char turns[3][5] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'E', 'E'},
        {' ', 'E', 'E', 'E', 'E'}
    };

    void display_board() {
        cout << endl;
        cout << "                    --------\n";

        // Top row
        cout << "                   |(2,0) " << turns[2][0] << " |\n";

        cout << "           --------------------------\n";

        // Middle row
        cout << "          |(1,0) " << turns[1][0] << " |(1,1) " << turns[1][1] << " |(1,2) " << turns[1][2] << " | \n";

        cout << "  --------------------------------------------\n";

        // Bottom row
        cout << " |(0,0) " << turns[0][0] << " |(0,1) " << turns[0][1] << " |(0,2) " << turns[0][2] << " |(0,3) " << turns[0][3] << " |(0,4) " << turns[0][4] << " |\n";

        cout << " ----------------------------------------------\n";
    }

    bool is_win() {

        if ((turns[0][0] == turns[0][1] && turns[0][1] == turns[0][2] && turns[0][1] != ' ') ||
            (turns[0][1] == turns[0][2] && turns[0][2] == turns[0][3] && turns[0][2] != ' ') ||
            (turns[0][2] == turns[0][3] && turns[0][3] == turns[0][4] && turns[0][3] != ' ') ||
            (turns[1][0] == turns[1][1] && turns[1][1] == turns[1][2] && turns[1][1] != ' ') ||
            (turns[2][0] == turns[1][0] && turns[1][0] == turns[0][0] && turns[1][0] != ' ') ||
            (turns[2][0] == turns[1][1] && turns[1][1] == turns[0][2] && turns[1][1] != ' ') ||
            (turns[2][0] == turns[1][2] && turns[1][2] == turns[0][4] && turns[1][2] != ' ')) {
            return true;
        }

        return false;
    }

    bool is_draw() {
        if (is_win()) {
            return false;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
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
            return true;
        }

        return false;
    }

    bool game_is_over() {

        if (is_win() || is_draw()) {
            turns[0][0] = turns[0][1] = turns[0][2] = turns[0][3] = turns[0][4] = turns[1][0] = turns[1][1] =
            turns[1][2] = turns[2][0] = ' ';
        }
        return (is_win() || is_draw());
    }

};

template <typename T>
class Pyramidplayer : public Player<T>{
public:
    Pyramidplayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
    }

};

template <typename T>
class RandomPyramidplayer : public Player<T>{
public:
    RandomPyramidplayer(T symbol) : Player<T>(symbol) {}

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        x = rand() % 3;
        y = rand() % 5;
    }

};