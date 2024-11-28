#pragma once
#include <iostream>
#include <string>
#include "Pyramid.h"
using namespace std;


template <typename T>
// PlayGame Class
class PlayPyramidGame {
private:
    Player<T>* firstPlayer = nullptr;
    Player<T>* secondPlayer = nullptr;
    int numGames = 0;

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
        char symbol1, symbol2;

        // Set up Player 1
        cout << "Player 1, enter your name: ";
        cin.ignore();
        getline(cin, name1);
        cout << "Choose your symbol:\n[1] 'X'\n[2] 'O'\n";
        symbol1 = (valid_choice(1, 2) == 1) ? 'X' : 'O';

        firstPlayer = new Pyramidplayer<T>(name1, symbol1);

        // Set up Player 2
        if (vsComputer) {
            symbol2 = (symbol1 == 'X') ? 'O' : 'X';
            secondPlayer = new RandomPyramidplayer<T>(symbol2);
        } else {
            cout << "Player 2, enter your name: ";
            cin.ignore();
            getline(cin, name2);
            symbol2 = (symbol1 == 'X') ? 'O' : 'X';
            secondPlayer = new Pyramidplayer<T>(name2, symbol2);
        }
    }

    static void playerTurn(Player<T>* player, Board<T>& board) {
        int x, y;
        while (true) {
            player->getmove(x, y);
            if (board.update_board(x, y, player->getsymbol())) {
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


        Player<T>* players[2];
        players[1] = firstPlayer;
        players[2] = secondPlayer;

        //GameManager<T>Pyramidgame(&board, players);
        //Pyramidgame.run();


        while (true) {



            numGames++;

            while (!board.game_is_over()) {
                board.display_board();
                playerTurn(firstPlayer, board);
                board.display_board();
                if (board.is_win()) {
                    announceWinner(firstPlayer);
                    break;
                }
                if (board.is_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }

                playerTurn(secondPlayer, board);
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

    ~PlayPyramidGame() {
        delete firstPlayer;
        delete secondPlayer;
    }
};
