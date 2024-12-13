#ifndef TicTacToe_5x5
#define TicTacToe_5x5

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

template <typename T>
class TicTacToe5x5 : public Board<T>
{
public:
    TicTacToe5x5()
    {
        this->rows = 5;
        this->columns = 5;
        this->board = new T *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++)
            {
                this->board[i][j] = ' '; // Initialize the board with empty spaces
            }
        }
        srand(time(0)); // set/edit Random numbers
    }

    bool update_board(int x, int y, T symbol) override
    {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ')
        {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                cout << (this->board[i][j] == ' ' ? '-' : this->board[i][j]);
                if (j < this->columns - 1)
                {
                    cout << " | ";
                }
            }
            cout << endl;
            if (i < this->rows - 1)
            {
                cout << string(this->columns * 4 - 1, '-') << endl;
            }
        }
    }

    bool is_win() override
    {
        // check win horizontally
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j <= this->columns - 3; j++)
            {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2])
                {
                    return true;
                }
            }
        }

        // check win vertically
        for (int j = 0; j < this->columns; j++)
        {
            for (int i = 0; i <= this->rows - 3; i++)
            {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j])
                {
                    return true;
                }
            }
        }

        // Check win diagonally --> left to right
        for (int i = 0; i <= this->rows - 3; i++)
        {
            for (int j = 0; j <= this->columns - 3; j++)
            {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2])
                {
                    return true;
                }
            }
        }

        // Check win diagonally --> right to left
        for (int i = 0; i <= this->rows - 3; i++)
        {
            for (int j = 2; j < this->columns; j++)
            {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i][j] == this->board[i + 2][j - 2])
                {
                    return true;
                }
            }
        }

        // If no winner 
        return false;
    }

    bool is_draw() override
    {
        return this->n_moves == (this->rows * this->columns);
    }

    bool game_is_over() override
    {
        return is_win() || is_draw();
    }

    void random_player(T symbol)
    {
        int x, y;
        do
        {
            x = rand() % this->rows;
            y = rand() % this->columns;
        } while (this->board[x][y] != ' '); // Check if the cell is empty

        update_board(x, y, symbol);
        cout << "Random player (" << symbol << ") played at: (" << x << ", " << y << ")" << endl;
    }
};


void playTicTacToe5x5()
{
    TicTacToe5x5<char> game;
    cout << "\n--- Tic Tac Toe 5x5 ---\n";

    // Player setup
    string playerXName, playerOName;
    int playerXType, playerOType;

    do {
        cout << "Enter Player X name: ";
        cin >> playerXName;
        if (playerXName.empty()) {
            cout << "Name cannot be empty. Please enter a valid name." << endl;
        }
    } while (playerXName.empty());

    do {
        cout << "Choose Player X type:\n1. Human\n2. Random Computer\n";
        cin >> playerXType;
        if (cin.fail() || (playerXType != 1 && playerXType != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter 1 or 2." << endl;
        }
    } while (playerXType != 1 && playerXType != 2);

    do {
        cout << "Enter Player O name: ";
        cin >> playerOName;
        if (playerOName.empty()) {
            cout << "Name cannot be empty. Please enter a valid name." << endl;
        }
    } while (playerOName.empty());

    do {
        cout << "Choose Player O type:\n1. Human\n2. Random Computer\n";
        cin >> playerOType;
        if (cin.fail() || (playerOType != 1 && playerOType != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice Please enter 1 or 2." << endl;
        }
    } while (playerOType != 1 && playerOType != 2);

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
            bool validInput = false;
            while (!validInput) {
                cout << "Enter row and column (0-4): ";
                cin >> x >> y;

                if (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter numbers between 0 and 4." << endl;
                } else if (!game.update_board(x, y, currentPlayer)) {
                    cout << "Cell is already occupied. Try again." << endl;
                } else {
                    validInput = true;
                }
            }
        }
        else if (currentPlayerType == 2) // Random Computer
        {
            game.random_player(currentPlayer);
        }

        // Switch to the next player
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
            currentPlayerName = playerOName;
            currentPlayerType = playerOType;
        } else {
            currentPlayer = 'X';
            currentPlayerName = playerXName;
            currentPlayerType = playerXType;
        }

        game.display_board();
    }

    if (game.is_win()) {

        if (currentPlayer == 'X') {
            currentPlayer = 'O';
            currentPlayerName = playerOName;
        } else {
            currentPlayer = 'X';
            currentPlayerName = playerXName;
        }
        cout << "Congratulations, " << currentPlayerName << " You won the game." << endl;
    } else if (game.is_draw()) {
        cout << "It's a draw! No winner this time." << endl;
    }
}
#endif 
