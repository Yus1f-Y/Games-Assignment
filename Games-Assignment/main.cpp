#include <iostream>
#include "NumericPlay.h"
#include "pyramidplay.h"
int main()
{

    PlayPyramidGame<char>a;
    PyramidBoard<char> c;
    a.startGame(c);

    PlayNumericGame<int>p;
    NumericBoard<int> b;
    p.startGame(b);
    return 0;
}
