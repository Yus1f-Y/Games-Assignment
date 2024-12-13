#ifndef _MISERETICTACTOEBOARD_H
#define _MISERETICTACTOEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <limits>

using namespace std;

template <typename T>
class MisereTicTacToeBoard : public Board<T>
{
public:
    MisereTicTacToeBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;


    void random_player(T symbol);
};

template <typename T>
MisereTicTacToeBoard<T>::MisereTicTacToeBoard()
{
    this->rows = 3;
    this->columns = 3;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; ++i)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j)
        {
            this->board[i][j] = '-';
        }
    }
    srand(time(0)); // set/edit random numbers
}

template <typename T>
bool MisereTicTacToeBoard<T>::update_board(int x, int y, T symbol)
{
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '-')
    {
        return false; // Invalid move
    }
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}

template <typename T>
void MisereTicTacToeBoard<T>::display_board()
{
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j < this->columns; ++j)
        {
            cout << this->board[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename T>
bool MisereTicTacToeBoard<T>::is_win()
{
    // player's win means they lose in Misere Tic-Tac-Toe
    for (int i = 0; i < 3; ++i)
    {
        // Check rows
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != '-')
        {
            return true;
        }
        // Check columns
        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != '-')
        {
            return true;
        }
    }
    // Check diagonals
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != '-')
    {
        return true; // Diagonal from top left to bottom right
    }
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != '-')
    {
        return true; // Diagonal from top right to bottom left
    }
    return false;
}

template <typename T>
bool MisereTicTacToeBoard<T>::is_draw()
{
    return this->n_moves == 9;
}

template <typename T>
bool MisereTicTacToeBoard<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
void MisereTicTacToeBoard<T>::random_player(T symbol)
{
    int x, y;
    do
    {
        x = rand() % this->rows;    // random row
        y = rand() % this->columns; // random col
    } while (this->board[x][y] != '-'); // check if the cell empty

    // تحديث اللوحة
    update_board(x, y, symbol);
    cout << "Random player (" << symbol << ") played at: (" << x << ", " << y << ")" << endl;
}

// play Misere Tic Tac Toe
void playMisereTicTacToe()
{
    MisereTicTacToeBoard<char> game;
    cout << "\n--- Misere Tic Tac Toe ---\n";

    // Player setup
    string playerXName, playerOName;
    int playerXType, playerOType;

    cout << "Enter Player X name: ";
    cin >> playerXName;

    // Ensure valid input for Player X type
    while (true)
    {
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> playerXType;

        if (cin.fail() || (playerXType != 1 && playerXType != 2))
        {
            cout << "Invalid input Please enter 1 for Human or 2 for Random Computer.\n";
            cin.clear(); // clear buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    cout << "Enter Player O name: ";
    cin >> playerOName;

    while (true)
    {
        cout << "Choose Player O type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> playerOType;

        if (cin.fail() || (playerOType != 1 && playerOType != 2))
        {
            cout << "Invalid input Please enter 1 for Human or 2 for Random Computer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    char currentPlayer = 'X';
    string currentPlayerName = playerXName;
    int currentPlayerType = playerXType;

    game.display_board();

    while (!game.game_is_over())
    {
        cout << currentPlayerName << " (" << currentPlayer << "), it's your turn." << endl;

        if (currentPlayerType == 1) // Human
        {
            int x, y;
            while (true)
            {
                cout << "Enter row and column (0-2): ";
                cin >> x >> y;

                if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3)
                {
                    cout << "Invalid input. Please enter numbers between 0 and 2 for both row and column.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (!game.update_board(x, y, currentPlayer))
                {
                    cout << "Cell is already occupied. Try again.\n";
                }
                else
                {
                    break;
                }
            }
        }
        else if (currentPlayerType == 2) // Random Computer
        {
            game.random_player(currentPlayer);
        }

        game.display_board();

        if (game.is_win())
        {
            if (currentPlayer == 'X')
            {
                currentPlayer = 'O';
                currentPlayerName = playerOName;
                currentPlayerType = playerOType;
            }
            else
            {
                currentPlayer = 'X';
                currentPlayerName = playerXName;
                currentPlayerType = playerXType;
            }

            cout << currentPlayerName << " (" << currentPlayer << ") wins" << endl;
            return;
        }

        if (game.is_draw())
        {
            cout << "It's a draw!" << endl;
            return;
        }

        if (currentPlayer == 'X')
        {
            currentPlayer = 'O';
            currentPlayerName = playerOName;
            currentPlayerType = playerOType;
        }
        else
        {
            currentPlayer = 'X';
            currentPlayerName = playerXName;
            currentPlayerType = playerXType;
        }
    }
}

#endif
