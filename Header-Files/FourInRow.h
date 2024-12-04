#ifndef _four_in_row_H
#define _four_in_row_H


#include "BoardGame_Classes.h"

template <typename T>
class Four_in_row_board:public Board<T> {
public:
    Four_in_row_board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Four_in_row_player : public Player<T> {
public:
    Four_in_row_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Four_in_row_Rand_player : public RandomPlayer<T>{
public:
    Four_in_row_Rand_player (T symbol);
    void getmove(int &x, int &y) ;
};

//-------------------------------------------------------------IMPLEMENTATION


#include <iostream>
template <typename T>
Four_in_row_board<T>::Four_in_row_board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Four_in_row_board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    
    if (this->board[x][y] != 0) {
        return false; 
    }

    
    if (x < this->rows - 1 && this->board[x + 1][y] == 0) {
        return false; 
    }

    
    if (mark != 0) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
    } else {
        this->n_moves--;
        this->board[x][y] = 0;
    }

    return true;
}


template <typename T>
void Four_in_row_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            
            cout << "(" << i << "," << j << ")";
           cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n" << string(8 * this->columns, '-');  
    }
    cout << endl;
}
template<typename T>
bool Four_in_row_board<T>::is_win() {
    // Check rows 
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][0] != 0) ||
            (this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][3] == this->board[i][4] && this->board[i][1] != 0) ||
            (this->board[i][2] == this->board[i][3] && this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][2] != 0)||
            (this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][5] == this->board[i][6] && this->board[i][3] != 0)) {
            return true;
        }
    }
    // check colums
    for (int i = 0; i < this->columns; i++)
    {
        if ((this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[0][i] != 0)||
            (this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[3][i] == this->board[4][i] && this->board[1][i] != 0)||
            (this->board[2][i] == this->board[3][i] && this->board[3][i] == this->board[4][i] && this->board[4][i] == this->board[5][i] && this->board[2][i] != 0 ))
        {
            return true;
        }
        
    }
    

    // Check diagonal wins (positive slope)
    for (int row = 0; row <= 6 - 4; row++) {
        for (int col = 0; col <= 7 - 4; col++) {
            if (this->board[row][col] != 0 &&
               this-> board[row][col] ==this-> board[row + 1][col + 1] &&
               this-> board[row][col] ==this-> board[row + 2][col + 2] &&
               this-> board[row][col] == this->board[row + 3][col + 3]) {
                return true;
            }
        }
    }
    // Check diagonal wins (negative slope)
    for (int row = 3; row < 6; row++) {
        for (int col = 0; col <= 7 - 4; col++) {
            if (this->board[row][col] != 0 &&
               this-> board[row][col] == this->board[row - 1][col + 1] &&
                this->board[row][col] == this->board[row - 2][col + 2] &&
               this-> board[row][col] == this->board[row - 3][col + 3]) {
                return true;
            }
        }
    }

    return false;
}
template <typename T>
bool Four_in_row_board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Four_in_row_board<T>::game_is_over() {
    return is_win() || is_draw();

}
template <typename T>
Four_in_row_player<T>::Four_in_row_player(string name, T symbol) : Player<T>(name, symbol) {
   
}

template <typename T>
void Four_in_row_player<T>::getmove(int& x, int& y) { 

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces and make sure you play in the bottom: ";
    cin >> x >> y;
}

template <typename T>
Four_in_row_Rand_player<T>::Four_in_row_Rand_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator


}
#include <cstdlib> // 
#include <ctime>   //
template <typename T>
void Four_in_row_Rand_player<T>::getmove(int& x, int& y) {

    x = rand() % 6; 
    y = rand() % 7;
}

#endif