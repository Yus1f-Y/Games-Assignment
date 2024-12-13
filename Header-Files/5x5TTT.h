#ifndef _5X5_TIC_TAC_TOE_H
#define _5X5_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class FiveByFiveBoard : public Board<T> {
public:
    FiveByFiveBoard();
    bool update_board(int x, int y, T mark);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class FiveByFivePlayer : public Player<T> {
public:
    FiveByFivePlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class FiveByFiveRandomPlayer : public RandomPlayer<T> {
public:
    FiveByFiveRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
FiveByFiveBoard<T>::FiveByFiveBoard() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FiveByFiveBoard<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void FiveByFiveBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                cout << "- | ";
            } else {
                cout << this->board[i][j] << " | ";
            }
        }
        cout << "\n-------------------------";
    }
    cout << endl;
}

template <typename T>
bool FiveByFiveBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0)
                return true;
        }
    }
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i < this->rows - 2; i++) {
            if (this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] && this->board[i][j] != 0)
                return true;
        }
    }
    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if (this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != 0)
                return true;
            if (this->board[i][j+2] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j] && this->board[i][j+2] != 0)
                return true;
        }
    }
    return false;
}

template <typename T>
bool FiveByFiveBoard<T>::is_draw() {
    return this->n_moves == 24 && !is_win();
}

template <typename T>
bool FiveByFiveBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
FiveByFivePlayer<T>::FiveByFivePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FiveByFivePlayer<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (x y): ";
    cin >> x >> y;
}

template <typename T>
FiveByFiveRandomPlayer<T>::FiveByFiveRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void FiveByFiveRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 5;
    y = rand() % 5;
}

void _5x5TicTacToe() {
    Player<char> *players[2];
    string playerXName, player2Name;

    FiveByFiveBoard<char> *B = new FiveByFiveBoard<char>();

    cin.ignore();

    cout << "Enter Player X name: ";
    getline(cin, playerXName);
    players[0] = new FiveByFivePlayer<char>(playerXName, 'X');

    int choice;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    cin.ignore();

   
    while (choice != 1 && choice != 2) {  
        cout << "Invalid choice for Player 2. Please enter 1 for Human or 2 for Random Computer: ";
        cin >> choice;
        cin.ignore(); 
    }

    if (choice == 1) {
        cout << "Enter Player 2 name: ";
        getline(cin, player2Name);
        players[1] = new FiveByFivePlayer<char>(player2Name, 'O');
    }
    else if (choice == 2) {
        players[1] = new FiveByFiveRandomPlayer<char>('O');
    }

    GameManager<char> game(B, players);
    game.run();
}

#endif //_5X5_TIC_TAC_TOE_H
