#pragma once
#include <iostream>
#include <string>
#include "Numeric.h"
using namespace std;

template <typename T>
// PlayGame Class
class PlayNumericGame {
private:
    Player<T>* firstPlayer = nullptr;
    Player<T>* secondPlayer = nullptr;

    static int menu1() {
        cout << "[1] Play VS a friend.\n";
        cout << "[2] Play VS computer.\n";
        return valid_choice(1, 2);
    }

    static int menu2() {
        cout << "[1] Play again.\n";
        cout << "[2] Exit.\n";
        return valid_choice(1, 2);
    }

    void setPlayers(bool vsComputer) {
        string name1, name2;
        int symbol1, symbol2;

        cout << "Player 1, enter your name: ";
        cin.ignore();
        getline(cin, name1);

        firstPlayer = new Numericplayer<T>(name1, 0);

        if (vsComputer) {
            secondPlayer = new RandomNumericplayer<T>(-1);
        } else {
            cout << "Player 2, enter your name: ";
            cin.ignore();
            getline(cin, name2);
            secondPlayer = new Numericplayer<T>(name2, 0);
        }
    }

    static void playerTurn(Player<T>* player, Board<T>* board) {
        int x, y;
        while (true) {
            player->getmove(x, y);

            int value;

            if(player->getsymbol() == -1) {
                value = rand() % 15;
                if(value == 0) {
                    value++;
                }
            }
            else {
                cout << "Enter the value you want to insert(between 0 and 15): \n";
                value = valid_choice(1,14);
            }

            if (board->update_board(x, y, value)) {
                break;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    static void announceWinner(Player<T>* winner) {
        cout << "The winner is " << winner->getname() << "!\n";
    }

public:

    void startGame(Board<T>& board) {
        cout << "Welcome to the game!\n";
        bool vsComputer;
        if(menu1() == 1) {
            vsComputer = false;
        }else {
            vsComputer = true;
        }

        setPlayers(vsComputer);


        while (true) {

            while (!board.game_is_over()) {
                board.display_board();
                playerTurn(firstPlayer, &board);
                board.display_board();
                if (board.is_win()) {
                    announceWinner(firstPlayer);
                    break;
                }
                if (board.is_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }

                playerTurn(secondPlayer, &board);
                board.display_board();
                if (board.is_win()) {
                    announceWinner(secondPlayer);
                    break;
                }
                if (board.is_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }
            }

            if (menu2() == 2) {
                cout << "Goodbye!\n";
                break;
            }
        }
    }

    ~PlayNumericGame() {
        delete firstPlayer;
        delete secondPlayer;
    }
};
