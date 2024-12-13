#pragma once
#include <bits/stdc++.h>
#include "UltimateTTT.h"
using namespace std;

template <typename T>
class PlayUltimateGame {

private:
    Player<T>* players[2];

    void setPlayer(int i) {
        string name;
        char symbol;
        if(i == 0) {
            symbol = 'X';
        }else {
            symbol = 'O';
        }

        cout << "Player " << symbol <<", enter your name: ";
        cin.ignore();
        getline(cin, name);


        int choice;
        cout << "Choose Player X type:\n";
        cout << "[1]-Human\n";
        cout << "[2]-Random Computer\n";
        //cout << "[3]-Smart Computer (AI)\n";
        choice = valid_choice(1,2);

        switch(choice) {
            case 1:
                players[i] = new Ultimateplayer<T>(name, symbol);
            break;
            case 2:
                players[i] = new Ultimaterandomplayer<T>(symbol);
            break;
            /*case 3:
                players[i] = new X_O_MinMax_Player<char>('X');
            players[i]->setBoard(B);
            break;*/
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
        cout << "Welcome to the game!\n";

        for(int i = 0; i < 2; i++) {
            setPlayer(i);
        }

        int x, y;


        boardPtr.display_board();

        while (!boardPtr.game_is_over()) {
            for (int i : {0, 1}) {
                if(players[i]->getname() == "Computer") {
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
    }
};