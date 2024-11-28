#pragma once

#include <iostream>
#include "GameClassesBoard.h"
using namespace std;

template <typename T>
class NumericBoard : public Board<T>{
private:
    int turns[3][3] = {};

public:
    NumericBoard() {
        this->rows = this->columns = 3;
    }

    void display_board() {

        cout << endl;

        cout << "          --------------------------- \n";

        // Top row
        cout << "          |(2,0) " << turns[2][0] << " |(2,1) " << turns[2][1] << " |(2,2) " << turns[2][2] << " | \n";

        cout << "          --------------------------- \n";

        // Middle row
        cout << "          |(1,0) " << turns[1][0] << " |(1,1) " << turns[1][1] << " |(1,2) " << turns[1][2] << " | \n";

        cout << "          --------------------------- \n";

        // Bottom row
        cout << "          |(0,0) " << turns[0][0] << " |(0,1) " << turns[0][1] << " |(0,2) " << turns[0][2] << " | \n";

        cout << "          --------------------------- \n";
    }

    bool is_win() {

        if ((turns[0][0] + turns[0][1] + turns[0][2] == 15 ) ||
            (turns[1][0] + turns[1][1] + turns[1][2] == 15 ) ||
            (turns[2][0] + turns[2][1] + turns[2][2] == 15 ) ||
            (turns[0][0] + turns[1][0] + turns[2][0] == 15 ) ||
            (turns[0][1] + turns[1][1] + turns[2][1] == 15 ) ||
            (turns[0][2] + turns[1][2] + turns[2][2] == 15 ) ||
            (turns[0][0] + turns[1][1] + turns[2][2] == 15 ) ||
            (turns[0][2] + turns[1][1] + turns[2][0] == 15 ) ) {
            return true;
        }

        return false;
    }

    bool is_draw() {
        if (is_win()) {
            return false;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (turns[i][j] == 0 ) {
                    return false;
                }
            }
        }
        return true;
    }

     bool update_board(int x, int y, T symbol) {
        if (turns[x][y] == 0) {

            if(symbol > 0 && symbol < 15) {
                cout << symbol;
                turns[x][y] = symbol;
                return true;
            }
            cout << "Value has to be bigger than 0 and smaller than 15.\n";
            return false;
        }
        else {
            cout << "This place is already used.\n";
            return false;
        }

    }

    bool game_is_over() {
        return (is_win() || is_draw());
    }
};


template <typename T>
class Numericplayer : public Player<T>{
public:
    Numericplayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
    }

};

template <typename T>
class RandomNumericplayer : public Player<T> {
public:
    RandomNumericplayer(T symbol) : Player<T>(symbol) {}

    void getmove(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        x = rand() % 3;
        y = rand() % 3;
    }
};

