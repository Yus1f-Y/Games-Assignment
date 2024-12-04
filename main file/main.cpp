#include <iostream>
#include "NumericPlay.h"
#include "pyramidplay.h"
#include "4x4TTT.h"
#include <cstdlib>

#include "UltimatePlay.h"
#include "UltimateTTT.h"

void game1() {
    PlayPyramidGame<char>A1;
    PyramidBoard<char> B;
    A1.startGame(B);
}

void game2() {

}

void game3() {

}

void game4() {

}

void game5() {
    PlayNumericGame<int>p;
    NumericBoard<int> b;
    p.startGame(b);
}

void game6() {

}

void game7() {
    PlayPyramidGame<char>a1;
    FourBYFourTTTBoard<char> c1;
    a1.startGame(c1);
}

void game8() {
    UltimateTTTBoard<char> A;
    PlayUltimateGame<char>B;
    B.StartGame(A);
}

void menu() {
    bool flag = true;
    while (flag){
        cout << endl << endl << endl << "Welcome To th games apllication." << endl;
        cout << "Please choose One Of The Next Options: " << endl;
        cout << "[1]- Pyramid TIC-TAC-TOE." << endl;
        cout << "[2]- Four in a row." << endl;
        cout << "[3]- 5 x 5 TIC-TAC-TOE." << endl;
        cout << "[4]- Word TIC-TAC-TOE." << endl;
        cout << "[5]- Numeric TIC-TAC-TOE." << endl;
        cout << "[6]- Misere TIC-TAC-TOE." << endl;
        cout << "[7]- 4 x 4 TIC-TAC-TOE." << endl;
        cout << "[8]- Ultimate TIC-TAC-TOE." << endl;
        cout << "[9]- Quit the program" << endl << endl;
        int choice = valid_choice(1, 9);

        system("cls");

        switch (choice) {
            case 1:
                game1();
                    break;
            case 2:
                ///game2
                    break;
            case 3:
                ///game3
                    break;
            case 4:
                ///game4
                    break;
            case 5:
                game5();
                    break;
            case 6:
                ///game6
                    break;
            case 7:
                game7();
                    break;
            case 8:
                game8();
                    break;
            case 9:
                ///Exit
                    flag = false;
            break;
        }
    }
}

int main()
{

    return 0;
}
