#ifndef _word_tic_tac_toe_H
#define _word_tic_tac_toe_H


#include "BoardGame_Classes.h"
#include <unordered_set>

template <typename T>
class Word_toe_board : public Board<T>{

public:
    unordered_set<string> words;
    string check1 = " ",check2 = " ",check3 = " ",check4 = " ",check5 =" ",check6 =" ",check7 = " ", check8 =" ";

public:
    Word_toe_board();
    bool update_board(int x , int y , T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Word_toe_player : public Player<T> {
private:
    T current_symbol ;  

public:
    Word_toe_player(string name, T symbol ='x');


    void getmove(int& x, int& y);

    
    T get_symbol() const;
};


template<typename T>
class Word_toe_Radn_player : public RandomPlayer<T>{
public:
    Word_toe_Radn_player(T symbol);
    void getmove(int &x , int &y);

};

//-------------------------------------------------------IMPLEMETATION
#include <iostream>
#include <iomanip>
#include <cctype>
#include<fstream>
#include<vector>
template <typename T>
Word_toe_board<T>::Word_toe_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    
    ifstream file("dic.txt");
    
    if (file.is_open())
    {
        string word;
        while (file>>word)
        {
            words.insert(word);
        }
        file.close();
        
    }
    
    
    
    


    
}

template <typename T>
bool Word_toe_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void Word_toe_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template<typename T>
bool Word_toe_board<T>::is_win() {
    check1 = string(1, this->board[0][0]) + string(1, this->board[0][1]) + string(1, this->board[0][2]);
    check2 = string(1, this->board[1][0]) + string(1, this->board[1][1]) + string(1, this->board[1][2]);
    check3 = string(1, this->board[2][0]) + string(1, this->board[2][1]) + string(1, this->board[2][2]);
    check4 = string(1, this->board[0][0]) + string(1, this->board[1][0]) + string(1, this->board[2][0]);
    check5 = string(1, this->board[0][1]) + string(1, this->board[1][1]) + string(1, this->board[2][1]);
    check6 = string(1, this->board[0][2]) + string(1, this->board[1][2]) + string(1, this->board[2][2]);
    check7 = string(1, this->board[0][0]) + string(1, this->board[1][1]) + string(1, this->board[2][2]);
    check8 = string(1, this->board[0][2]) + string(1, this->board[1][1]) + string(1, this->board[2][0]);

    vector<string> checks = {check1, check2, check3, check4, check5, check6, check7, check8};

    for (const string& check : checks) {
        if (words.count(check)) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool Word_toe_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
template <typename T>
bool Word_toe_board<T>::game_is_over() {
    return is_win() || is_draw();

}
template <typename T>
Word_toe_player<T>::Word_toe_player(string name, T symbol) : Player<T>(name, symbol) {
   
}

template <typename T>
void Word_toe_player<T>::getmove(int& x, int& y) {
    while (true)
    {
        cout << "Please enter a character for your move from (a to z): ";
        cin >> this->symbol;
        if (isalpha(this->symbol))
        {
            this->symbol = toupper(this->symbol);
            break;
        }
        cout << "Invalid input. Only characters a-z are allowed.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}



template <typename T>
T Word_toe_player<T>::get_symbol() const {
    return current_symbol;
}



template <typename T>
Word_toe_Radn_player<T>::Word_toe_Radn_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator


}

#include <cstdlib> // 
#include <ctime>   //
template <typename T>
void Word_toe_Radn_player<T>::getmove(int& x, int& y) {
    
    this->symbol = 'A' + (rand() % 26); 

    x = rand() % 3; 
    y = rand() % 3;
}




#endif
