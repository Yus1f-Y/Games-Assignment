#pragma once
#include <bits/stdc++.h>
#include "UltimateTTT.h"
using namespace std;

template <typename T>
class PlayUltimateGame {

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
        char symbol1, symbol2;

        // Set up Player 1
        cout << "Player 1, enter your name: ";
        cin.ignore();
        getline(cin, name1);
        cout << "Choose your symbol:\n[1] 'X'\n[2] 'O'\n";
        symbol1 = (valid_choice(1, 2) == 1) ? 'X' : 'O';

        firstPlayer = new Ultimateplayer<T>(name1, symbol1);

        // Set up Player 2
        if (vsComputer) {
            symbol2 = (symbol1 == 'X') ? 'O' : 'X';
            secondPlayer = new Ultimaterandomplayer<T>(symbol2);
        } else {
            cout << "Player 2, enter your name: ";
            cin.ignore();
            getline(cin, name2);
            symbol2 = (symbol1 == 'X') ? 'O' : 'X';
            secondPlayer = new Ultimateplayer<T>(name2, symbol2);
        }
    }

    static void playerturn(Player<T>* player, bool isComputer, UltimateTTTBoard<T>& boared) {
        while (true) {
            if (isComputer) {
                if(boared.update_board_random(player->getsymbol())) {
                    break;
                }
            } else {
                int x, y;
                player->getmove(x, y);
                if(boared.update_board(x,y, player->getsymbol())) {
                    break;
                }
            }
        }
    }

    static void announceWinner(Player<T>* winner) {
        cout << "The winner is " << winner->getname() << "!\n";
    }

public:

    void StartGame(UltimateTTTBoard<T> boardPtr) {
        while (true) {
            cout << "Welcome to the game!\n";
            bool vsComputer;
            if(menu1() == 1) {
                vsComputer = false;
            }else {
                vsComputer = true;
            }

            setPlayers(vsComputer);

            Player<T>* players[2];
            players[0] = firstPlayer;
            players[1] = secondPlayer;
            int x, y;


            boardPtr.display_board();

            while (!boardPtr.game_is_over()) {
                for (int i : {0, 1}) {
                    if(vsComputer && i == 1) {
                        while (true) {
                            bool check = boardPtr.update_board_random(players[i]->getsymbol());
                            if(check) {
                                break;
                            }
                        }
                        boardPtr.display_board();
                        if (boardPtr.is_win()) {
                            announceWinner(players[i]);
                            break;
                        }
                        if (boardPtr.is_draw()) {
                            cout << "Draw!\n";
                            break;
                        }
                    }
                    else {
                        players[i]->getmove(x, y);
                        while (!boardPtr.update_board(x, y, players[i]->getsymbol())) {
                            players[i]->getmove(x, y);
                        }
                        boardPtr.display_board();
                        if (boardPtr.is_win()) {
                            announceWinner(players[i]);
                            break;
                        }
                        if (boardPtr.is_draw()) {
                            cout << "Draw!\n";
                            break;
                        }
                    }
                }
            }

            if (menu2() == 2) {
                cout << "Goodbye!\n";
                break;
            }
        }
    }

    ~PlayUltimateGame() {
        delete firstPlayer;
        delete secondPlayer;
    }
};